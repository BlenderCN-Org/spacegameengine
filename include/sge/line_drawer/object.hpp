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


#ifndef SGE_LINE_DRAWER_OBJECT_HPP_INCLUDED
#define SGE_LINE_DRAWER_OBJECT_HPP_INCLUDED

#include <sge/line_drawer/line_sequence.hpp>
#include <sge/line_drawer/scoped_lock_fwd.hpp>
#include <sge/line_drawer/symbol.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/state/core/blend/object_unique_ptr.hpp>
#include <sge/renderer/vertex/buffer_unique_ptr.hpp>
#include <sge/renderer/vertex/declaration_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace line_drawer
{
class object
{
FCPPT_NONCOPYABLE(
	object);
public:
	SGE_LINE_DRAWER_SYMBOL explicit
	object(
		sge::renderer::device::core &);

	SGE_LINE_DRAWER_SYMBOL void
	render(
		sge::renderer::context::core &);

	SGE_LINE_DRAWER_SYMBOL ~object();
private:
	friend class sge::line_drawer::scoped_lock;

	sge::renderer::device::core &renderer_;
	sge::renderer::vertex::declaration_unique_ptr const vertex_declaration_;
	sge::renderer::state::core::blend::object_unique_ptr const blend_state_;
	sge::renderer::vertex::buffer_unique_ptr vb_;
	line_sequence lines_;

	void
	lock();

	void
	unlock();
};
}
}

#endif
