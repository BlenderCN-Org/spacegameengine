/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RENDERER_DEFAULT_TRANSFORMABLE_HPP_INCLUDED
#define SGE_RENDERER_DEFAULT_TRANSFORMABLE_HPP_INCLUDED

#include "transformable.hpp"
#include "../math/matrix_util.hpp"

namespace sge
{

class default_transformable {
public:
	default_transformable(
		const renderer_ptr rend,
		const math::space_matrix& internal,
		const math::space_matrix& projection,
		const math::space_matrix& transform
			= math::matrix_identity());
	void internal_transformation(const math::space_matrix&);
	void transform(const math::space_matrix&);
	void projection(const math::space_matrix&);
	void set_matrices();
private:
	renderer_ptr rend;
	math::space_matrix internal_matrix_,
			   projection_,
	                   transform_;
};

}

#endif
