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


#ifndef SGE_MODEL_OBJ_FACE_POINT_HPP_INCLUDED
#define SGE_MODEL_OBJ_FACE_POINT_HPP_INCLUDED

#include <sge/model/obj/face_point_fwd.hpp>
#include <sge/model/obj/index.hpp>
#include <sge/model/obj/optional_index.hpp>
#include <sge/model/obj/symbol.hpp>


namespace sge
{
namespace model
{
namespace obj
{

struct face_point
{
	SGE_MODEL_OBJ_SYMBOL
	face_point();

	obj::index vertex_index_;

	obj::optional_index texcoord_index_;

	obj::optional_index normal_index_;
};

}
}
}

#endif
