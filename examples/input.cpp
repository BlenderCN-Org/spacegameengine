/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/input/cursor/button_code_to_string.hpp>
#include <sge/input/cursor/button_event.hpp>
#include <sge/input/cursor/discover_callback.hpp>
#include <sge/input/cursor/discover_event.hpp>
#include <sge/input/cursor/manager.hpp>
#include <sge/input/cursor/move_event.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/remove_callback.hpp>
#include <sge/input/cursor/remove_event.hpp>
#include <sge/input/info/optional_string.hpp>
#include <sge/input/joypad/absolute_axis_event.hpp>
#include <sge/input/joypad/absolute_axis_info.hpp>
#include <sge/input/joypad/absolute_axis_info_container.hpp>
#include <sge/input/joypad/axis_code_to_string.hpp>
#include <sge/input/joypad/button_event.hpp>
#include <sge/input/joypad/button_info.hpp>
#include <sge/input/joypad/button_info_container.hpp>
#include <sge/input/joypad/device.hpp>
#include <sge/input/joypad/discover_callback.hpp>
#include <sge/input/joypad/discover_event.hpp>
#include <sge/input/joypad/info.hpp>
#include <sge/input/joypad/manager.hpp>
#include <sge/input/joypad/relative_axis_event.hpp>
#include <sge/input/joypad/relative_axis_info.hpp>
#include <sge/input/joypad/relative_axis_info_container.hpp>
#include <sge/input/joypad/remove_callback.hpp>
#include <sge/input/joypad/remove_event.hpp>
#include <sge/input/keyboard/char_event.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/discover_callback.hpp>
#include <sge/input/keyboard/discover_event.hpp>
#include <sge/input/keyboard/key_code_to_string.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/input/keyboard/key_repeat_event.hpp>
#include <sge/input/keyboard/manager.hpp>
#include <sge/input/keyboard/remove_callback.hpp>
#include <sge/input/keyboard/remove_event.hpp>
#include <sge/input/mouse/axis_code_to_string.hpp>
#include <sge/input/mouse/axis_event.hpp>
#include <sge/input/mouse/axis_info.hpp>
#include <sge/input/mouse/axis_info_container.hpp>
#include <sge/input/mouse/button_code_to_string.hpp>
#include <sge/input/mouse/button_event.hpp>
#include <sge/input/mouse/button_info.hpp>
#include <sge/input/mouse/button_info_container.hpp>
#include <sge/input/mouse/device.hpp>
#include <sge/input/mouse/discover_callback.hpp>
#include <sge/input/mouse/discover_event.hpp>
#include <sge/input/mouse/info.hpp>
#include <sge/input/mouse/manager.hpp>
#include <sge/input/mouse/remove_callback.hpp>
#include <sge/input/mouse/remove_event.hpp>
#include <sge/log/global.hpp>
#include <sge/systems/cursor_option.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/input_helper.hpp>
#include <sge/systems/input_helper_field.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/window.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/parameters.hpp>
#include <sge/window/system.hpp>
#include <sge/window/title.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/function_context.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/from_std_wstring.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/log/activate_levels.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <example_main.hpp>
#include <ostream>
#include <string>
#include <fcppt/config/external_end.hpp>


namespace
{

fcppt::string const
output_optional_string(
	sge::input::info::optional_string const &
);

void
cursor_discover(
	sge::input::cursor::discover_event const &
);

void
cursor_remove(
	sge::input::cursor::remove_event const &
);

void
cursor_button(
	sge::input::cursor::object &,
	sge::input::cursor::button_event const &
);

void
cursor_move(
	sge::input::cursor::object &,
	sge::input::cursor::move_event const &
);

void
joypad_discover(
	sge::input::joypad::discover_event const &
);

void
joypad_remove(
	sge::input::joypad::remove_event const &
);

void
joypad_absolute_axis(
	sge::input::joypad::device &,
	sge::input::joypad::absolute_axis_event const &
);

void
joypad_button(
	sge::input::joypad::device &,
	sge::input::joypad::button_event const &
);

void
joypad_relative_axis(
	sge::input::joypad::device &,
	sge::input::joypad::relative_axis_event const &
);

void
keyboard_discover(
	sge::input::keyboard::discover_event const &
);

void
keyboard_remove(
	sge::input::keyboard::remove_event const &
);

void
keyboard_char(
	sge::input::keyboard::device &,
	sge::input::keyboard::char_event const &
);

void
keyboard_key(
	sge::input::keyboard::device &,
	sge::input::keyboard::key_event const &
);

void
keyboard_key_repeat(
	sge::input::keyboard::device &,
	sge::input::keyboard::key_repeat_event const &
);

void
mouse_discover(
	sge::input::mouse::discover_event const &
);

void
mouse_remove(
	sge::input::mouse::remove_event const &
);

void
mouse_axis(
	sge::input::mouse::device &,
	sge::input::mouse::axis_event const &
);

void
mouse_button(
	sge::input::mouse::device &,
	sge::input::mouse::button_event const &
);

bool
extract_silent_parameter(
	awl::main::function_context const &
);

std::string const silent_parameter(
	"-silent"
);

struct dummy_event_handler
{
	typedef void result_type;

