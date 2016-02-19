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


#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/context/make_id.hpp>
#include <sge/opengl/target/context.hpp>
#include <sge/opengl/target/optional_base_ref.hpp>


sge::opengl::target::context::context()
:
	sge::opengl::context::base(),
	last_target_()
{
}

sge::opengl::target::context::~context()
{
}

sge::opengl::target::optional_base_ref const &
sge::opengl::target::context::last_target()
{
	return
		last_target_;
}

void
sge::opengl::target::context::last_target(
	sge::opengl::target::optional_base_ref const &_target
)
{
	last_target_ =
		_target;
}

sge::opengl::context::id const
sge::opengl::target::context::static_id(
	sge::opengl::context::make_id()
);
