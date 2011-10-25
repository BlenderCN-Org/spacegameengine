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


#ifndef SGE_SRC_MODEL_OBJ_PARSE_STATE_HPP_INCLUDED
#define SGE_SRC_MODEL_OBJ_PARSE_STATE_HPP_INCLUDED

#include <sge/model/obj/mesh_sequence.hpp>
#include <sge/model/obj/normal_sequence.hpp>
#include <sge/model/obj/texcoord_sequence.hpp>
#include <sge/model/obj/vertex_sequence.hpp>
#include <sge/src/model/obj/parse_state_fwd.hpp>


namespace sge
{
namespace model
{
namespace obj
{

struct parse_state
{
	obj::vertex_sequence vertices_;

	obj::texcoord_sequence texcoords_;

	obj::normal_sequence normals_;

	obj::mesh_sequence meshes_;
};

}
}
}

#endif
