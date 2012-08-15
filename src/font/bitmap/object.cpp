/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/font/exception.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text_parameters_fwd.hpp>
#include <sge/font/text_unique_ptr.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/element_vector.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/get.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/parse_file.hpp>
#include <sge/src/font/bitmap/char_metric.hpp>
#include <sge/src/font/bitmap/load_one_file.hpp>
#include <sge/src/font/bitmap/object.hpp>
#include <sge/src/font/bitmap/text.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


sge::font::bitmap::object::object(
	boost::filesystem::path const &_path,
	sge::image2d::system &_image_system
)
:
	images_(),
	line_height_(),
	char_map_()
{
	sge::parse::json::object result;

	if(
		!sge::parse::json::parse_file(
			_path,
			result
		)
	)
		throw sge::font::exception(
			fcppt::filesystem::path_to_string(
				_path
			)
			+ FCPPT_TEXT(" contains errors!")
		);


	sge::parse::json::member_map const &top_members(
		result.members
	);

	line_height_
		= sge::parse::json::find_member_exn<
			int
		>(
			top_members,
			FCPPT_TEXT("line_height")
		);

	boost::filesystem::path const parent_path(
		_path.parent_path()
	);

	sge::parse::json::array const &textures_array(
		sge::parse::json::find_member_exn<
			sge::parse::json::array
		>(
			top_members,
			FCPPT_TEXT("textures")
		)
	);

	for(
		sge::parse::json::element_vector::const_iterator elem_it(
			textures_array.elements.begin()
		);
		elem_it != textures_array.elements.end();
		++elem_it
	)
		fcppt::container::ptr::push_back_unique_ptr(
			images_,
			sge::font::bitmap::load_one_file(
				parent_path,
				sge::parse::json::get<
					parse::json::object
				>(
					*elem_it
				),
				_image_system,
				char_map_
			)
		);
}

sge::font::bitmap::object::~object()
{
}

sge::font::text_unique_ptr
sge::font::bitmap::object::create_text(
	sge::font::string const &_string,
	sge::font::text_parameters const &_text_parameters
)
{
	return
		sge::font::text_unique_ptr(
			fcppt::make_unique_ptr<
				sge::font::bitmap::text
			>(
				fcppt::ref(
					char_map_
				),
				_string,
				fcppt::cref(
					_text_parameters
				)
			)
		);
}