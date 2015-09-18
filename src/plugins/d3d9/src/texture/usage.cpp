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


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/usage.hpp>
#include <sge/d3d9/texture/usage.hpp>
#include <sge/d3d9/convert/resource_flags.hpp>
#include <sge/renderer/resource_flags.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/texture/capabilities.hpp>
#include <fcppt/container/bitfield/operators.hpp>


sge::d3d9::usage const
sge::d3d9::texture::usage(
	sge::renderer::resource_flags_field const &_flags,
	sge::renderer::texture::capabilities_field const &_caps
)
{
	DWORD ret(
		0u
	);

	if(
		_flags & sge::renderer::resource_flags::dynamic
	)
		ret |= D3DUSAGE_DYNAMIC;

	if(
		_caps & sge::renderer::texture::capabilities::render_target
	)
		ret |= D3DUSAGE_RENDERTARGET;

	return
		sge::d3d9::usage(
			ret
		);
}
