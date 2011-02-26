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


#ifndef SGE_D3D9_TEXTURE_BASIC_IMPL_HPP_INCLUDED
#define SGE_D3D9_TEXTURE_BASIC_IMPL_HPP_INCLUDED

#include "basic.hpp"

template<
	typename Types
>
sge::d3d9::texture::basic<Type>::basic(
	d3d9::d3d_device_ptr const _device,
	parameters_type const &_params
)
:
	Types::base(),
	d3d9::texture::base(0),
	d3d9::resource(),
	device_(_device),
	params_(_params)
{
}

template<
	typename Types
>
sge::d3d9::texture::basic<Type>::~basic()
{
}

template<
	typename Types
>
typename sge::d3d9::texture::basic<Types>::parameters_type const &
sge::d3d9::texture::basic<Types>::parameters() const
{
	return params_;
}

template<
	typename Types
>
sge::d3d9::d3d_device_ptr const
sge::d3d9::texture::basic<Types>::device() const
{
	return device_;
}

template<
	typename Types
>
void
sge::d3d9::texture::basic<Types>::on_reset()
{
	texture::base(
		this->do_reset()
	);
}

template<
	typename Types
>
void
sge::d3d9::texture::basic<Types>::on_loss()
{
	this->do_loss();

	this->reset_base();
}

template<
	typename Types
>
sge::renderer::resource_flags_field const
sge::d3d9::texture::basic<Types>::flags() const
{
	return this->parameters().resource_flags();
}

#endif
