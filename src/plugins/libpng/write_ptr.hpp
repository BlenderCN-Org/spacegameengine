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


#ifndef SGE_LIBPNG_WRITE_PTR_HPP_INCLUDED
#define SGE_LIBPNG_WRITE_PTR_HPP_INCLUDED

#include "png.hpp"
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace libpng
{

class write_ptr
{
	FCPPT_NONCOPYABLE(
		write_ptr
	);
public:
	write_ptr(
		png_const_charp user_png_ver,
		png_voidp error_ptr,
		png_error_ptr error_fn,
		png_error_ptr warn_fn
	);

	~write_ptr();

	png_structp
	ptr() const;
private:
	png_structp ptr_;
};

}
}

#endif
