/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/font/dpi.hpp>
#include <sge/font/parameters.hpp>
#include <sge/pango/create_font_map.hpp>
#include <sge/pango/glib_deleter.hpp>
#include <sge/pango/pango_font_map_unique_ptr.hpp>
#include <fcppt/maybe_void.hpp>
#include <fcppt/config/external_begin.hpp>
#include <pango/pangoft2.h>
#include <fcppt/config/external_end.hpp>


sge::pango::pango_font_map_unique_ptr
sge::pango::create_font_map(
	sge::font::parameters const &_parameters
)
{
	sge::pango::pango_font_map_unique_ptr result(
		::pango_ft2_font_map_new()
	);

	fcppt::maybe_void(
		_parameters.dpi(),
		[
			&result
		](
			sge::font::dpi const _dpi
		)
		{
			::pango_ft2_font_map_set_resolution(
				reinterpret_cast<
					PangoFT2FontMap *
				>(
					result.get()
				),
				_dpi.w(),
				_dpi.h()
			);
		}
	);

	return
		result;
}
