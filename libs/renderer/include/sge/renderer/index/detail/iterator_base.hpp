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


#ifndef SGE_RENDERER_INDEX_DETAIL_ITERATOR_BASE_HPP_INCLUDED
#define SGE_RENDERER_INDEX_DETAIL_ITERATOR_BASE_HPP_INCLUDED

#include <sge/renderer/index/const_proxy_fwd.hpp>
#include <sge/renderer/index/difference_type.hpp>
#include <sge/renderer/index/iterator_fwd.hpp>
#include <sge/renderer/index/nonconst_tag.hpp>
#include <sge/renderer/index/proxy_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <iterator>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace renderer
{
namespace index
{
namespace detail
{

template<
	typename Format
>
using
iterator_base
=
boost::iterator_facade<
	sge::renderer::index::iterator<
		Format
	>,
	typename
	Format::index_type,
	std::random_access_iterator_tag,
	typename
	std::conditional<
		std::is_same<
			typename
			Format::constness,
			sge::renderer::index::nonconst_tag
		>::value,
		sge::renderer::index::proxy<
			Format
		>,
		sge::renderer::index::const_proxy<
			Format
		>
	>::type,
	sge::renderer::index::difference_type
>;

}
}
}
}

#endif
