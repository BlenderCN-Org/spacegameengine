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


#ifndef SGE_BVH_BOUNDING_BOX_HPP_INCLUDED
#define SGE_BVH_BOUNDING_BOX_HPP_INCLUDED

#include <sge/bvh/traits/box.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/math/box/extend_bounding_box.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace bvh
{
template<typename Traits>
typename Traits::box const
bounding_box(
	typename Traits::leaf_wrapper_sequence const &_leaves)
{
	FCPPT_ASSERT_PRE(
		!_leaves.empty());

	typename Traits::box result =
		sge::bvh::traits::box<typename Traits::leaf>::extract_box(
			_leaves.front().value());

	for(
		typename Traits::leaf_wrapper_sequence::const_iterator it =
			boost::next(
				_leaves.begin());
		it != _leaves.end();
		++it)
		result =
			fcppt::math::box::extend_bounding_box(
				result,
				sge::bvh::traits::box<typename Traits::leaf>::extract_box(
					it->value()));

	return
		result;
}
}
}

#endif