	template<
		typename Device,
		typename Event
	>
	result_type
	operator()(
		Device &,
		Event const &
	) const;
};

template<
	typename Functor,
	typename Function
>
Functor const
wrap_silent(
	Function const &,
	bool silent
);

}

awl::main::exit_code const
example_main(
	awl::main::function_context const &_context
)
try
{
	if(
		_context.argc() > 2
		||
		(
			_context.argc() == 2
			&&
			_context.argv()[1]
			!=
			silent_parameter
		)
	)
	{
		fcppt::io::cerr()
			<< FCPPT_TEXT("You can pass no arguments or -silent to suppress input.\n");

		return
			awl::main::exit_failure();
	}

	bool const silent(
		extract_silent_parameter(
			_context
		)
	);

	if(
		silent
	)
		sge::log::global().enable(
			false
		);
	else
		fcppt::log::activate_levels(
			sge::log::global(),
			fcppt::log::level::debug
		);

	sge::systems::instance const sys(
		sge::systems::list()
		(
			sge::systems::window(
				sge::window::parameters(
					sge::window::title(
						FCPPT_TEXT("sge input example")
					),
					sge::window::dim(
						1024,
						768
					)
				)
			)
		)
		(
			sge::systems::input(
				sge::systems::input_helper_field(
					sge::systems::input_helper::keyboard_collector
				),
				sge::systems::cursor_option_field(
					sge::systems::cursor_option::exclusive
				)
			)
		)
	);

	fcppt::io::cout()
		<< std::boolalpha;

	sge::input::cursor::manager const cursor_manager(
		sys.input_processor(),
		sge::input::cursor::discover_callback(
			::cursor_discover
		),
		sge::input::cursor::remove_callback(
			::cursor_remove
		),
		wrap_silent<
			sge::input::cursor::manager::button_callback
		>(
			::cursor_button,
			silent
		),
		wrap_silent<
			sge::input::cursor::manager::move_callback
		>(
			::cursor_move,
			silent
		)
	);

	sge::input::joypad::manager const joypad_manager(
		sys.input_processor(),
		sge::input::joypad::discover_callback(
			::joypad_discover
		),
		sge::input::joypad::remove_callback(
			::joypad_remove
		),
		wrap_silent<
			sge::input::joypad::manager::absolute_axis_callback
		>(
			::joypad_absolute_axis,
			silent
		),
		wrap_silent<
			sge::input::joypad::manager::button_callback
		>(
			::joypad_button,
			silent
		),
		wrap_silent<
			sge::input::joypad::manager::relative_axis_callback
		>(
			::joypad_relative_axis,
			silent
		)
	);

	sge::input::keyboard::manager const keyboard_manager(
		sys.input_processor(),
		sge::input::keyboard::discover_callback(
			::keyboard_discover
		),
		sge::input::keyboard::remove_callback(
			::keyboard_remove
		),
		wrap_silent<
			sge::input::keyboard::manager::char_callback
		>(
			::keyboard_char,
			silent
		),
		wrap_silent<
			sge::input::keyboard::manager::key_callback
		>(
			::keyboard_key,
			silent
		),
		wrap_silent<
			sge::input::keyboard::manager::key_repeat_callback
		>(
			::keyboard_key_repeat,
			silent
		)
	);

	sge::input::mouse::manager const mouse_manager(
		sys.input_processor(),
		sge::input::mouse::discover_callback(
			::mouse_discover
		),
		sge::input::mouse::remove_callback(
			::mouse_remove
		),
		wrap_silent<
			sge::input::mouse::manager::axis_callback
		>(
			::mouse_axis,
			silent
		),
		wrap_silent<
			sge::input::mouse::manager::button_callback
		>(
			::mouse_button,
			silent
		)
	);

	while(
		sys.window_system().next()
	)
		;

	return
		sys.window_system().exit_code();
}
catch(
	fcppt::exception const &_exception
)
{
	fcppt::io::cerr()
		<< _exception.string()
		<< FCPPT_TEXT('\n');

	return awl::main::exit_failure();
}

