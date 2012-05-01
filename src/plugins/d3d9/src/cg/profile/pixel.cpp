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


#include <sge/cg/check_state.hpp>
#include <sge/cg/profile/object.hpp>
#include <sge/cg/profile/object_unique_ptr.hpp>
#include <sge/d3d9/cg/scoped_device_fwd.hpp>
#include <sge/d3d9/cg/profile/pixel.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cg.h>
#include <Cg/cgD3D9.h>
#include <fcppt/config/external_end.hpp>


sge::cg::profile::object_unique_ptr
sge::d3d9::cg::profile::pixel(
	sge::d3d9::cg::scoped_device const &
)
{
	CGprofile const ret(
		::cgD3D9GetLatestPixelProfile()
	);

	SGE_CG_CHECK_STATE(
		FCPPT_TEXT("cgD3D9GetLatestPixelProfile failed"),
		sge::renderer::exception
	)

	FCPPT_ASSERT_ERROR(
		ret
		!=
		CG_PROFILE_UNKNOWN
	);

	return
		fcppt::make_unique_ptr<
			sge::cg::profile::object
		>(
			ret
		);
}
