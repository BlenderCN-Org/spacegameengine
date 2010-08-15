/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_XCB_WINDOW_ATTRIBUTE_ENUM_TO_MASK_HPP_INCLUDED
#define SGE_XCB_WINDOW_ATTRIBUTE_ENUM_TO_MASK_HPP_INCLUDED

#include <sge/xcb/window/attribute/enum.hpp>
#include <sge/xcb/value_mask.hpp>
#include <sge/xcb/symbol.hpp>

namespace sge
{
namespace xcb
{
namespace window
{
namespace attribute
{

SGE_XCB_SYMBOL
xcb::value_mask const
enum_to_mask(
	enum_::type
);

}
}
}
}

#endif
