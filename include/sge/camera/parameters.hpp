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


#ifndef SGE_CAMERA_PARAMETERS_HPP_INCLUDED
#define SGE_CAMERA_PARAMETERS_HPP_INCLUDED

#include <sge/camera/projection/object.hpp>
#include <sge/camera/symbol.hpp>
#include <sge/camera/gizmo_type.hpp>
#include <sge/camera/movement_speed.hpp>
#include <sge/camera/rotation_speed.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/input/mouse/device_fwd.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/nonassignable.hpp>

namespace sge
{
namespace camera
{
class parameters
{
	FCPPT_NONASSIGNABLE(
		parameters
	);
public:
	SGE_CAMERA_SYMBOL
	explicit
	parameters(
		camera::movement_speed const &,
		camera::rotation_speed const &,
		input::keyboard::device &,
		input::mouse::device &);

	SGE_CAMERA_SYMBOL camera::parameters &
	projection(
		projection::object const &);

	SGE_CAMERA_SYMBOL camera::parameters &
	gizmo(
		camera::gizmo_type const &);

	SGE_CAMERA_SYMBOL camera::parameters &
	active(
		bool);

	SGE_CAMERA_SYMBOL
	projection::object const &
	projection() const;

	SGE_CAMERA_SYMBOL
	renderer::scalar
	movement_speed() const;

	SGE_CAMERA_SYMBOL
	renderer::scalar
	rotation_speed() const;

	SGE_CAMERA_SYMBOL
	camera::gizmo_type const &
	gizmo() const;

	SGE_CAMERA_SYMBOL
	input::keyboard::device &
	keyboard() const;

	SGE_CAMERA_SYMBOL
	input::mouse::device &
	mouse() const;

	bool
	active() const;
private:
	camera::projection::object projection_;
	renderer::scalar movement_speed_;
	renderer::scalar rotation_speed_;
	camera::gizmo_type gizmo_;
	input::keyboard::device &keyboard_;
	input::mouse::device &mouse_;
	bool active_;
};
}
}

#endif
