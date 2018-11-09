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


#ifndef SGE_SPRITE_INTRUSIVE_ORDERED_RANGE_DECL_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_ORDERED_RANGE_DECL_HPP_INCLUDED

#include <sge/sprite/count.hpp>
#include <sge/sprite/intrusive/ordered/iterator_fwd.hpp>
#include <sge/sprite/intrusive/ordered/range_fwd.hpp>
#include <sge/sprite/intrusive/ordered/detail/map.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace intrusive
{
namespace ordered
{

template<
	typename Choices,
	typename Order,
	bool IsConst
>
class range
{
	typedef
	sge::sprite::intrusive::ordered::detail::map<
		Order,
		Choices
	>
	ordered_map;
public:
	typedef
	fcppt::reference<
		typename
		std::conditional<
			IsConst,
			ordered_map const,
			ordered_map
		>::type
	>
	ordered_map_reference;

	typedef
	sge::sprite::intrusive::ordered::iterator<
		Choices,
		Order,
		IsConst
	>
	iterator;

	explicit
	range(
		ordered_map_reference
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
		typename Equal
	>
	void
	sort(
		Equal const &
	) const;
private:
	ordered_map_reference ordered_map_;

	sge::sprite::count size_;
};

}
}
}
}

#endif
