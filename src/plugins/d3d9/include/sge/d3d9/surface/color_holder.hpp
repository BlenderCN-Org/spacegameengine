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


#ifndef SGE_D3D9_SURFACE_COLOR_HOLDER_HPP_INCLUDED
#define SGE_D3D9_SURFACE_COLOR_HOLDER_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/surface/color_holder_fwd.hpp>
#include <sge/d3d9/surface/d3d_scoped_ptr.hpp>
#include <sge/d3d9/surface/d3d_unique_ptr.hpp>
#include <sge/renderer/dim2.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/math/dim/object_decl.hpp>


namespace sge
{
namespace d3d9
{
namespace surface
{

class color_holder
{
	FCPPT_NONCOPYABLE(
		color_holder
	);
public:
	explicit
	color_holder(
		sge::d3d9::surface::d3d_unique_ptr &&
	);

	~color_holder();

	IDirect3DSurface9 &
	get() const;

	sge::renderer::dim2 const &
	size() const;

	bool
	is_render_target() const;
private:
	sge::d3d9::surface::d3d_scoped_ptr const surface_;

	sge::renderer::dim2 const size_;

	bool const is_render_target_;
};

}
}
}

#endif
