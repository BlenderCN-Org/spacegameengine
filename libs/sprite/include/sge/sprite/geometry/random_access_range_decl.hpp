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


#ifndef SGE_SPRITE_GEOMETRY_RANDOM_ACCESS_RANGE_DECL_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_RANDOM_ACCESS_RANGE_DECL_HPP_INCLUDED

#include <sge/sprite/count.hpp>
#include <sge/sprite/geometry/random_access_range_fwd.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/type_traits/is_iterator_of_category.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iterator>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace geometry
{

template<
	typename Iterator
>
class random_access_range
{
	FCPPT_NONASSIGNABLE(
		random_access_range
	);
public:
	static_assert(
		fcppt::type_traits::is_iterator_of_category<
			Iterator,
			std::random_access_iterator_tag
		>::value,
		"Iterator must be a random access iterator"
	);

	typedef Iterator iterator;

	random_access_range(
		iterator begin,
		iterator end
	);

	iterator
	begin() const;

	iterator
	end() const;

	sge::sprite::count
	size() const;

	bool
	empty() const;

	template<
		typename Compare
	>
	void
	sort(
		Compare const &
	) const;
private:
	iterator const
		begin_,
		end_;
};

}
}
}

#endif
