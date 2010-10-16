/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_GUI_DETAIL_MANAGERS_MOUSE_HPP_INCLUDED
#define SGE_GUI_DETAIL_MANAGERS_MOUSE_HPP_INCLUDED

#include <sge/gui/dim.hpp>
#include <sge/gui/point.hpp>
#include <sge/gui/detail/submanager.hpp>
#include <sge/gui/cursor/base_ptr.hpp>
#include <sge/gui/widgets/fwd.hpp>
#include <sge/input/mouse/device_ptr.hpp>
#include <sge/input/mouse/axis_event_fwd.hpp>
#include <sge/input/mouse/button_event_fwd.hpp>
#include <sge/sprite/object.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

namespace sge
{
namespace gui
{
namespace detail
{
namespace managers
{
class mouse : public submanager
{
public:
	mouse(
		input::mouse::device_ptr,
		cursor::base_ptr);

	void resize(
		widgets::base &,
		dim const &);
	void reposition(
		widgets::base &,
		point const &);
	void add(widgets::base &);
	void update();
	void activation(widgets::base &,activation_state::type);
	void remove(widgets::base &);
	void recalculate_focus();
	void z(widgets::base &,depth_type);
private:
	typedef boost::ptr_vector<
		widgets::base,
		boost::view_clone_allocator> widget_container;

	widget_container widgets;
	fcppt::signal::scoped_connection const
		axis_connection,
		button_connection;
	cursor::base_ptr cursor_;
	widgets::base *focus;
	bool dirty_;

	void
	axis_callback(
		input::mouse::axis_event const &
	);

	void
	button_callback(
		input::mouse::button_event const &
	);

	widgets::base *recalculate_focus(widgets::base &w,point const &);
	widgets::base *do_recalculate_focus(widgets::base &,point const &);
};
}
}
}
}

#endif
