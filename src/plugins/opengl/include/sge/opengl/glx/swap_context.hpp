/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_OPENGL_GLX_SWAP_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_GLX_SWAP_CONTEXT_HPP_INCLUDED

#include <sge/opengl/context/system/base.hpp>
#include <sge/opengl/context/system/id.hpp>
#include <sge/opengl/glx/proc_context_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <GL/glx.h>
#include <X11/Xlib.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace glx
{

class swap_context
:
	public sge::opengl::context::system::base
{
	FCPPT_NONCOPYABLE(
		swap_context
	);
public:
	typedef sge::opengl::glx::proc_context const &parameter;

	explicit
	swap_context(
		parameter
	);

	~swap_context()
	override;

	bool
	swap_interval_supported() const;

	typedef
	int(
		*glx_swap_interval_sgi
	)(
		int
	);

	typedef
	void(
		*glx_swap_interval_ext
	)(
		Display *,
		GLXDrawable,
		int
	);

	glx_swap_interval_sgi
	swap_interval_sgi() const;

	glx_swap_interval_ext
	swap_interval_ext() const;

	static sge::opengl::context::system::id const static_id;
private:
	glx_swap_interval_sgi swap_interval_sgi_;

	glx_swap_interval_ext swap_interval_ext_;
};

}
}
}

#endif
