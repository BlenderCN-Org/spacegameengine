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


#include <sge/renderer/parameters.hpp>

sge::renderer::parameters::parameters(
	renderer::optional_display_mode const &_display_mode,
	renderer::depth_buffer::type const _depth_buffer,
	renderer::stencil_buffer::type const _stencil_buffer,
	renderer::vsync::type const _vsync,
	renderer::multi_sample_type const _samples
)
:
	display_mode_(_display_mode),
	depth_buffer_(_depth_buffer),
	stencil_buffer_(_stencil_buffer),
	vsync_(_vsync),
	samples_(_samples)
{
}

sge::renderer::optional_display_mode const &
sge::renderer::parameters::display_mode() const
{
	return display_mode_;
}

sge::renderer::depth_buffer::type
sge::renderer::parameters::depth_buffer() const
{
	return depth_buffer_;
}

sge::renderer::stencil_buffer::type
sge::renderer::parameters::stencil_buffer() const
{
	return stencil_buffer_;
}

sge::renderer::vsync::type
sge::renderer::parameters::vsync() const
{
	return vsync_;
}

sge::renderer::multi_sample_type
sge::renderer::parameters::samples() const
{
	return samples_;
}
