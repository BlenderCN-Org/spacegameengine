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


#include <sge/renderer/context/ffp.hpp>
#include <sge/scenic/render_context/base.hpp>
#include <sge/scenic/render_context/ffp/manager.hpp>
#include <sge/scenic/render_context/ffp/object.hpp>
#include <fcppt/make_unique_ptr_fcppt.hpp>
#include <fcppt/unique_ptr_to_base.hpp>


sge::scenic::render_context::ffp::manager::manager(
	sge::renderer::device::ffp &_renderer,
	sge::renderer::vertex::declaration &_vertex_declaration)
:
	renderer_(
		_renderer),
	vertex_declaration_(
		_vertex_declaration)
{
}

sge::scenic::render_context::base_unique_ptr
sge::scenic::render_context::ffp::manager::create_context(
	sge::renderer::context::core &_context)
{
	return
		fcppt::unique_ptr_to_base<
			sge::scenic::render_context::base
		>(
			fcppt::make_unique_ptr_fcppt<sge::scenic::render_context::ffp::object>(
				*this,
				dynamic_cast<sge::renderer::context::ffp &>(
					_context)));
}

sge::scenic::render_context::ffp::manager::~manager()
{
}
