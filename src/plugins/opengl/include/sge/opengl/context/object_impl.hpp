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


#ifndef SGE_OPENGL_CONTEXT_OBJECT_IMPL_HPP_INCLUDED
#define SGE_OPENGL_CONTEXT_OBJECT_IMPL_HPP_INCLUDED

#include <sge/opengl/context/base_decl.hpp>
#include <sge/opengl/context/id_decl.hpp>
#include <sge/opengl/context/object_decl.hpp>
#include <fcppt/move.hpp>
#include <fcppt/assert/error.hpp>


template<
	typename Domain
>
sge::opengl::context::object<
	Domain
>::object()
:
	elements_()
{
}

template<
	typename Domain
>
sge::opengl::context::object<
	Domain
>::~object()
{
}

template<
	typename Domain
>
typename sge::opengl::context::object<
	Domain
>::base_type *
sge::opengl::context::object<
	Domain
>::get(
	id_type const _id
)
{
	return
		elements_.get(
			_id.get()
		);
}

template<
	typename Domain
>
typename sge::opengl::context::object<
	Domain
>::base_type &
sge::opengl::context::object<
	Domain
>::insert(
	id_type const _id,
	base_unique_ptr _ptr
)
{
	base_type *const ret(
		elements_.insert(
			_id.get(),
			fcppt::move(
				_ptr
			)
		)
	);

	FCPPT_ASSERT_ERROR(
		ret
	);

	return *ret;
}

#endif
