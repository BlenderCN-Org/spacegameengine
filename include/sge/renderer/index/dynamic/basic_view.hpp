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


#ifndef SGE_RENDERER_INDEX_DYNAMIC_BASIC_VIEW_HPP_INCLUDED
#define SGE_RENDERER_INDEX_DYNAMIC_BASIC_VIEW_HPP_INCLUDED

#include <sge/renderer/const_raw_pointer.hpp>
#include <sge/renderer/raw_pointer.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/index/dynamic/basic_view_fwd.hpp>
#include <sge/renderer/index/dynamic/format.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/if.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace renderer
{
namespace index
{
namespace dynamic
{

template<
	bool IsConst
>
class basic_view
{
public:
	typedef typename boost::mpl::if_c<
		IsConst,
		sge::renderer::const_raw_pointer,
		sge::renderer::raw_pointer
	>::type pointer;

	typedef renderer::size_type size_type;

	SGE_RENDERER_DETAIL_SYMBOL
	basic_view(
		pointer,
		size_type,
		sge::renderer::index::dynamic::format
	);

	SGE_RENDERER_DETAIL_SYMBOL
	pointer
	data() const;

	SGE_RENDERER_DETAIL_SYMBOL
	size_type
	size() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::index::dynamic::format
	format() const;
private:
	pointer data_;

	size_type size_;

	sge::renderer::index::dynamic::format format_;
};

}
}
}
}

#endif
