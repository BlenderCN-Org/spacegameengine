/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SPRITE_INTRUSIVE_COLLECTION_DECL_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_COLLECTION_DECL_HPP_INCLUDED

#include <sge/sprite/count.hpp>
#include <sge/sprite/object_decl.hpp>
#include <sge/sprite/intrusive/collection_fwd.hpp>
#include <sge/sprite/intrusive/connection_fwd.hpp>
#include <sge/sprite/intrusive/range_fwd.hpp>
#include <sge/sprite/intrusive/detail/connection_decl.hpp>
#include <sge/sprite/intrusive/detail/list.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace sprite
{
namespace intrusive
{

template<
	typename Choices
>
class collection
{
	FCPPT_NONCOPYABLE(
		collection
	);
public:
	typedef sge::sprite::object<
		Choices
	> object;

	typedef sge::sprite::intrusive::connection<
		Choices
	> connection_type;

	collection();

	~collection();

	connection_type &
	connection();

	typedef sge::sprite::intrusive::range<
		Choices,
		false
	> range_type;

	typedef sge::sprite::intrusive::range<
		Choices,
		true
	> const_range_type;

	range_type const
	range();

	const_range_type const
	range() const;
private:
	typedef typename sge::sprite::intrusive::detail::list<
		Choices
	>::type list;

	list sprites_;

	sge::sprite::count count_;

	typedef sge::sprite::intrusive::detail::connection<
		Choices
	> connection_impl;

	connection_impl connection_;
};

}
}
}

#endif
