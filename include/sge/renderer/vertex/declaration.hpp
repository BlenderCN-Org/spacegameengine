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


#ifndef SGE_RENDERER_VERTEX_DECLARATION_HPP_INCLUDED
#define SGE_RENDERER_VERTEX_DECLARATION_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{
namespace vertex
{

/**
\brief A dynamic representation of a vertex format

In order to activate vertex buffers, the corresponding vertex declaration needs
to be set first.

\see sge::renderer::device::create_vertex_declaration

\see sge::renderer::device::vertex_declaration
*/
class SGE_CORE_DETAIL_CLASS_SYMBOL declaration
{
	FCPPT_NONCOPYABLE(
		declaration
	);
protected:
	SGE_RENDERER_DETAIL_SYMBOL
	declaration();
public:
	SGE_RENDERER_DETAIL_SYMBOL
	virtual
	~declaration() = 0;
};

}
}
}

#endif
