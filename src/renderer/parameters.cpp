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


#include <sge/renderer/depth_stencil_buffer.hpp>
#include <sge/renderer/multi_samples.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/screen_mode.hpp>
#include <sge/renderer/vsync.hpp>


sge::renderer::parameters::parameters(
	sge::renderer::screen_mode const &_screen_mode,
	sge::renderer::depth_stencil_buffer::type const _depth_stencil_buffer,
	sge::renderer::vsync::type const _vsync,
	sge::renderer::multi_samples const _samples
)
:
	screen_mode_(
		_screen_mode
	),
	depth_stencil_buffer_(
		_depth_stencil_buffer
	),
	vsync_(
		_vsync
	),
	samples_(
		_samples
	)
{
}

sge::renderer::screen_mode const &
sge::renderer::parameters::screen_mode() const
{
	return screen_mode_;
}

sge::renderer::depth_stencil_buffer::type
sge::renderer::parameters::depth_stencil_buffer() const
{
	return depth_stencil_buffer_;
}

sge::renderer::vsync::type
sge::renderer::parameters::vsync() const
{
	return vsync_;
}

sge::renderer::multi_samples const
sge::renderer::parameters::samples() const
{
	return samples_;
}
