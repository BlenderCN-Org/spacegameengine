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


#ifndef SGE_SPRITE_EXTERNAL_SYSTEM_IMPL_HPP_INCLUDED
#define SGE_SPRITE_EXTERNAL_SYSTEM_IMPL_HPP_INCLUDED

#include <sge/sprite/external_system_decl.hpp>
#include <sge/sprite/system_base_impl.hpp>
#include <sge/sprite/render_states.hpp>
#include <sge/sprite/set_matrices.hpp>
#include <sge/sprite/detail/fill_geometry.hpp>
#include <sge/sprite/detail/optional_size.hpp>
#include <sge/sprite/detail/render.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/index_buffer.hpp>
#include <sge/renderer/scoped_vertex_buffer.hpp>
#include <sge/renderer/scoped_vertex_declaration.hpp>
#include <sge/renderer/state/scoped.hpp>
#include <fcppt/optional_impl.hpp>
#include <iterator>

template<
	typename Choices
>
sge::sprite::external_system<Choices>::external_system(
	renderer::device &_rend
)
:
 	base(
		_rend
	)
{
}

template<
	typename Choices
>
sge::sprite::external_system<Choices>::~external_system()
{
}

template<
	typename Choices
>
template<
	typename Iterator,
	typename SortFunction,
	typename EqualFunction
>
void
sge::sprite::external_system<Choices>::render(
	Iterator const _begin,
	Iterator const _end,
	SortFunction const &_sort_fun,
	EqualFunction const &_equal_fun
)
{
	sprite::set_matrices(
		base::renderer()
	);

	sge::renderer::state::scoped const state(
		base::renderer(),
		sprite::render_states<
			Choices
		>()
	);

	render_advanced(
		_begin,
		_end,
		_sort_fun,
		_equal_fun
	);
}

template<
	typename Choices
>
template<
	typename Iterator,
	typename SortFunction,
	typename EqualFunction
>
void
sge::sprite::external_system<Choices>::render_advanced(
	Iterator const _begin,
	Iterator const _end,
	SortFunction const &_sort_fun,
	EqualFunction const &_equal_fun
)
{
	if(
		_begin == _end
	)
		return;

	_sort_fun(
		_begin,
		_end
	);

	renderer::size_type const sprite_count(
		static_cast<
			renderer::size_type
		>(
			std::distance(
				_begin,
				_end
			)
		)
	);

	this->allocate_buffers(
		sprite_count
	);

	detail::fill_geometry(
		_begin,
		_end,
		base::buffers(),
		detail::optional_size(
			sprite_count
		)
	);

	renderer::scoped_vertex_declaration const vb_declaration(
		base::renderer(),
		base::vertex_declaration()
	);

	renderer::scoped_vertex_buffer const vb_context(
		base::renderer(),
		*base::vertex_buffer()
	);

	detail::render(
		_begin,
		_end,
		_equal_fun,
		base::renderer(),
		base::buffers()
	);
}

#endif
