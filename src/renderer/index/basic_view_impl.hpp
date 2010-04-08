/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RENDERER_INDEX_BASIC_VIEW_IMPL_HPP_INCLUDED
#define SGE_RENDERER_INDEX_BASIC_VIEW_IMPL_HPP_INCLUDED

#include <sge/renderer/index/basic_view.hpp>
#include <sge/renderer/index/dynamic/make_format.hpp>
#include <fcppt/assert.hpp>
#include <boost/type_traits/remove_const.hpp>

template<
	typename Index
>
sge::renderer::index::basic_view<Index>::basic_view(
	pointer const data_,
	size_type const size_
)
:
	data_(data_),
	size_(size_)
{
	FCPPT_ASSERT(data_);
}

template<
	typename Index
>
typename sge::renderer::index::basic_view<Index>::pointer
sge::renderer::index::basic_view<Index>::data() const
{
	return data_;
}

template<
	typename Index
>
sge::renderer::size_type
sge::renderer::index::basic_view<Index>::size() const
{
	return size_;
}

template<
	typename Index
>
typename sge::renderer::index::basic_view<Index>::iterator
sge::renderer::index::basic_view<Index>::begin() const
{
	return data();
}

template<
	typename Index
>
typename sge::renderer::index::basic_view<Index>::iterator
sge::renderer::index::basic_view<Index>::end() const
{
	return begin() + size();
}

template<
	typename Index
>
sge::renderer::index::dynamic::format::type
sge::renderer::index::basic_view<Index>::format() const
{
	return
		dynamic::make_format<
			typename boost::remove_const<
				Index
			>::type
		>();
}

#endif
