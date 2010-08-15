/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/renderer/nonindexed_primitive_count.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

sge::renderer::size_type
sge::renderer::nonindexed_primitive_count(
	size_type const vertex_count,
	nonindexed_primitive_type::type const prim
)
{
	switch(prim)
	{
	case nonindexed_primitive_type::point:
		return vertex_count;
	case nonindexed_primitive_type::line:
		if(vertex_count <= 1)
			throw exception(
				FCPPT_TEXT("nonindexed_primitive_count(): line needs at least two vertices!")
			);
		return vertex_count / 2;
	
	case nonindexed_primitive_type::line_strip:
		if(vertex_count <= 1)
			throw exception(
				FCPPT_TEXT("nonindexed_primitive_count(): line_strip needs at least two vertices!")
			);
		return vertex_count - 1;
	case nonindexed_primitive_type::triangle_strip:
	case nonindexed_primitive_type::triangle_fan:
		if(vertex_count <= 2)
			throw exception(
				FCPPT_TEXT("nonindexed_primitive_count(): triangle_fan and triangle_strip need at least three vertices!")
			);
		return vertex_count - 2;
	case nonindexed_primitive_type::triangle:
		if(vertex_count % 3)
			throw exception(
				FCPPT_TEXT("nonindexed_primitive_count(): triangle needs a multiple of three vertices!")
			);
		return vertex_count / 3;
	}

	throw renderer::exception(
		FCPPT_TEXT("Invalid nonindexed_primitive_type!")
	);
}
