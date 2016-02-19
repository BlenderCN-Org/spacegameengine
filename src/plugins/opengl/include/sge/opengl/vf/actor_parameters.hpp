/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_OPENGL_VF_ACTOR_PARAMETERS_HPP_INCLUDED
#define SGE_OPENGL_VF_ACTOR_PARAMETERS_HPP_INCLUDED

#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/vf/actor_parameters_fwd.hpp>
#include <sge/renderer/vf/dynamic/offset.hpp>
#include <sge/renderer/vf/dynamic/stride.hpp>
#include <fcppt/nonassignable.hpp>


namespace sge
{
namespace opengl
{
namespace vf
{

class actor_parameters
{
	FCPPT_NONASSIGNABLE(
		actor_parameters
	);
public:
	actor_parameters(
		sge::renderer::vf::dynamic::stride,
		sge::renderer::vf::dynamic::offset,
		sge::opengl::context::object &
	);

	sge::renderer::vf::dynamic::stride
	stride() const;

	sge::renderer::vf::dynamic::offset
	offset() const;

	sge::opengl::context::object &
	context() const;
private:
	sge::renderer::vf::dynamic::stride const stride_;

	sge::renderer::vf::dynamic::offset const offset_;

	opengl::context::object &context_;
};

}
}
}

#endif
