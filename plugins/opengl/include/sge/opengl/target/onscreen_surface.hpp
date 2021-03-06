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


#ifndef SGE_OPENGL_TARGET_ONSCREEN_SURFACE_HPP_INCLUDED
#define SGE_OPENGL_TARGET_ONSCREEN_SURFACE_HPP_INCLUDED

#include <sge/image/color/format.hpp>
#include <sge/opengl/color_format_fwd.hpp>
#include <sge/renderer/raw_value.hpp>
#include <sge/renderer/color_buffer/readable_surface.hpp>
#include <awl/window/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/container/buffer/object_decl.hpp>
#include <fcppt/optional/object_decl.hpp>


namespace sge
{
namespace opengl
{
namespace target
{

class onscreen_surface
:
	public sge::renderer::color_buffer::readable_surface
{
	FCPPT_NONCOPYABLE(
		onscreen_surface
	);
public:
	explicit
	onscreen_surface(
		awl::window::object &
	);

	~onscreen_surface()
	override;
private:
	sge::renderer::color_buffer::readable_surface::const_view
	lock_c(
		sge::renderer::color_buffer::readable_surface::lock_area const &
	) const
	override;

	void
	unlock() const
	override;

	dim
	size() const
	override;

	sge::opengl::color_format
	gl_format() const;

	sge::image::color::format
	format() const
	override;

	awl::window::object &window_;

	typedef
	fcppt::container::buffer::object<
		sge::renderer::raw_value
	>
	buffer_type;

	typedef
	fcppt::optional::object<
		buffer_type
	>
	optional_buffer_type;

	mutable optional_buffer_type buffer_;
};

}
}
}

#endif
