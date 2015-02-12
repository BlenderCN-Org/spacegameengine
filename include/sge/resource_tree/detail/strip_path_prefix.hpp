/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_RESOURCE_TREE_DETAIL_STRIP_PATH_PREFIX_HPP_INCLUDED
#define SGE_RESOURCE_TREE_DETAIL_STRIP_PATH_PREFIX_HPP_INCLUDED

#include <sge/resource_tree/path_fwd.hpp>
#include <sge/resource_tree/detail/base_path.hpp>
#include <sge/resource_tree/detail/sub_path.hpp>
#include <sge/resource_tree/detail/symbol.hpp>


namespace sge
{
namespace resource_tree
{
namespace detail
{

SGE_RESOURCE_TREE_DETAIL_SYMBOL
sge::resource_tree::path
strip_path_prefix(
	sge::resource_tree::detail::base_path const &,
	sge::resource_tree::detail::sub_path const &);

}
}
}

#endif
