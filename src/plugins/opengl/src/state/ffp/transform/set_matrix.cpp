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


#include <sge/opengl/call.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/state/ffp/transform/context.hpp>
#include <sge/opengl/state/ffp/transform/set_matrix.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/matrix4.hpp>
#include <fcppt/maybe.hpp>
#include <fcppt/text.hpp>


void
sge::opengl::state::ffp::transform::set_matrix(
	sge::opengl::context::system::object &_context,
	sge::renderer::matrix4 const &_matrix
)
{
	fcppt::maybe(
		sge::opengl::context::use<
			sge::opengl::state::ffp::transform::context
		>(
			_context
		).load_transpose_matrix_f(),
		[
			&_matrix
		]{
			sge::opengl::call(
				::glLoadMatrixf,
				_matrix.data()
			);

			SGE_OPENGL_CHECK_STATE(
				FCPPT_TEXT("glLoadMatrixf failed"),
				sge::renderer::exception
			)
		},
		[
			&_matrix
		](
			sge::opengl::state::ffp::transform::context::gl_load_transpose_matrix_f _load_matrix
		)
		{
			_load_matrix(
				_matrix.data()
			);

			SGE_OPENGL_CHECK_STATE(
				FCPPT_TEXT("glLoadTransposeMatrixf failed"),
				sge::renderer::exception
			)
		}
	);
}
