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


#ifndef SGE_OPENGL_BACKEND_DUMMY_HPP_INCLUDED
#define SGE_OPENGL_BACKEND_DUMMY_HPP_INCLUDED

#include <sge/opengl/backend/context_scoped_ptr.hpp>
#include <sge/opengl/backend/scoped_current.hpp>
#include <sge/opengl/backend/system_fwd.hpp>
#include <awl/system/object_fwd.hpp>
#include <awl/visual/object_scoped_ptr.hpp>
#include <awl/window/object_scoped_ptr.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace backend
{

class dummy
{
	FCPPT_NONCOPYABLE(
		dummy
	);
public:
	dummy(
		awl::system::object &,
		sge::opengl::backend::system &
	);

	~dummy();
private:
	awl::visual::object_scoped_ptr const awl_visual_;

	awl::window::object_scoped_ptr const awl_window_;

	sge::opengl::backend::context_scoped_ptr const context_;

	sge::opengl::backend::scoped_current const scoped_current_;
};

}
}
}

#endif
