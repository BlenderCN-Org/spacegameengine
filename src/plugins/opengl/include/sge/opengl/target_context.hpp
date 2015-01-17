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


#ifndef SGE_OPENGL_TARGET_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_TARGET_CONTEXT_HPP_INCLUDED

#include <sge/opengl/optional_target_base_ref.hpp>
#include <sge/opengl/context/device/base.hpp>
#include <sge/opengl/context/device/id.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{

class target_context
:
	public sge::opengl::context::device::base
{
	FCPPT_NONCOPYABLE(
		target_context
	);
public:
	target_context();

	~target_context()
	override;

	sge::opengl::optional_target_base_ref const &
	last_target();

	void
	last_target(
		sge::opengl::optional_target_base_ref const &
	);

	typedef void parameter;

	static sge::opengl::context::device::id const static_id;
private:
	sge::opengl::optional_target_base_ref last_target_;
};

}
}

#endif
