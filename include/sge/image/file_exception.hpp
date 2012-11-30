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


#ifndef SGE_IMAGE_FILE_EXCEPTION_HPP_INCLUDED
#define SGE_IMAGE_FILE_EXCEPTION_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/image/exception.hpp>
#include <sge/image/optional_path_fwd.hpp>
#include <sge/image/symbol.hpp>
#include <fcppt/string.hpp>


namespace sge
{
namespace image
{

class SGE_CLASS_SYMBOL file_exception
:
	public sge::image::exception
{
public:
	SGE_IMAGE_SYMBOL
	file_exception(
		sge::image::optional_path const &,
		fcppt::string const &
	);
};

}
}

#endif
