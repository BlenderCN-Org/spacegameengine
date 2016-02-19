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


#ifndef SGE_SCENIC_INDEX_BUFFER_RANGE_HPP_INCLUDED
#define SGE_SCENIC_INDEX_BUFFER_RANGE_HPP_INCLUDED

#include <sge/renderer/index/count.hpp>
#include <sge/renderer/index/first.hpp>
#include <sge/scenic/detail/symbol.hpp>


namespace sge
{
namespace scenic
{
class index_buffer_range
{
public:
	SGE_SCENIC_DETAIL_SYMBOL
	index_buffer_range(
		sge::renderer::index::first const &,
		sge::renderer::index::count const &);

	SGE_SCENIC_DETAIL_SYMBOL
	sge::renderer::index::first const &
	first_index() const;

	SGE_SCENIC_DETAIL_SYMBOL
	sge::renderer::index::count const &
	index_count() const;
private:
	sge::renderer::index::first first_index_;
	sge::renderer::index::count index_count_;
};
}
}

#endif
