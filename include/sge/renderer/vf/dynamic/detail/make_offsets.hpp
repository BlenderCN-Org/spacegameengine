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


#ifndef SGE_RENDERER_VF_DYNAMIC_DETAIL_MAKE_OFFSETS_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_DETAIL_MAKE_OFFSETS_HPP_INCLUDED

#include <sge/renderer/vf/vertex_size.hpp>
#include <sge/renderer/vf/dynamic/offset.hpp>
#include <sge/renderer/vf/dynamic/offset_list.hpp>
#include <fcppt/nonassignable.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{
namespace dynamic
{
namespace detail
{

class make_offsets
{
	FCPPT_NONASSIGNABLE(
		make_offsets
	);
public:
	explicit
	make_offsets(
		sge::renderer::vf::dynamic::offset_list &_offsets
	)
	:
		offsets_(
			_offsets
		)
	{
	}

	typedef void result_type;

	result_type
	operator()(
		sge::renderer::vf::vertex_size const &_value
	) const
	{
		offsets_.push_back(
			sge::renderer::vf::dynamic::offset(
				_value
			)
		);
	}
private:
	sge::renderer::vf::dynamic::offset_list &offsets_;
};

}
}
}
}
}

#endif
