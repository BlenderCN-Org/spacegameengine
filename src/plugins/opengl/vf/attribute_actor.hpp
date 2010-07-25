/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENGL_VF_ATTRIBUTE_ACTOR_HPP_INCLUDED
#define SGE_OPENGL_VF_ATTRIBUTE_ACTOR_HPP_INCLUDED

#include "pointer_actor.hpp"
#include "client_state_combiner_fwd.hpp"
#include "attribute_context_fwd.hpp"
#include "actor_parameters_fwd.hpp"
#include "pointer.hpp"
#include "../context/object_fwd.hpp"
#include <sge/renderer/vf/dynamic/unspecified_fwd.hpp>

namespace sge
{
namespace opengl
{
namespace vf
{

class attribute_actor
:
	public pointer_actor
{
public:
	explicit attribute_actor(
		actor_parameters const &,
		renderer::vf::dynamic::unspecified const &
	);
private:
	void
	operator()(
		client_state_combiner &,
		vf::pointer
	) const;

	void
	unuse(
		client_state_combiner &
	) const;

	vf::attribute_context &context_;

	GLint const elements_;

	GLenum const format_;

	GLint const index_;
};

}
}
}

#endif
