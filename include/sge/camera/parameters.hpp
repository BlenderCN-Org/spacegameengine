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


#ifndef SGE_CAMERA_PARAMETERS_HPP_INCLUDED
#define SGE_CAMERA_PARAMETERS_HPP_INCLUDED

#include <sge/camera/projection/object.hpp>
#include <sge/camera/symbol.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/vector3.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/input/mouse/device_fwd.hpp>
#include <fcppt/math/vector/basic_impl.hpp>

namespace sge
{
namespace camera
{
class parameters
{
public:
	SGE_CAMERA_SYMBOL
	explicit
	parameters(
		projection::object const &,
		renderer::scalar movement_speed,
		renderer::scalar rotation_speed,
		renderer::vector3 const &position,
		sge::input::keyboard::device &,
		sge::input::mouse::device &);

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
	renderer::vector3 const &
	position() const;

	SGE_CAMERA_SYMBOL
	sge::input::keyboard::device &
	keyboard() const;

	SGE_CAMERA_SYMBOL
	sge::input::mouse::device &
	mouse() const;
private:
	projection::object projection_;
	renderer::scalar movement_speed_;
	renderer::scalar rotation_speed_;
	renderer::vector3 position_;
	sge::input::keyboard::device &keyboard_;
	sge::input::mouse::device &mouse_;
};
}
}

#endif
