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


#include <sge/renderer/bit_depth.hpp>
#include <sge/renderer/depth_stencil_buffer.hpp>
#include <sge/renderer/optional_bit_count.hpp>
#include <sge/renderer/stencil_buffer_bits.hpp>
#include <fcppt/assert/unreachable.hpp>


sge::renderer::optional_bit_count const
sge::renderer::stencil_buffer_bits(
	sge::renderer::depth_stencil_buffer::type const _type
)
{
	switch(
		_type
	)
	{
	case sge::renderer::depth_stencil_buffer::off:
	case sge::renderer::depth_stencil_buffer::d16:
	case sge::renderer::depth_stencil_buffer::d24:
	case sge::renderer::depth_stencil_buffer::d32:
		return
			sge::renderer::optional_bit_count();
	case sge::renderer::depth_stencil_buffer::d24s8:
		return
			sge::renderer::optional_bit_count(
				sge::renderer::bit_count(
					8u
				)
			);
	}

	FCPPT_ASSERT_UNREACHABLE;
}
