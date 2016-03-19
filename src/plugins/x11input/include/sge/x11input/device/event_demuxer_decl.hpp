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


#ifndef SGE_X11INPUT_DEVICE_EVENT_DEMUXER_DECL_HPP_INCLUDED
#define SGE_X11INPUT_DEVICE_EVENT_DEMUXER_DECL_HPP_INCLUDED

#include <sge/x11input/device/event_demuxer_fwd.hpp>
#include <sge/x11input/device/id.hpp>
#include <awl/backends/x11/system/event/object_fwd.hpp>
#include <awl/backends/x11/system/event/opcode.hpp>
#include <awl/backends/x11/system/event/processor_fwd.hpp>
#include <awl/backends/x11/system/event/type.hpp>
#include <awl/backends/x11/window/object_fwd.hpp>
#include <fcppt/function_impl.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/strong_typedef_std_hash.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_decl.hpp>
#include <fcppt/signal/unregister/base_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <unordered_map>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace x11input
{
namespace device
{

template<
	typename Event
>
class event_demuxer
{
	FCPPT_NONCOPYABLE(
		event_demuxer
	);

	typedef
	void
	signature(
		Event const &
	);
public:
	event_demuxer(
		awl::backends::x11::system::event::processor &,
		awl::backends::x11::system::event::opcode const &,
		awl::backends::x11::window::object const &
	);

	~event_demuxer();

	typedef
	fcppt::function<
		signature
	>
	callback;

	fcppt::signal::auto_connection
	register_callback(
		awl::backends::x11::system::event::type const &,
		sge::x11input::device::id const &,
		callback const &
	);

	void
	active(
		bool
	);
private:
	void
	on_event(
		awl::backends::x11::system::event::object const &
	);

	void
	unregister(
		device::id const &,
		awl::backends::x11::system::event::type
	);

	bool
	signal_remains(
		awl::backends::x11::system::event::type
	) const;

	typedef
	fcppt::signal::object<
		signature,
		fcppt::signal::unregister::base
	>
	signal;

	typedef
	std::pair<
		awl::backends::x11::system::event::type,
		sge::x11input::device::id
	>
	event_pair;

	// TODO: Why does the pair hash not work?
	typedef
	std::map<
		event_pair,
		signal
	>
	signal_map;

	typedef
	std::unordered_map<
		awl::backends::x11::system::event::type,
		fcppt::signal::auto_connection
	>
	connection_map;

	awl::backends::x11::system::event::processor &system_processor_;

	awl::backends::x11::system::event::opcode const opcode_;

	awl::backends::x11::window::object const &window_;

	connection_map connections_;

	signal_map signals_;
};

}
}
}

#endif
