/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/cegui/default_cursor.hpp>
#include <sge/cegui/syringe.hpp>
#include <sge/input/cursor/object.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/tr1/functional.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
sge::cegui::default_cursor::default_cursor(
	syringe &_syringe,
	sge::input::cursor::object &_cursor)
:
	syringe_(
		_syringe),
	button_connection_(
		_cursor.button_callback(
			std::tr1::bind(
				&default_cursor::button_callback,
				this,
				std::tr1::placeholders::_1))),
	axis_connection_(
		_cursor.move_callback(
			std::tr1::bind(
				&default_cursor::move_callback,
				this,
				std::tr1::placeholders::_1)))
{
	syringe_.inject(
		_cursor.position());
}
FCPPT_PP_POP_WARNING

sge::cegui::default_cursor::~default_cursor()
{
}

void
sge::cegui::default_cursor::button_callback(
	sge::input::cursor::button_event const &e)
{
	syringe_.inject(
		e);
}

void
sge::cegui::default_cursor::move_callback(
	sge::input::cursor::move_event const &e)
{
	syringe_.inject(
		e);
}
