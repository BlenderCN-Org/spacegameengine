/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_PLUGIN_DETAIL_ITERATOR_BASE_TYPE_HPP_INCLUDED
#define SGE_PLUGIN_DETAIL_ITERATOR_BASE_TYPE_HPP_INCLUDED

#include <sge/plugin/context_fwd.hpp>
#include <sge/plugin/iterator_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <iterator>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace plugin
{
namespace detail
{

template<
	typename Type
>
struct iterator_base_type
{
	typedef boost::iterator_facade<
 		sge::plugin::iterator<
			Type
		>,
		sge::plugin::context<
			Type
		>,
		std::random_access_iterator_tag,
		sge::plugin::context<
			Type
		>
	> type;
};

}
}
}

#endif
