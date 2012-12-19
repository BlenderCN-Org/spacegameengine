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


#include <sge/cegui/default_keyboard.hpp>
#include <sge/cegui/syringe.hpp>
#include <sge/input/keyboard/device.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
sge::cegui::default_keyboard::default_keyboard(
	syringe &_syringe,
	sge::input::keyboard::device &_keyboard)
:
	syringe_(
		_syringe),
	key_callback_(
		_keyboard.key_callback(
			std::bind(
				&default_keyboard::key_callback,
				this,
				std::placeholders::_1))),
	key_repeat_callback_(
		_keyboard.key_repeat_callback(
			std::bind(
				&default_keyboard::key_repeat_callback,
				this,
				std::placeholders::_1))),
	char_callback_(
		_keyboard.char_callback(
			std::bind(
				&default_keyboard::char_callback,
				this,
				std::placeholders::_1)))
{
}
FCPPT_PP_POP_WARNING

sge::cegui::default_keyboard::~default_keyboard()
{
}

void
sge::cegui::default_keyboard::key_callback(
	sge::input::keyboard::key_event const &e)
{
	syringe_.inject(
		e);
}

void
sge::cegui::default_keyboard::key_repeat_callback(
	sge::input::keyboard::key_repeat_event const &e)
{
	syringe_.inject(
		e);
}

void
sge::cegui::default_keyboard::char_callback(
	sge::input::keyboard::char_event const &e)
{
	syringe_.inject(
		e);
}
