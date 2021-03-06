/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_RENDERER_DISPLAY_MODE_COMPARISON_HPP_INCLUDED
#define SGE_RENDERER_DISPLAY_MODE_COMPARISON_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/display_mode/object_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace display_mode
{

/**
\brief Compares every member of a display mode using ==

Compares \a mode1 to \a mode2 using == on every member.

\return Whether \a mode1 and \a mode2 are equal
*/
SGE_RENDERER_DETAIL_SYMBOL
bool
operator==(
	sge::renderer::display_mode::object const &mode1,
	sge::renderer::display_mode::object const &mode2
);

/**
\brief Compares every member of a display mode using !=

Compares \a mode1 to \a mode2 using != on every member.

\return Whether \a mode1 and \a mode2 are equal
*/
SGE_RENDERER_DETAIL_SYMBOL
bool
operator!=(
	sge::renderer::display_mode::object const &mode1,
	sge::renderer::display_mode::object const &mode2
);

}
}
}

#endif
