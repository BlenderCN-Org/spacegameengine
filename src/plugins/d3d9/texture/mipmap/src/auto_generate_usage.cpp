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


#include "../auto_generate_usage.hpp"
#include "../../../d3dinclude.hpp"
#include <sge/renderer/texture/mipmap/auto_generate.hpp>
#include <fcppt/assert/unreachable.hpp>

sge::d3d9::usage const
sge::d3d9::texture::mipmap::auto_generate_usage(
	sge::renderer::texture::mipmap::auto_generate::type const _value
)
{
	switch(
		_value
	)
	{
	case renderer::texture::mipmap::auto_generate::yes:
		return
			d3d9::usage(
				D3DUSAGE_AUTOGENMIPMAP
			);
	case renderer::texture::mipmap::auto_generate::no:
		return
			d3d9::usage(
				0u
			);
	}

	FCPPT_ASSERT_UNREACHABLE
}
