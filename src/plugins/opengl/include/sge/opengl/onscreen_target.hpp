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


#ifndef SGE_OPENGL_ONSCREEN_TARGET_HPP_INCLUDED
#define SGE_OPENGL_ONSCREEN_TARGET_HPP_INCLUDED

#include <sge/opengl/basic_target.hpp>
#include <sge/opengl/onscreen_target_fwd.hpp>
#include <sge/opengl/backend/context_fwd.hpp>
#include <sge/opengl/context/device/object_fwd.hpp>
#include <sge/renderer/screen_unit.hpp>
#include <sge/renderer/color_buffer/surface_fwd.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <awl/window/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{

class onscreen_target
:
	public sge::opengl::basic_target<
		sge::renderer::target::onscreen
	>
{
	FCPPT_NONCOPYABLE(
		onscreen_target
	);
public:
	typedef sge::opengl::basic_target<
		sge::renderer::target::onscreen
	> base;

	onscreen_target(
		sge::opengl::context::device::object &,
		sge::opengl::backend::context &,
		awl::window::object &
	);

	~onscreen_target()
	override;
private:
	void
	on_bind()
	override;

	void
	on_unbind()
	override;

	void
	end_rendering()
	override;

	sge::renderer::color_buffer::surface const &
	surface() const
	override;

	sge::renderer::screen_unit
	height() const
	override;

	typedef
	std::unique_ptr<
		sge::renderer::color_buffer::surface
	>
	color_surface_unique_ptr;

	sge::opengl::backend::context &context_;

	color_surface_unique_ptr const main_surface_;
};

}
}

#endif
