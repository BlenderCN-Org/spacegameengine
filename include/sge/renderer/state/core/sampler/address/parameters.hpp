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


#ifndef SGE_RENDERER_STATE_CORE_SAMPLER_ADDRESS_PARAMETERS_HPP_INCLUDED
#define SGE_RENDERER_STATE_CORE_SAMPLER_ADDRESS_PARAMETERS_HPP_INCLUDED

#include <sge/renderer/symbol.hpp>
#include <sge/renderer/state/core/sampler/address/mode_s.hpp>
#include <sge/renderer/state/core/sampler/address/mode_t.hpp>
#include <sge/renderer/state/core/sampler/address/mode_u.hpp>
#include <sge/renderer/state/core/sampler/address/parameters_fwd.hpp>


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
namespace address
{

class parameters
{
public:
	parameters(
		sge::renderer::state::core::sampler::address::mode_s,
		sge::renderer::state::core::sampler::address::mode_t,
		sge::renderer::state::core::sampler::address::mode_u
	);

	SGE_RENDERER_SYMBOL
	sge::renderer::state::core::sampler::address::mode_s const
	mode_s() const;

	SGE_RENDERER_SYMBOL
	sge::renderer::state::core::sampler::address::mode_t const
	mode_t() const;

	SGE_RENDERER_SYMBOL
	sge::renderer::state::core::sampler::address::mode_u const
	mode_u() const;
private:
	sge::renderer::state::core::sampler::address::mode_s mode_s_;

	sge::renderer::state::core::sampler::address::mode_t mode_t_;

	sge::renderer::state::core::sampler::address::mode_u mode_u_;
};

SGE_RENDERER_SYMBOL
bool
operator==(
	sge::renderer::state::core::sampler::address::parameters const &,
	sge::renderer::state::core::sampler::address::parameters const &
);

}
}
}
}
}
}

#endif