namespace
{

fcppt::string const
output_optional_string(
	sge::input::info::optional_string const &_name
)
{
	return
		_name
		?
			*_name
		:
			fcppt::string(
				FCPPT_TEXT("unnamed")
			)
		;
}

void
cursor_discover(
	sge::input::cursor::discover_event const &_event
)
{
	fcppt::io::cout()
		<< FCPPT_TEXT("cursor_discover: ")
		<< &_event.get()
		<< FCPPT_TEXT('\n');
}

void
cursor_remove(
	sge::input::cursor::remove_event const &_event
)
{
	fcppt::io::cout()
		<< FCPPT_TEXT("cursor_remove: ")
		<< &_event.get()
		<< FCPPT_TEXT('\n');
}

void
cursor_button(
	sge::input::cursor::object &_object,
	sge::input::cursor::button_event const &_event
)
{
	fcppt::io::cout()
		<< FCPPT_TEXT("cursor_button: ")
		<< &_object
		<< FCPPT_TEXT("\n\tcode: ")
		<< sge::input::cursor::button_code_to_string(
			_event.button_code()
		)
		<< FCPPT_TEXT("\n\tpressed: ")
		<< _event.pressed()
		<< FCPPT_TEXT('\n');
}

void
cursor_move(
	sge::input::cursor::object &_object,
	sge::input::cursor::move_event const &_event
)
{
	fcppt::io::cout()
		<< FCPPT_TEXT("cursor_move: ")
		<< &_object
		<< FCPPT_TEXT("\n\tposition: ")
		<< _event.position()
		<< FCPPT_TEXT('\n');
}

void
joypad_discover(
	sge::input::joypad::discover_event const &_event
)
{
	sge::input::joypad::info const info(
		_event.get().info()
	);

	fcppt::io::cout()
		<< FCPPT_TEXT("joypad_discover: ")
		<< &_event.get()
		<< FCPPT_TEXT(", ")
		<< info.name()
		<< FCPPT_TEXT('\n');

	{
		sge::input::joypad::absolute_axis_info_container::vector const &absolute_axes(
			info.absolute_axes().get()
		);

		fcppt::io::cout()
			<< FCPPT_TEXT("\tabsolute axes: ")
			<< absolute_axes.size()
			<< FCPPT_TEXT('\n');

		for(
			sge::input::joypad::absolute_axis_info_container::vector::const_iterator it(
				absolute_axes.begin()
			);
			it != absolute_axes.end();
			++it
		)
		{
			sge::input::joypad::absolute_axis_info const &axis_info(
				*it
			);

			fcppt::io::cout()
				<< FCPPT_TEXT("\t\tname: ")
				<< output_optional_string(
					axis_info.name()
				)
				<< FCPPT_TEXT("\n\t\tcode: ")
				<< sge::input::joypad::axis_code_to_string(
					axis_info.code()
				)
				<< FCPPT_TEXT("\n\t\tmin: ")
				<< axis_info.min()
				<< FCPPT_TEXT("\n\t\tmax: ")
				<< axis_info.max()
				<< FCPPT_TEXT('\n');
		}
	}

	{
		sge::input::joypad::relative_axis_info_container::vector const &relative_axes(
			info.relative_axes().get()
		);

		fcppt::io::cout()
			<< FCPPT_TEXT("\trelative axes: ")
			<< relative_axes.size()
			<< FCPPT_TEXT('\n');

		for(
			sge::input::joypad::relative_axis_info_container::vector::const_iterator it(
				relative_axes.begin()
			);
			it != relative_axes.end();
			++it
		)
		{
			sge::input::joypad::relative_axis_info const &axis_info(
				*it
			);

			fcppt::io::cout()
				<< FCPPT_TEXT("\t\tname: ")
				<< output_optional_string(
					axis_info.name()
				)
				<< FCPPT_TEXT("\n\t\tcode: ")
				<< sge::input::joypad::axis_code_to_string(
					axis_info.code()
				)
				<< FCPPT_TEXT('\n');
		}
	}

	{
		sge::input::joypad::button_info_container::vector const &buttons(
			info.buttons().get()
		);

		fcppt::io::cout()
			<< FCPPT_TEXT("\tbuttons: ")
			<< buttons.size()
			<< FCPPT_TEXT('\n');

		for(
			sge::input::joypad::button_info_container::vector::const_iterator it(
				buttons.begin()
			);
			it != buttons.end();
			++it
		)
		{
			sge::input::joypad::button_info const &button_info(
				*it
			);

			fcppt::io::cout()
				<< FCPPT_TEXT("\t\tname: ")
				<< output_optional_string(
					button_info.name()
				)
				<< FCPPT_TEXT('\n');
		}
	}

}

void
joypad_remove(
	sge::input::joypad::remove_event const &_event
)
{
	fcppt::io::cout()
		<< FCPPT_TEXT("joypad_remove: ")
		<< &_event.get()
		<< FCPPT_TEXT('\n');
}

void
joypad_absolute_axis(
	sge::input::joypad::device &_device,
	sge::input::joypad::absolute_axis_event const &_event
)
{
	fcppt::io::cout()
		<< FCPPT_TEXT("joypad_absolute_axis: ")
		<< &_device
		<< FCPPT_TEXT("\n\tcode: ")
		<< sge::input::joypad::axis_code_to_string(
			_event.axis().code()
		)
		<< FCPPT_TEXT("\n\tid: ")
		<< _event.axis().id()
		<< FCPPT_TEXT("\n\tvalue: ")
		<< _event.value()
		<< FCPPT_TEXT('\n');
}

void
joypad_button(
	sge::input::joypad::device &_device,
	sge::input::joypad::button_event const &_event
)
{
	fcppt::io::cout()
		<< FCPPT_TEXT("joypad_button: ")
		<< &_device
		<< FCPPT_TEXT("\n\tid: ")
		<< _event.button_id()
		<< FCPPT_TEXT("\n\tpressed: ")
		<< _event.pressed()
		<< FCPPT_TEXT('\n');
}

void
joypad_relative_axis(
	sge::input::joypad::device &_device,
	sge::input::joypad::relative_axis_event const &_event
)
{
	fcppt::io::cout()
		<< FCPPT_TEXT("joypad_relative_axis: ")
		<< &_device
		<< FCPPT_TEXT("\n\tcode: ")
		<< sge::input::joypad::axis_code_to_string(
			_event.axis().code()
		)
		<< FCPPT_TEXT("\n\tid: ")
		<< _event.axis().id()
		<< FCPPT_TEXT("\n\tvalue: ")
		<< _event.value()
		<< FCPPT_TEXT('\n');
}

void
keyboard_discover(
	sge::input::keyboard::discover_event const &_event
)
{
	fcppt::io::cout()
		<< FCPPT_TEXT("keyboard_discover: ")
		<< &_event.get()
		<< FCPPT_TEXT('\n');
}

void
keyboard_remove(
	sge::input::keyboard::remove_event const &_event
)
{
	fcppt::io::cout()
		<< FCPPT_TEXT("keyboard_remove: ")
		<< &_event.get()
		<< FCPPT_TEXT('\n');
}

void
keyboard_char(
	sge::input::keyboard::device &_device,
	sge::input::keyboard::char_event const &_event
)
{
	fcppt::io::cout()
		<< FCPPT_TEXT("keyboard_char: ")
		<< &_device
		<< FCPPT_TEXT("\n\tcharacter_value: ")
		<< static_cast<
			unsigned long
		>(
			_event.character()
		)
		<< FCPPT_TEXT("\n\tchar: ")
		<< fcppt::from_std_wstring(
			std::wstring(
				1u,
				_event.character()
			)
		)
		<< FCPPT_TEXT("\n\trepeated: ")
		<< _event.repeated()
		<< FCPPT_TEXT('\n');
}

void
keyboard_key(
	sge::input::keyboard::device &_device,
	sge::input::keyboard::key_event const &_event
)
{
	fcppt::io::cout()
		<< FCPPT_TEXT("keyboard_key: ")
		<< &_device
		<< FCPPT_TEXT("\n\tkey: ")
		<< sge::input::keyboard::key_code_to_string(
			_event.key_code()
		)
		<< FCPPT_TEXT("\n\tpressed: ")
		<< _event.pressed()
		<< FCPPT_TEXT('\n');
}

void
keyboard_key_repeat(
	sge::input::keyboard::device &_device,
	sge::input::keyboard::key_repeat_event const &_event
)
{
	fcppt::io::cout()
		<< FCPPT_TEXT("keyboard_key_repeat: ")
		<< &_device
		<< FCPPT_TEXT("\n\tkey: ")
		<< sge::input::keyboard::key_code_to_string(
			_event.key_code()
		)
		<< FCPPT_TEXT('\n');
}

void
mouse_discover(
	sge::input::mouse::discover_event const &_event
)
{
	sge::input::mouse::info const info(
		_event.get().info()
	);

	fcppt::io::cout()
		<< FCPPT_TEXT("mouse_discover: ")
		<< &_event.get()
		<< FCPPT_TEXT(", ")
		<< info.name()
		<< FCPPT_TEXT('\n');

	{
		sge::input::mouse::axis_info_container::vector const &axes(
			info.axes().get()
		);

		fcppt::io::cout()
			<< FCPPT_TEXT("\taxes: ")
			<< axes.size()
			<< FCPPT_TEXT('\n');

		for(
			sge::input::mouse::axis_info_container::vector::const_iterator it(
				axes.begin()
			);
			it != axes.end();
			++it
		)
		{
			sge::input::mouse::axis_info const &axis_info(
				*it
			);

			fcppt::io::cout()
				<< FCPPT_TEXT("\t\tname: ")
				<< output_optional_string(
					axis_info.name()
				)
				<< FCPPT_TEXT("\n\t\tcode: ")
				<< sge::input::mouse::axis_code_to_string(
					axis_info.code()
				)
				<< FCPPT_TEXT('\n');
		}
	}

	{
		sge::input::mouse::button_info_container::vector const &buttons(
			info.buttons().get()
		);

		fcppt::io::cout()
			<< FCPPT_TEXT("\tbuttons: ")
			<< buttons.size()
			<< FCPPT_TEXT('\n');

		for(
			sge::input::mouse::button_info_container::vector::const_iterator it(
				buttons.begin()
			);
			it != buttons.end();
			++it
		)
		{
			sge::input::mouse::button_info const &button_info(
				*it
			);

			fcppt::io::cout()
				<< FCPPT_TEXT("\t\tname: ")
				<< output_optional_string(
					button_info.name()
				)
				<< FCPPT_TEXT("\n\t\tcode: ")
				<< sge::input::mouse::button_code_to_string(
					button_info.code()
				)
				<< FCPPT_TEXT('\n');
		}
	}
}

void
mouse_remove(
	sge::input::mouse::remove_event const &_event
)
{
	fcppt::io::cout()
		<< FCPPT_TEXT("mouse_remove: ")
		<< &_event.get()
		<< FCPPT_TEXT('\n');
}

void
mouse_axis(
	sge::input::mouse::device &_device,
	sge::input::mouse::axis_event const &_event
)
{
	fcppt::io::cout()
		<< FCPPT_TEXT("mouse_axis: ")
		<< &_device
		<< FCPPT_TEXT("\n\tcode: ")
		<< sge::input::mouse::axis_code_to_string(
			_event.axis().code()
		)
		<< FCPPT_TEXT("\n\tid: ")
		<< _event.axis().id()
		<< FCPPT_TEXT("\n\tvalue: ")
		<< _event.value()
		<< FCPPT_TEXT('\n');
}

void
mouse_button(
	sge::input::mouse::device &_device,
	sge::input::mouse::button_event const &_event
)
{
	fcppt::io::cout()
		<< FCPPT_TEXT("mouse_button: ")
		<< &_device
		<< FCPPT_TEXT("\n\tcode: ")
		<< sge::input::mouse::button_code_to_string(
			_event.button().code()
		)
		<< FCPPT_TEXT("\n\tid: ")
		<< _event.button().id()
		<< FCPPT_TEXT("\n\tpressed: ")
		<< _event.pressed()
		<< FCPPT_TEXT('\n');
}

bool
extract_silent_parameter(
	awl::main::function_context const &_context
)
{
	return
		_context.argc() == 2
		&&
		_context.argv()[1]
		==
		silent_parameter
		;
}

template<
	typename Device,
	typename Event
>
typename dummy_event_handler::result_type
dummy_event_handler::operator()(
	Device &,
	Event const &
) const
{
}

template<
	typename Functor,
	typename Function
>
Functor const
wrap_silent(
	Function const &_function,
	bool const _silent
)
{
	return
		_silent
		?
			Functor(
				dummy_event_handler()
			)
		:
			Functor(
				_function
			)
		;
}

}
