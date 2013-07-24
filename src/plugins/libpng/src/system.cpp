/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/image/capabilities.hpp>
#include <sge/image/capabilities_field.hpp>
#include <sge/image/file_exception.hpp>
#include <sge/image/optional_path.hpp>
#include <sge/image/unsupported_format.hpp>
#include <sge/image2d/file_unique_ptr.hpp>
#include <sge/libpng/file.hpp>
#include <sge/libpng/system.hpp>
#include <sge/media/const_raw_range.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional_comparison.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/array.hpp>
#include <ios>
#include <fcppt/config/external_end.hpp>


namespace
{

sge::media::extension const supported_extension(
	FCPPT_TEXT("png")
);

sge::media::extension_set const const_extensions{
	supported_extension
};

}

sge::libpng::system::system()
{
}

sge::libpng::system::~system()
{
}

sge::image2d::file_unique_ptr
sge::libpng::system::load(
	boost::filesystem::path const &_path
)
{
	boost::filesystem::ifstream file_stream(
		_path,
		std::ios_base::binary);

	if(
		!file_stream.is_open()
	)
		throw image::file_exception(
			sge::image::optional_path(
				_path
			),
			FCPPT_TEXT("couldn't open file"));
	try
	{
		return
			sge::image2d::file_unique_ptr(
				fcppt::make_unique_ptr<
					libpng::file
				>(
					file_stream,
					sge::image::optional_path(
						_path)
				)
			);
	}
	catch(
		sge::image::unsupported_format const &
	)
	{
		return sge::image2d::file_unique_ptr();
	}
}

sge::image2d::file_unique_ptr
sge::libpng::system::load_raw(
	sge::media::const_raw_range const &_range,
	sge::media::optional_extension const &_extension
)
{
	if(
		_extension
		&&
		_extension
		!=
		sge::media::optional_extension(
			supported_extension
		)
	)
		return sge::image2d::file_unique_ptr();

	typedef
	boost::iostreams::stream<
		boost::iostreams::array_source
	>
	stream_type;

	stream_type raw_stream(
		reinterpret_cast<
			boost::iostreams::array_source::char_type const *
		>(
			_range.begin()
		),
		reinterpret_cast<
			boost::iostreams::array_source::char_type const *
		>(
			_range.end()
		)
	);

	try
	{
		return
			sge::image2d::file_unique_ptr(
				fcppt::make_unique_ptr<
					libpng::file
				>(
					raw_stream,
					sge::image::optional_path()
				)
			);
	}
	catch (
		sge::image::unsupported_format const &)
	{
		return sge::image2d::file_unique_ptr();
	}
}

sge::image2d::file_unique_ptr
sge::libpng::system::load_stream(
	std::istream &_stream,
	sge::media::optional_extension const &_extension
)
{
	if(
		_extension &&
		_extension
		!=
		sge::media::optional_extension(
			supported_extension
		)
	)
		return sge::image2d::file_unique_ptr();

	try
	{
		return
			sge::image2d::file_unique_ptr(
				fcppt::make_unique_ptr<
					libpng::file
				>(
					_stream,
					sge::image::optional_path()
				)
			);
	}
	catch (
		sge::image::unsupported_format const &)
	{
		return sge::image2d::file_unique_ptr();
	}
}

sge::image2d::file_unique_ptr
sge::libpng::system::create(
	image2d::view::const_object const &_view,
	sge::media::optional_extension const &_extension
)
{
	return
		(
			_extension
			&&
			*_extension != supported_extension
		)
		?
			sge::image2d::file_unique_ptr()
		:
			sge::image2d::file_unique_ptr(
				fcppt::make_unique_ptr<
					file
				>(
					_view
				)
			)
		;
}

sge::image::capabilities_field const
sge::libpng::system::capabilities() const
{
	return
		sge::image::capabilities_field(
			image::capabilities::threadsafe
		);
}

sge::media::extension_set const
sge::libpng::system::extensions() const
{
	return const_extensions;
}
