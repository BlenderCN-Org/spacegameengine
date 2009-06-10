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


#ifndef SGE_OPENGL_VF_CLIENT_STATE_COMBINER_HPP_INCLUDED
#define SGE_OPENGL_VF_CLIENT_STATE_COMBINER_HPP_INCLUDED

#include "client_state.hpp"
#include <sge/noncopyable.hpp>

namespace sge
{
namespace opengl
{
namespace vf
{

class client_state_combiner {
	SGE_NONCOPYABLE(client_state_combiner)
public:
	explicit client_state_combiner(
		client_state const &old_states);
	void enable(
		GLenum);
	void enable_attribute(
		GLuint);
	~client_state_combiner();
private:
	client_state const old_states;
	client_state new_states;
};

}
}
}

#endif
