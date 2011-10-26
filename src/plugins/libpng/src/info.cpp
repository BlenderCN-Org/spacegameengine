/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/libpng/info.hpp>
#include <sge/libpng/png.hpp>
#include <sge/image/exception.hpp>
#include <fcppt/text.hpp>


sge::libpng::info::info(
	png_structp const _ptr
)
:
	ptr_(
		_ptr
	),
	info_(
		png_create_info_struct(
			_ptr
		)
	)
{
	if(
		!info_
	)
		throw image::exception(
			FCPPT_TEXT("couldn't generate png info structure")
		);
}

sge::libpng::info::~info()
{
	png_destroy_info_struct(
		ptr_,
		&info_
	);
}

png_infop
sge::libpng::info::get() const
{
	return info_;
}
