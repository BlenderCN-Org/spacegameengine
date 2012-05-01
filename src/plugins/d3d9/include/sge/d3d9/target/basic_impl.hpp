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


#ifndef SGE_D3D9_TARGET_BASIC_IMPL_HPP_INCLUDED
#define SGE_D3D9_TARGET_BASIC_IMPL_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/devicefuncs/set_scissor_rect.hpp>
#include <sge/d3d9/devicefuncs/set_viewport.hpp>
#include <sge/d3d9/target/base.hpp>
#include <sge/d3d9/target/basic.hpp>
#include <sge/renderer/target/scissor_area.hpp>
#include <sge/renderer/target/viewport.hpp>


template<
	typename Base
>
sge::d3d9::target::basic<
	Base
>::basic(
	IDirect3DDevice9 *const _device,
	sge::renderer::target::viewport const &_viewport
)
:
	Base(),
	sge::d3d9::target::base(),
	device_(
		_device
	),
	active_(
		false
	),
	viewport_(
		_viewport
	),
	scissor_area_(
		sge::renderer::target::scissor_area(
			_viewport.get()
		)
	)
{
}

template<
	typename Base
>
sge::d3d9::target::basic<
	Base
>::~basic()
{
}

template<
	typename Base
>
void
sge::d3d9::target::basic<
	Base
>::viewport(
	sge::renderer::target::viewport const &_viewport
)
{
	viewport_ = _viewport;

	this->check_viewport();
}

template<
	typename Base
>
sge::renderer::target::viewport const
sge::d3d9::target::basic<
	Base
>::viewport() const
{
	return viewport_;
}

template<
	typename Base
>
void
sge::d3d9::target::basic<
	Base
>::scissor_area(
	sge::renderer::target::scissor_area const &_scissor_area
)
{
	scissor_area_ = _scissor_area;

	this->check_scissor_area();
}

template<
	typename Base
>
sge::renderer::target::scissor_area const
sge::d3d9::target::basic<
	Base
>::scissor_area() const
{
	return scissor_area_;
}

template<
	typename Base
>
void
sge::d3d9::target::basic<
	Base
>::active(
	bool const _active
)
{
	active_ = _active;

	this->check_viewport();

	this->check_scissor_area();

	if(
		_active
	)
		this->on_activate();
	else
		this->on_deactivate();
}

template<
	typename Base
>
IDirect3DDevice9 *
sge::d3d9::target::basic<
	Base
>::device() const
{
	return device_;
}

template<
	typename Base
>
void
sge::d3d9::target::basic<
	Base
>::check_viewport()
{
	if(
		active_
	)
		sge::d3d9::devicefuncs::set_viewport(
			device_,
			viewport_
		);
}

template<
	typename Base
>
void
sge::d3d9::target::basic<
	Base
>::check_scissor_area()
{
	if(
		active_
	)
		sge::d3d9::devicefuncs::set_scissor_rect(
			device_,
			scissor_area_
		);
}

#endif