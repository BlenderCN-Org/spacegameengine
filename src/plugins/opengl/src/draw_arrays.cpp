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


#include <sge/opengl/draw_arrays.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/convert/nonindexed_primitive.hpp>
#include <sge/log/global.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/warning.hpp>


void
sge::opengl::draw_arrays(
	renderer::first_vertex const _first_vertex,
	renderer::vertex_count const _num_vertices,
	renderer::nonindexed_primitive_type::type const _ptype
)
{
	if(
		_num_vertices.get() == 0u
	)
	{
		FCPPT_LOG_WARNING(
			sge::log::global(),
			fcppt::log::_
				<< FCPPT_TEXT("Empty device::render() call. ")
				<< FCPPT_TEXT("vertex_count was 0.")
		);

		return;
	}

	::glDrawArrays(
		convert::nonindexed_primitive(
			_ptype
		),
		static_cast<
			GLsizei
		>(
			_first_vertex.get()
		),
		static_cast<
			GLint
		>(
			_num_vertices.get()
		)
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glDrawArrays failed"),
		sge::renderer::exception
	)
}
