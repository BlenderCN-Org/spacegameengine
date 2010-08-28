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


#ifndef SGE_SPRITE_INTRUSIVE_SYSTEM_IMPL_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_SYSTEM_IMPL_HPP_INCLUDED

#include <sge/sprite/intrusive/system_decl.hpp>
#include <sge/sprite/intrusive/adder_impl.hpp>
#include <sge/sprite/detail/fill_geometry.hpp>
#include <sge/sprite/detail/optional_size.hpp>
#include <sge/sprite/detail/render.hpp>
#include <sge/sprite/detail/set_matrices.hpp>
#include <sge/sprite/render_states.hpp>
#include <sge/sprite/system_base_impl.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/renderer/state/scoped.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/index_buffer.hpp>
#include <sge/renderer/scoped_vertex_buffer.hpp>
#include <sge/renderer/size_type.hpp>
#include <fcppt/optional_impl.hpp>
#include <boost/foreach.hpp>

template<
	typename Choices
>
sge::sprite::intrusive::system<Choices>::system(
	renderer::device_ptr const _rend
)
:
	base(
		_rend
	),
	sprite_levels_(),
	adder_(
		sprite_levels_
	)
{}

template<
	typename Choices
>
sge::sprite::intrusive::system<Choices>::~system()
{}

template<
	typename Choices
>
template<
	typename EqualFunction
>
void
sge::sprite::intrusive::system<Choices>::render_all(
	EqualFunction const &_equal
)
{
	sprite::detail::set_matrices<
		typename Choices::type_choices
	>(
		base::renderer()
	);

	sge::renderer::state::scoped const state(
		base::renderer(),
		sprite::render_states()
	);

	BOOST_FOREACH(
		typename level_map::value_type const &v,
		sprite_levels_
	)
		render(
			*v.second,
			_equal
		);
}

template<
	typename Choices
>
template<
	typename EqualFunction
>
void
sge::sprite::intrusive::system<Choices>::render(
	order const _order,
	EqualFunction const &_equal
)
{
	sprite::detail::set_matrices<
		typename Choices::type_choices
	>(
		base::renderer()
	);

	sge::renderer::state::scoped const state(
		base::renderer(),
		sprite::render_states()
	);

	render(
		sprite_levels_[
			_order
		],
		_equal
	);
}

template<
	typename Choices
>
template<
	typename EqualFunction
>
void
sge::sprite::intrusive::system<Choices>::render_advanced(
	order const _order,
	EqualFunction const &_equal
)
{
	render(
		sprite_levels_[
			_order
		],
		_equal
	);
}

template<
	typename Choices
>
template<
	typename EqualFunction
>
void
sge::sprite::intrusive::system<Choices>::render(
	list const &sprites,
	EqualFunction const &equal
)
{
	if(
		sprites.empty()
	)
		return;
	
	// TODO: better track the sprites size
	renderer::size_type const sprite_count(
		sprites.size()
	);

	base::allocate_buffers(
		sprite_count
	);

	renderer::vertex_buffer_ptr const vb(
		base::vertex_buffer()
	);

	renderer::index_buffer_ptr const ib(
		base::index_buffer()
	);

	sprite::detail::fill_geometry(
		sprites.begin(),
		sprites.end(),
		base::vertex_buffer(),
		base::index_buffer(),
		sprite::detail::optional_size(
			sprite_count
		)
	);

	renderer::device_ptr const rend(
		base::renderer()
	);

	renderer::scoped_vertex_buffer const vb_context(
		rend,
		vb
	);

	sprite::detail::render(
		sprites.begin(),
		sprites.end(),
		equal,
		rend,
		ib
	);
}

template<
	typename Choices
>
typename sge::sprite::intrusive::system<Choices>::adder_base *
sge::sprite::intrusive::system<Choices>::adder()
{
	return &adder_;
}

#endif
