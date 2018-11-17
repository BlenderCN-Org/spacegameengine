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


#ifndef SGE_CAMERA_ORTHO_FREELOOK_PARAMETERS_HPP_INCLUDED
#define SGE_CAMERA_ORTHO_FREELOOK_PARAMETERS_HPP_INCLUDED

#include <sge/camera/detail/symbol.hpp>
#include <sge/camera/ortho_freelook/optional_projection_rectangle.hpp>
#include <sge/camera/ortho_freelook/pan_speed.hpp>
#include <sge/camera/ortho_freelook/zoom_speed.hpp>
#include <sge/camera/ortho_freelook/action/mapping.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/renderer/projection/rect.hpp>


namespace sge
{
namespace camera
{
namespace ortho_freelook
{

class parameters
{
public:
	SGE_CAMERA_DETAIL_SYMBOL
	parameters(
		sge::renderer::projection::near,
		sge::renderer::projection::far
	);

	SGE_CAMERA_DETAIL_SYMBOL
	parameters &
	zoom_speed(
		sge::camera::ortho_freelook::zoom_speed
	);

	SGE_CAMERA_DETAIL_SYMBOL
	sge::camera::ortho_freelook::zoom_speed
	zoom_speed() const;

	SGE_CAMERA_DETAIL_SYMBOL
	parameters &
	action_mapping(
		sge::camera::ortho_freelook::action::mapping const &
	);

	SGE_CAMERA_DETAIL_SYMBOL
	sge::camera::ortho_freelook::action::mapping const &
	action_mapping() const;

	SGE_CAMERA_DETAIL_SYMBOL
	parameters &
	pan_speed(
		sge::camera::ortho_freelook::pan_speed
	);

	SGE_CAMERA_DETAIL_SYMBOL
	sge::camera::ortho_freelook::pan_speed
	pan_speed() const;

	SGE_CAMERA_DETAIL_SYMBOL
	parameters &
	projection_rectangle(
		sge::renderer::projection::rect const &
	);

	SGE_CAMERA_DETAIL_SYMBOL
	sge::camera::ortho_freelook::optional_projection_rectangle const &
	projection_rectangle() const;

	SGE_CAMERA_DETAIL_SYMBOL
	sge::renderer::projection::near
	near() const;

	SGE_CAMERA_DETAIL_SYMBOL
	sge::renderer::projection::far
	far() const;

	SGE_CAMERA_DETAIL_SYMBOL
	~parameters();
private:
	sge::camera::ortho_freelook::zoom_speed zoom_speed_;

	sge::camera::ortho_freelook::pan_speed pan_speed_;

	sge::camera::ortho_freelook::optional_projection_rectangle projection_rectangle_;

	sge::renderer::projection::near near_;

	sge::renderer::projection::far far_;

	sge::camera::ortho_freelook::action::mapping action_mapping_;
};

}
}
}

#endif
