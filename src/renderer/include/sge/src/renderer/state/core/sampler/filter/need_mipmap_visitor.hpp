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


#ifndef SGE_SRC_RENDERER_STATE_CORE_SAMPLER_FILTER_NEED_MIPMAP_VISITOR_HPP_INCLUDED
#define SGE_SRC_RENDERER_STATE_CORE_SAMPLER_FILTER_NEED_MIPMAP_VISITOR_HPP_INCLUDED

#include <sge/renderer/state/core/sampler/filter/anisotropic/parameters_fwd.hpp>
#include <sge/renderer/state/core/sampler/filter/normal/parameters_fwd.hpp>
#include <fcppt/nonassignable.hpp>


namespace sge
{
namespace renderer
{
namespace state
{
namespace core
{
namespace sampler
{
namespace filter
{

class need_mipmap_visitor
{
	FCPPT_NONASSIGNABLE(
		need_mipmap_visitor
	);
public:
	typedef bool result_type;

	result_type
	operator()(
		sge::renderer::state::core::sampler::filter::anisotropic::parameters const &
	) const;

	result_type
	operator()(
		sge::renderer::state::core::sampler::filter::normal::parameters const &
	) const;
};

}
}
}
}
}
}

#endif
