/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/d3d9/texture/mipmap/auto_generate_usage.hpp>
#include <sge/renderer/texture/mipmap/auto_generate.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/assert/unreachable.hpp>


sge::d3d9::usage const
sge::d3d9::texture::mipmap::auto_generate_usage(
	sge::renderer::texture::mipmap::auto_generate const _value
)
{
	switch(
		_value
	)
	{
	case sge::renderer::texture::mipmap::auto_generate::yes:
		return
			fcppt::strong_typedef_construct_cast<
				sge::d3d9::usage
			>(
				D3DUSAGE_AUTOGENMIPMAP
			);
	case sge::renderer::texture::mipmap::auto_generate::no:
		return
			sge::d3d9::usage(
				0u
			);
	}

	FCPPT_ASSERT_UNREACHABLE;
}
