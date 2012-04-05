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


#include <sge/charconv/system_fwd.hpp>
#include <sge/font/metrics_unique_ptr.hpp>
#include <sge/font/size_type.hpp>
#include <sge/freetype/system.hpp>
#include <sge/freetype/metrics.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


sge::freetype::system::system(
	sge::charconv::system &_conv_system
)
:
	conv_system_(
		_conv_system
	)
{
}

sge::freetype::system::~system()
{
}

sge::font::metrics_unique_ptr
sge::freetype::system::create_font(
	boost::filesystem::path const &_font_name,
	font::size_type const _font_size
)
{
	return
		sge::font::metrics_unique_ptr(
			fcppt::make_unique_ptr<
				freetype::metrics
			>(
				fcppt::ref(
					library_
				),
				fcppt::ref(
					conv_system_
				),
				_font_name,
				_font_size
			)
		);
}
