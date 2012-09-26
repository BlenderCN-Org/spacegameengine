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


#ifndef SGE_SCENIC_RENDER_CONTEXT_LIGHT_DIRECTIONAL_HPP_INCLUDED
#define SGE_SCENIC_RENDER_CONTEXT_LIGHT_DIRECTIONAL_HPP_INCLUDED

#include <sge/scenic/symbol.hpp>
#include <sge/scenic/render_context/light/direction.hpp>
#include <sge/scenic/render_context/light/directional_fwd.hpp>


namespace sge
{
namespace scenic
{
namespace render_context
{
namespace light
{
class directional
{
public:
	SGE_SCENIC_SYMBOL
	explicit
	directional(
		sge::scenic::render_context::light::direction const &);

	SGE_SCENIC_SYMBOL
	sge::scenic::render_context::light::direction const &
	direction() const;
private:
	sge::scenic::render_context::light::direction direction_;
};
}
}
}
}

#endif
