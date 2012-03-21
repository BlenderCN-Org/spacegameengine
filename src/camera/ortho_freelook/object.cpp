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


#include <sge/camera/identity_gizmo.hpp>
#include <sge/camera/ortho_freelook/object.hpp>
#include <sge/camera/ortho_freelook/parameters.hpp>
#include <sge/camera/projection/invalid.hpp>
#include <sge/camera/projection/orthogonal.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/input/mouse/axis_event.hpp>
#include <sge/input/mouse/device.hpp>
#include <fcppt/chrono/duration_impl.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/variant/holds_type.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
sge::camera::ortho_freelook::object::object(
	ortho_freelook::parameters const &_params)
:
	camera::base(
		_params.projection_rect()
		?
			sge::camera::projection::object(
				sge::camera::projection::orthogonal(
					*(_params.projection_rect()),
					_params.near(),
					_params.far()))
		:
			sge::camera::projection::object(
				sge::camera::projection::invalid()),
		camera::identity_gizmo()),
	mouse_axis_connection_(
		_params.mouse().axis_callback(
			std::tr1::bind(
				&object::mouse_axis_callback,
				this,
				std::tr1::placeholders::_1))),
	keyboard_key_connection_(
		_params.keyboard().key_callback(
			std::tr1::bind(
				&object::keyboard_key_callback,
				this,
				std::tr1::placeholders::_1))),
	zoom_to_panning_speed_factor_(
		_params.zoom_to_panning_speed_factor()),
	zoom_to_zooming_speed_factor_(
		_params.zoom_to_zooming_speed_factor()),
	near_(
		_params.near()),
	far_(
		_params.far()),
	zoom_in_(
		false),
	zoom_out_(
		false),
	pan_(
		false),
	active_(
		_params.active())
{
}
FCPPT_PP_POP_WARNING

void
sge::camera::ortho_freelook::object::update(
	camera::duration const &d)
{
	if(!active_)
		return;

	if(fcppt::variant::holds_type<sge::camera::projection::invalid>(this->projection_object()))
		return;

	camera::projection::orthogonal const current_projection_object(
		camera::base::projection_object().get<camera::projection::orthogonal>());

	renderer::projection::rect _projection_rect =
		current_projection_object.rect();

	renderer::vector2 const
		current_zoom =
			renderer::vector2(
				zoom_to_zooming_speed_factor_.x() *
				static_cast<renderer::scalar>(
					_projection_rect.w()),
				zoom_to_zooming_speed_factor_.y() *
				static_cast<renderer::scalar>(
					_projection_rect.h())),
		current_zoom_speed =
			d.count() *
			current_zoom;

	renderer::scalar const sign =
		(zoom_in_ && !zoom_out_)
		?
			static_cast<renderer::scalar>(1.0f)
		:
			(zoom_out_ && !zoom_in_)
			?
				static_cast<renderer::scalar>(-1.0f)
			:
				static_cast<renderer::scalar>(0.0f);

	_projection_rect.pos(
		_projection_rect.pos() +
		sign *
		current_zoom_speed);

	_projection_rect.size(
		_projection_rect.size() +
		(static_cast<renderer::scalar>(-1.0f) * sign) *
		static_cast<renderer::scalar>(2.0f) *
		renderer::projection::rect::dim(
			current_zoom_speed.x(),
			current_zoom_speed.y()));

	camera::base::projection_object(
		camera::projection::orthogonal(
			_projection_rect,
			renderer::projection::near(
				current_projection_object.near()),
			renderer::projection::far(
				current_projection_object.far())));
}

bool
sge::camera::ortho_freelook::object::active() const
{
	return active_;
}

void
sge::camera::ortho_freelook::object::active(
	bool const _active)
{
	active_ =
		_active;
}

void
sge::camera::ortho_freelook::object::projection_rect(
	renderer::projection::rect const &_rect)
{
	this->projection_object(
		sge::camera::projection::orthogonal(
			_rect,
			near_,
			far_));
}

sge::camera::ortho_freelook::object::~object()
{
}

void
sge::camera::ortho_freelook::object::mouse_axis_callback(
	input::mouse::axis_event const &e)
{
	if(!active_)
		return;

	if(!pan_)
		return;

	camera::projection::orthogonal const current_projection_object(
		camera::base::projection_object().get<camera::projection::orthogonal>());

	renderer::projection::rect _projection_rect =
		current_projection_object.rect();

	renderer::vector2 const
		current_panning =
			renderer::vector2(
				zoom_to_panning_speed_factor_.x() *
				static_cast<renderer::scalar>(
					_projection_rect.w()),
				zoom_to_panning_speed_factor_.y() *
				static_cast<renderer::scalar>(
					_projection_rect.h())),
		current_panning_speed =
			renderer::vector2(
				static_cast<renderer::scalar>(
					e.axis().code() == input::mouse::axis_code::x
					?
						static_cast<renderer::scalar>(
							-e.value())
					:
						0.0f) *
				current_panning.x(),
				static_cast<renderer::scalar>(
					e.axis().code() == input::mouse::axis_code::y
					?
						static_cast<renderer::scalar>(
							-e.value())
					:
						0.0f) *
				current_panning.y());

	_projection_rect.pos(
		_projection_rect.pos() +
		current_panning_speed);

	camera::base::projection_object(
		camera::projection::orthogonal(
			_projection_rect,
			renderer::projection::near(
				current_projection_object.near()),
			renderer::projection::far(
				current_projection_object.far())));
}

void
sge::camera::ortho_freelook::object::keyboard_key_callback(
	input::keyboard::key_event const &k)
{
	if(!active_)
		return;

	switch(k.key_code())
	{
		case input::keyboard::key_code::w:
			zoom_in_ = k.pressed();
			break;
		case input::keyboard::key_code::s:
			zoom_out_ = k.pressed();
			break;
		case input::keyboard::key_code::g:
			pan_ = k.pressed();
			break;
		default: break;
	}
}
