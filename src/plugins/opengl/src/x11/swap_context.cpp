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


#include <sge/opengl/context/system/base.hpp>
#include <sge/opengl/context/system/id.hpp>
#include <sge/opengl/context/system/make_id.hpp>
#include <sge/opengl/glx/proc_address.hpp>
#include <sge/opengl/x11/swap_context.hpp>
#include <fcppt/null_ptr.hpp>


sge::opengl::x11::swap_context::swap_context(
	sge::opengl::x11::swap_context::parameter _proc_context
)
:
	sge::opengl::context::system::base(),
	swap_interval_sgi_(
		reinterpret_cast<
			glx_swap_interval_sgi
		>(
			sge::opengl::glx::proc_address(
				_proc_context,
				"glXSwapIntervalSGI"
			)
		)
	),
	swap_interval_ext_(
		reinterpret_cast<
			glx_swap_interval_ext
		>(
			sge::opengl::glx::proc_address(
				_proc_context,
				"glXSwapIntervalEXT"
			)
		)
	)

{
}

sge::opengl::x11::swap_context::~swap_context()
{
}

bool
sge::opengl::x11::swap_context::swap_interval_supported() const
{
	return
		swap_interval_sgi_
		!=
		fcppt::null_ptr()
		||
		swap_interval_ext_
		!=
		fcppt::null_ptr()
		;
}

sge::opengl::x11::swap_context::glx_swap_interval_sgi
sge::opengl::x11::swap_context::swap_interval_sgi() const
{
	return swap_interval_sgi_;
}

sge::opengl::x11::swap_context::glx_swap_interval_ext
sge::opengl::x11::swap_context::swap_interval_ext() const
{
	return swap_interval_ext_;
}

sge::opengl::context::system::id const
sge::opengl::x11::swap_context::static_id(
	sge::opengl::context::system::make_id()
);
