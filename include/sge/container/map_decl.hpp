/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_CONTAINER_MAP_DECL_HPP_INCLUDED
#define SGE_CONTAINER_MAP_DECL_HPP_INCLUDED

#include <sge/container/map_fwd.hpp>
#include <utility>

namespace sge
{
namespace container
{

template<
	template<
		typename,
		typename,
		typename,
		typename
	> class MapType,
	typename Key,
	typename Mapped,
	template<
		typename
	> class Alloc,
	template<
		typename
	> class Comp 
>
class map {
	typedef MapType<
		Key,
		Mapped,
		Comp<
			Key
		>,
		Alloc<
			std::pair<
				Key,
				Mapped
			>
		>
	> internal_type;
public:
	typedef typename internal_type::key_type key_type;
	typedef typename internal_type::mapped_type mapped_type;

	typedef typename internal_type::value_type value_type;
	typedef typename internal_type::key_compare key_compare;
	typedef typename internal_type::allocator_type allocator_type;
	typedef typename internal_type::reference reference;
	typedef typename internal_type::const_reference const_reference;
	typedef typename internal_type::iterator iterator;
	typedef typename internal_type::const_iterator const_iterator;
	typedef typename internal_type::size_type size_type;
	typedef typename internal_type::difference_type difference_type;
	typedef typename internal_type::pointer pointer;
	typedef typename internal_type::const_pointer const_pointer;
	typedef typename internal_type::reverse_iterator reverse_iterator;
	typedef typename internal_type::const_reverse_iterator const_reverse_iterator;

	map();
	explicit map(
		internal_type const &);

	template<
		typename In
	>
	map(
		In beg,
		In end);

	void insert(
		key_type const &,
		mapped_type const &);
	
	void erase(
		key_type const &);

	mapped_type const &
	operator[](
		key_type const &) const;
	
	mapped_type &
	operator[](
		key_type const &);

	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;
private:
	internal_type impl_;
};

}
}

#endif
