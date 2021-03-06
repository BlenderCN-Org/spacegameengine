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


#ifndef SGE_X11INPUT_FOCUS_OBJECT_HPP_INCLUDED
#define SGE_X11INPUT_FOCUS_OBJECT_HPP_INCLUDED

#include <sge/input/focus/object.hpp>
#include <sge/input/key/code_fwd.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/x11input/device/id.hpp>
#include <sge/x11input/event/window_demuxer_fwd.hpp>
#include <sge/x11input/focus/object_fwd.hpp>
#include <sge/x11input/key/repeated.hpp>
#include <sge/x11input/xim/const_optional_method_ref_fwd.hpp>
#include <sge/x11input/xim/context_fwd.hpp>
#include <awl/backends/x11/window/base_fwd.hpp>
#include <awl/backends/x11/window/object_fwd.hpp>
#include <awl/event/base_unique_ptr.hpp>
#include <awl/event/connection_unique_ptr.hpp>
#include <awl/event/container.hpp>
#include <fcppt/enable_shared_from_this_decl.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_decl.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/optional/object_decl.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace x11input
{
namespace focus
{

class object
:
	public
		sge::input::focus::object,
	public
		fcppt::enable_shared_from_this<
			sge::x11input::focus::object
		 >
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	object(
		sge::window::object &,
		fcppt::log::object &,
		awl::backends::x11::window::object &,
		sge::x11input::device::id,
		sge::x11input::event::window_demuxer &,
		sge::x11input::xim::const_optional_method_ref const &
	);

	~object()
	override;
private:
	sge::window::object &
	window() const
	override;

	awl::event::container
	on_event(
		XIDeviceEvent const &
	);

	awl::event::container
	on_key_press(
		XIDeviceEvent const &
	);

	awl::event::base_unique_ptr
	on_key_release(
		XIDeviceEvent const &
	);

	awl::event::base_unique_ptr
	on_focus_in();

	awl::event::base_unique_ptr
	on_focus_out();

	awl::event::base_unique_ptr
	process_key_down(
		sge::x11input::key::repeated,
		sge::input::key::code
	);

	sge::window::object &sge_window_;

	fcppt::log::object &log_;

	awl::backends::x11::window::base const &window_;

	typedef
	fcppt::unique_ptr<
		sge::x11input::xim::context
	>
	xim_context_unique_ptr;

	typedef
	fcppt::optional::object<
		xim_context_unique_ptr
	>
	optional_xim_context_unique_ptr;

	optional_xim_context_unique_ptr const xim_context_;

	typedef
	fcppt::optional::object<
		awl::event::connection_unique_ptr
	>
	optional_connection_unique_ptr;

	optional_connection_unique_ptr const mask_connection_;

	fcppt::signal::auto_connection const event_connection_;
};

}
}
}

#endif
