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


#ifndef SGE_D3D9_TARGET_OFFSCREEN_HPP_INCLUDED
#define SGE_D3D9_TARGET_OFFSCREEN_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/target/basic.hpp>
#include <sge/d3d9/target/offscreen_fwd.hpp>
#include <sge/d3d9/surface/color_shared_ptr.hpp>
#include <sge/d3d9/surface/depth_stencil_shared_ptr.hpp>
#include <sge/renderer/color_surface_shared_ptr.hpp>
#include <sge/renderer/depth_stencil_surface_shared_ptr.hpp>
#include <sge/renderer/optional_dim2.hpp>
#include <sge/renderer/target/offscreen.hpp>
#include <sge/renderer/target/surface_index.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/container/index_map_decl.hpp>


namespace sge
{
namespace d3d9
{
namespace target
{

class offscreen
:
	public sge::d3d9::target::basic<
		sge::renderer::target::offscreen
	>
{
	FCPPT_NONCOPYABLE(
		offscreen
	);

	typedef sge::d3d9::target::basic<
		sge::renderer::target::offscreen
	> base;
public:
	explicit
	offscreen(
		IDirect3DDevice9 *
	);

	~offscreen();
private:
	void
	color_surface(
		sge::renderer::color_surface_shared_ptr,
		sge::renderer::target::surface_index
	);

	void
	depth_stencil_surface(
		sge::renderer::depth_stencil_surface_shared_ptr
	);

	sge::renderer::optional_dim2 const
	size() const;

	void
	on_activate();

	void
	on_deactivate();

	void
	change_surfaces(
		bool
	);

	typedef fcppt::container::index_map<
		sge::d3d9::surface::color_shared_ptr
	> color_surface_map;

	color_surface_map color_surfaces_;

	sge::d3d9::surface::depth_stencil_shared_ptr depth_stencil_surface_;
};

}
}
}

#endif
