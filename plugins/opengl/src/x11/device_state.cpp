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


#include <sge/opengl/platform/device_state.hpp>
#include <sge/opengl/x11/device_state.hpp>
#include <sge/opengl/xrandr/optional_system_ref.hpp>
#include <sge/opengl/xrandr/resolution.hpp>
#include <sge/opengl/xrandr/state.hpp>
#include <sge/opengl/xrandr/state_unique_ptr.hpp>
#include <sge/opengl/xrandr/system.hpp>
#include <sge/renderer/display_mode/container.hpp>
#include <sge/renderer/display_mode/object.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/window/object_fwd.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/optional/bind.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/maybe.hpp>


sge::opengl::x11::device_state::device_state(
	fcppt::log::object &_log,
	sge::opengl::xrandr::optional_system_ref const &_xrandr_system,
	sge::renderer::display_mode::optional_object const &_display_mode,
	sge::window::object &_window
)
:
	sge::opengl::platform::device_state(),
	log_{
		_log
	},
	xrandr_state_(
		fcppt::optional::map(
			_xrandr_system,
			[
				&_window
			](
				fcppt::reference<
					sge::opengl::xrandr::system
				> const _system
			)
			{
				return
					_system.get().create_state(
						_window
					);
			}
		)
	),
	resolution_()
{
	if(
		_display_mode.has_value()
	)
		this->display_mode(
			_display_mode
		);
}

sge::opengl::x11::device_state::~device_state()
{
}

sge::renderer::display_mode::optional_object
sge::opengl::x11::device_state::display_mode() const
{
	return
		fcppt::optional::bind(
			xrandr_state_,
			[](
				xrandr_state_unique_ptr const &_state
			)
			{
				return
					_state->display_mode();
			}
		);
}

void
sge::opengl::x11::device_state::display_mode(
	sge::renderer::display_mode::optional_object const &_opt_display_mode
)
{
	// TODO: Optimize this
	resolution_ =
		optional_resolution_unique_ptr();

	resolution_ =
		fcppt::optional::bind(
			_opt_display_mode,
			[
				this
			](
				sge::renderer::display_mode::object const &_display_mode
			)
			{
				return
					fcppt::optional::maybe(
						xrandr_state_,
						[
							this
						]{
							FCPPT_LOG_ERROR(
								log_,
								fcppt::log::out
									<< FCPPT_TEXT("Xrandr was not found. Can't change the display mode.")
							);

							return
								optional_resolution_unique_ptr();
						},
						[
							&_display_mode
						](
							xrandr_state_unique_ptr const &_state
						){
							return
								optional_resolution_unique_ptr(
									_state->choose_resolution(
										_display_mode
									)
								);
						}
					);
			}
		);
}


sge::renderer::display_mode::container
sge::opengl::x11::device_state::display_modes() const
{
	return
		fcppt::optional::maybe(
			xrandr_state_,
			[]{
				return
					sge::renderer::display_mode::container();
			},
			[](
				xrandr_state_unique_ptr const &_state
			)
			{
				return
					_state->display_modes();
			}
		);
}
