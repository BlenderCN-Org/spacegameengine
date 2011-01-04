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


#include <sge/input/cursor/button_event.hpp>
#include <sge/input/cursor/move_event.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/object_ptr.hpp>
#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/input/mouse/axis_event.hpp>
#include <sge/input/mouse/button_event.hpp>
#include <sge/input/mouse/device.hpp>
#include <sge/input/mouse/device_ptr.hpp>
#include <sge/input/processor.hpp>
#include <sge/input/processor_ptr.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/input_helper_field.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/window.hpp>
#include <sge/window/dim_type.hpp>
#include <sge/window/instance.hpp>
#include <sge/window/simple_parameters.hpp>
#include <awl/mainloop/dispatcher.hpp>
#include <awl/mainloop/io_service.hpp>
#include <awl/mainloop/asio/create_io_service_base.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/signal/connection_manager.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/signal/shared_connection.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/text.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <boost/foreach.hpp>
#include <cassert>
#include <cstdlib>

namespace
{

class mouse_listener
{
	FCPPT_NONCOPYABLE(
		mouse_listener
	)
public:
	explicit mouse_listener(
		sge::input::mouse::device_ptr
	);
private:
	void
	on_button_event(
		sge::input::mouse::button_event const &
	);

	void
	on_axis_event(
		sge::input::mouse::axis_event const &
	);

	fcppt::signal::connection_manager const connections_;
};

class cursor_listener
{
	FCPPT_NONCOPYABLE(
		cursor_listener
	)
public:
	explicit cursor_listener(
		sge::input::cursor::object_ptr
	);
private:
	void
	on_button_event(
		sge::input::cursor::button_event const &
	);

	void
	on_move_event(
		sge::input::cursor::move_event const &
	);

	fcppt::signal::connection_manager const connections_;
};

class device_manager
{
	FCPPT_NONCOPYABLE(
		device_manager
	)
public:
	explicit device_manager(
		sge::input::processor_ptr
	);
private:	
	void
	on_mouse_add(
		sge::input::mouse::device_ptr
	);

	void
	on_mouse_remove(
		sge::input::mouse::device_ptr
	);

	typedef boost::ptr_map<
		sge::input::mouse::device_ptr,
		mouse_listener
	> mouse_listener_map;

	fcppt::signal::connection_manager const connections_;

	mouse_listener_map mouse_listeners_;
};

}

int main()
try
{
	awl::mainloop::io_service_ptr const io_service(
		awl::mainloop::asio::create_io_service_base()
	);

	sge::systems::instance sys(
		sge::systems::list()
		(
			sge::systems::window(
				sge::window::simple_parameters(
					FCPPT_TEXT("sge input example"),
					sge::window::dim_type(
						1024,
						768
					)
				)
			)
			.io_service(
				io_service
			)
		)
		(
			sge::systems::input(
				sge::systems::input_helper_field()
			)
		)
	);

	sys.window()->show();

	::device_manager const manager(
		sys.input_processor()
	);

	fcppt::signal::scoped_connection const input_connection(
		sys.keyboard_collector()->key_callback(
			sge::input::keyboard::action(
				sge::input::keyboard::key_code::escape,
				std::tr1::bind(
					&awl::mainloop::dispatcher::stop,
					sys.window()->awl_dispatcher()
				)
			)
		)
	);

	io_service->run();
}
catch(
	fcppt::exception const &_exception
)
{
	fcppt::io::cerr
		<< _exception.string()
		<< FCPPT_TEXT('\n');
	
	return EXIT_FAILURE;
}

namespace
{

mouse_listener::mouse_listener(
	sge::input::mouse::device_ptr const _device
)
:
	connections_(
		fcppt::assign::make_container<
			fcppt::signal::connection_manager::container		
		>(
			fcppt::signal::shared_connection(
				_device->button_callback(
					std::tr1::bind(
						&mouse_listener::on_button_event,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				_device->axis_callback(
					std::tr1::bind(
						&mouse_listener::on_axis_event,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
	)
{
}

void
mouse_listener::on_button_event(
	sge::input::mouse::button_event const &_event
)
{
}

void
mouse_listener::on_axis_event(
	sge::input::mouse::axis_event const &_event
)
{
}


cursor_listener::cursor_listener(
	sge::input::cursor::object_ptr const _device
)
:
	connections_(
		fcppt::assign::make_container<
			fcppt::signal::connection_manager::container		
		>(
			fcppt::signal::shared_connection(
				_device->button_callback(
					std::tr1::bind(
						&cursor_listener::on_button_event,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				_device->move_callback(
					std::tr1::bind(
						&cursor_listener::on_move_event,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
	)
{
}

void
cursor_listener::on_button_event(
	sge::input::cursor::button_event const &_event
)
{
}

void
cursor_listener::on_move_event(
	sge::input::cursor::move_event const &_event
)
{
}


device_manager::device_manager(
	sge::input::processor_ptr const _processor
)
:
	connections_(
		fcppt::assign::make_container<
			fcppt::signal::connection_manager::container		
		>(
			fcppt::signal::shared_connection(
				_processor->mouse_discover_callback(
					std::tr1::bind(
						&device_manager::on_mouse_add,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				_processor->mouse_remove_callback(
					std::tr1::bind(
						&device_manager::on_mouse_remove,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
	),
	mouse_listeners_()
{
	BOOST_FOREACH(
		sge::input::mouse::device_vector::value_type const mouse,
		_processor->mice()
	)
		this->on_mouse_add(
			mouse
		);
}

void
device_manager::on_mouse_add(
	sge::input::mouse::device_ptr const _device
)
{
	assert(
		fcppt::container::ptr::insert_unique_ptr_map(
			mouse_listeners_,
			_device,
			fcppt::make_unique_ptr<
				::mouse_listener
			>(
				_device
			)
		).second
		== true
	);
}

void
device_manager::on_mouse_remove(
	sge::input::mouse::device_ptr const _device
)
{
	assert(
		mouse_listeners_.erase(
			_device
		) == 1u
	);
}

}
