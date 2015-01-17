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


#include <sge/opengl/common.hpp>
#include <sge/opengl/state/convert/fog_mode.hpp>
#include <sge/renderer/state/ffp/fog/mode.hpp>
#include <fcppt/assert/unreachable.hpp>


GLint
sge::opengl::state::convert::fog_mode(
	sge::renderer::state::ffp::fog::mode const _mode
)
{
	switch(
		_mode
	)
	{
	case sge::renderer::state::ffp::fog::mode::linear:
		return GL_LINEAR;
	case sge::renderer::state::ffp::fog::mode::exp:
		return GL_EXP;
	case sge::renderer::state::ffp::fog::mode::exp2:
		return GL_EXP2;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
