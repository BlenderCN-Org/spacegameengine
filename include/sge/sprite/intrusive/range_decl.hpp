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


#ifndef SGE_SPRITE_INTRUSIVE_RANGE_DECL_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_RANGE_DECL_HPP_INCLUDED

#include <sge/sprite/count.hpp>
#include <sge/sprite/intrusive/range_fwd.hpp>
#include <sge/sprite/intrusive/detail/list.hpp>
#include <fcppt/nonassignable.hpp>
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

template<
	typename Choices,
	bool IsConst
>
class range
{
	FCPPT_NONASSIGNABLE(
		range
	);

	typedef
	sge::sprite::intrusive::detail::list<
		Choices
	>
	list;
public:
	typedef
	fcppt::reference<
		typename
		std::conditional<
			IsConst,
			list const,
			list
		>::type
	>
	reference;

	typedef
	typename
	std::conditional<
		IsConst,
		typename
		list::const_iterator,
		typename
		list::iterator
	>::type
	iterator;

	range(
		reference,
		sge::sprite::count
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
	reference const list_;

	sge::sprite::count const size_;
};

}
}
}

#endif
