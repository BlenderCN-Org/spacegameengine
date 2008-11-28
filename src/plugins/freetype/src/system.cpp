/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../system.hpp"
#include "../metrics.hpp"

sge::font::metrics_ptr const
sge::ft::system::create_font(
	path const &font_name,
	font::size_type const font_size)
{
	loaded_fonts_list::mapped_type &wfptr = loaded_fonts[
		loaded_fonts_list::key_type(
			font_size,
			font_name
		)
	];

	font::metrics_ptr fptr(wfptr.lock());
	if (!fptr)
	{
		fptr.reset(
			new metrics(
				library_,
				font_name,
				font_size));
		wfptr = fptr.boost_ptr();
	}
	return fptr;
}
