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


#ifndef SGE_RENDERER_VERTEX_SCOPED_BUFFER_HPP_INCLUDED
#define SGE_RENDERER_VERTEX_SCOPED_BUFFER_HPP_INCLUDED

#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/vertex/buffer_fwd.hpp>
#include <sge/renderer/vertex/scoped_buffer_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{
namespace vertex
{

/**
\brief A scoped vertex buffer block

Sets a vertex buffer in the constructor and unsets it in the destructor.
*/
class scoped_buffer
{
	FCPPT_NONCOPYABLE(
		scoped_buffer
	);
public:
	/**
	\brief Sets a vertex buffer

	Sets \a vertex_buffer for \a device

	\param context The context to set the vertex buffer for

	\param vertex_buffer The vertex buffer to set

	\warning The behaviour is undefined if the vertex buffer is already set

	\warning The behaviour is undefined if the corresponding vertex
	declaration is not set
	*/
	SGE_RENDERER_DETAIL_SYMBOL
	scoped_buffer(
		sge::renderer::context::core &context,
		sge::renderer::vertex::buffer const &vertex_buffer
	);

	/**
	\brief Unsets the vertex buffer

	\warning The behaviour is undefined if the vertex buffer was already
	unset
	*/
	SGE_RENDERER_DETAIL_SYMBOL
	~scoped_buffer();
private:
	sge::renderer::context::core &context_;

	sge::renderer::vertex::buffer const &vertex_buffer_;
};

}
}
}

#endif
