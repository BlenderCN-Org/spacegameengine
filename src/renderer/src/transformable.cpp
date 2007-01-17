/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include "../transformable.hpp"

sge::transformable::transformable(const renderer_ptr rend, const math::space_matrix& internal, const math::space_matrix& _projection, const math::space_matrix& _transform)
 : rend(rend),
   _internal_matrix(internal),
   _projection(_projection),
   _transform(_transform)
{}

void sge::transformable::internal_transformation(const math::space_matrix& m)
{
	_internal_matrix = m;
}

void sge::transformable::transform(const math::space_matrix& m)
{
	_transform = m;
}

void sge::transformable::projection(const math::space_matrix& m)
{
	_projection = m;
}

void sge::transformable::set_matrices()
{
	rend->transform(_internal_matrix * _transform);
	rend->projection(_projection);
}

