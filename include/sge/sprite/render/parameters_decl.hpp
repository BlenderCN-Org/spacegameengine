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


#ifndef SGE_SPRITE_RENDER_PARAMETERS_DECL_HPP_INCLUDED
#define SGE_SPRITE_RENDER_PARAMETERS_DECL_HPP_INCLUDED

#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <sge/sprite/render/parameters_fwd.hpp>
#include <sge/sprite/state/render_context.hpp>
#include <fcppt/nonassignable.hpp>


namespace sge
{
namespace sprite
{
namespace render
{

template<
	typename StateOptions
>
class parameters
{
	FCPPT_NONASSIGNABLE(
		parameters
	);
public:
	typedef
	sge::sprite::state::render_context<
		StateOptions
	>
	render_context_type;

	parameters(
		render_context_type &,
		sge::renderer::vertex::declaration const &
	);

	render_context_type &
	render_context() const;

	sge::renderer::vertex::declaration const &
	vertex_declaration() const;
private:
	render_context_type &render_context_;

	sge::renderer::vertex::declaration const &vertex_declaration_;
};

}
}
}

#endif
