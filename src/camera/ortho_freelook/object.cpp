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


#include <sge/camera/projection_matrix.hpp>
#include <sge/camera/coordinate_system/identity.hpp>
#include <sge/camera/coordinate_system/object.hpp>
#include <sge/camera/ortho_freelook/object.hpp>
#include <sge/camera/ortho_freelook/parameters.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_event_fwd.hpp>
#include <sge/input/mouse/axis_event.hpp>
#include <sge/input/mouse/device.hpp>
#include <sge/renderer/vector2.hpp>
#include <sge/renderer/projection/orthogonal.hpp>
#include <sge/renderer/projection/rect.hpp>
#include <sge/src/camera/set_pressed_if_appropriate.hpp>
#include <fcppt/maybe_void.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/math/box/stretch_relative.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/dim.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::camera::ortho_freelook::object::object(
	ortho_freelook::parameters const &_params)
:
	mouse_axis_connection_(
		_params.mouse().axis_callback(
			std::bind(
				&object::mouse_axis_callback,
				this,
				std::placeholders::_1))),
	keyboard_key_connection_(
		_params.keyboard().key_callback(
			std::bind(
				&object::key_callback,
				this,
				std::placeholders::_1))),
	action_mapping_(
		_params.action_mapping()),
	current_projection_rectangle_(),
	zoom_speed_(
		_params.zoom_speed()),
	pan_speed_(
		_params.pan_speed()),
	near_(
		_params.near()),
	far_(
		_params.far()),
	is_active_(
		_params.is_active()),
	zoom_in_pressed_(
		false),
	zoom_out_pressed_(
		false),
	pan_pressed_(
		false)
{
}

FCPPT_PP_POP_WARNING

void
sge::camera::ortho_freelook::object::zoom_speed(
	ortho_freelook::zoom_speed const &_zoom_speed)
{
	zoom_speed_ =
		_zoom_speed;
}

sge::camera::coordinate_system::object const
sge::camera::ortho_freelook::object::coordinate_system() const
{
	return
		sge::camera::coordinate_system::identity();
}

sge::camera::projection_matrix const
sge::camera::ortho_freelook::object::projection_matrix() const
{
	return
		sge::camera::projection_matrix(
			sge::renderer::projection::orthogonal(
				FCPPT_ASSERT_OPTIONAL_ERROR(
					current_projection_rectangle_
				),
				near_,
				far_
			)
		);
}

sge::camera::is_active const
sge::camera::ortho_freelook::object::is_active() const
{
	return
		is_active_;
}

void
sge::camera::ortho_freelook::object::is_active(
	sge::camera::is_active const _is_active)
{
	is_active_ =
		_is_active;
}

void
sge::camera::ortho_freelook::object::update(
	camera::update_duration const _delta)
{
	if(!is_active_.get() ||  zoom_in_pressed_ == zoom_out_pressed_)
		return;

	fcppt::maybe_void(
		current_projection_rectangle_,
		[
			this,
			_delta
		](
			sge::renderer::projection::rect const &_current_projection_rectangle
		)
		{
			sge::renderer::vector2 const
				ones(
					1.0f,
					1.0f),
				scaled_zoom_speed(
					_delta.count() * zoom_speed_.get());

			renderer::scalar const zoom_sign(
				static_cast<renderer::scalar>(
					zoom_out_pressed_) -
				static_cast<renderer::scalar>(
					zoom_in_pressed_));

			renderer::vector2 const
				zoom_factor(
					ones +
					zoom_sign * scaled_zoom_speed);

			current_projection_rectangle_ =
				ortho_freelook::optional_projection_rectangle(
					fcppt::math::box::stretch_relative(
						_current_projection_rectangle,
						zoom_factor
					)
				);
		}
	);
}

void
sge::camera::ortho_freelook::object::projection_rectangle(
	renderer::projection::rect const &_current_projection_rectangle)
{
	current_projection_rectangle_ =
		ortho_freelook::optional_projection_rectangle(
			_current_projection_rectangle);
}

sge::camera::ortho_freelook::object::~object()
{
}

void
sge::camera::ortho_freelook::object::mouse_axis_callback(
	sge::input::mouse::axis_event const &_axis)
{
	if(!is_active_.get() || !pan_pressed_)
		return;

	if(_axis.code() != input::mouse::axis_code::x && _axis.code() != input::mouse::axis_code::y)
		return;

	fcppt::maybe_void(
		current_projection_rectangle_,
		[
			&_axis,
			this
		](
			sge::renderer::projection::rect &_current_projection_rectangle
		){
			renderer::vector2 const
				pan_axis(
					_axis.code() == input::mouse::axis_code::x
					?
						-static_cast<float>(
							_axis.value())
					:
						0.0f,
					_axis.code() == input::mouse::axis_code::y
					?
						-static_cast<float>(
							_axis.value())
					:
						0.0f),
				panning_speed(
					pan_speed_.get() *
					pan_axis *
					_current_projection_rectangle.size()
				);

			_current_projection_rectangle.pos(
				_current_projection_rectangle.pos() +
				panning_speed);
		}
	);
}

void
sge::camera::ortho_freelook::object::key_callback(
	sge::input::keyboard::key_event const &_key_event)
{
	sge::camera::set_pressed_if_appropriate(
		zoom_in_pressed_,
		action_mapping_.zoom_in().get(),
		_key_event);

	sge::camera::set_pressed_if_appropriate(
		zoom_out_pressed_,
		action_mapping_.zoom_out().get(),
		_key_event);

	sge::camera::set_pressed_if_appropriate(
		pan_pressed_,
		action_mapping_.activate_pan().get(),
		_key_event);
}
