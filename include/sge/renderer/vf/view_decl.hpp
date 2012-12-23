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


#ifndef SGE_RENDERER_VF_VIEW_DECL_HPP_INCLUDED
#define SGE_RENDERER_VF_VIEW_DECL_HPP_INCLUDED

#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vf/iterator_fwd.hpp>
#include <sge/renderer/vf/pointer.hpp>
#include <sge/renderer/vf/view_fwd.hpp>
#include <sge/renderer/vf/dynamic/basic_view_fwd.hpp>
#include <fcppt/nonassignable.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{

template<
	typename Part,
	typename Constness
>
class view
{
	FCPPT_NONASSIGNABLE(
		view
	);
public:
	typedef sge::renderer::vf::iterator<
		Part,
		Constness
	> iterator;

	typedef typename sge::renderer::vf::pointer<
		Constness
	>::type pointer;

	typedef sge::renderer::vf::dynamic::basic_view<
		pointer
	> dynamic_view_type;

	typedef sge::renderer::vertex::count size_type;

	explicit
	view(
		dynamic_view_type const &
	);

	template<
		typename OtherView
	>
	explicit
	view(
		sge::renderer::vf::dynamic::basic_view<
			OtherView
		> const &
	);

	iterator
	begin() const;

	iterator
	end() const;
private:
	pointer const data_;

	size_type const size_;
};

}
}
}

#endif
