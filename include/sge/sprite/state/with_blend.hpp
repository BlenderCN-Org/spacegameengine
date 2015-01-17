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


#ifndef SGE_SPRITE_STATE_WITH_BLEND_HPP_INCLUDED
#define SGE_SPRITE_STATE_WITH_BLEND_HPP_INCLUDED

#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/state/core/blend/object.hpp>
#include <sge/renderer/state/core/blend/object_unique_ptr.hpp>
#include <sge/renderer/state/core/blend/write_mask.hpp>
#include <sge/sprite/detail/symbol.hpp>
#include <sge/sprite/state/with_blend_fwd.hpp>
#include <sge/sprite/state/roles/blend.hpp>
#include <sge/sprite/state/roles/blend_write_mask.hpp>
#include <fcppt/optional_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/bool.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace state
{

struct with_blend
{
	typedef sge::sprite::state::roles::blend role;

	typedef sge::sprite::state::roles::blend_write_mask parameter_role;

	typedef boost::mpl::false_ needs_ffp;

	typedef boost::mpl::true_ persistent;

	typedef boost::mpl::true_ has_parameter;

	typedef sge::renderer::state::core::blend::object state_type;

	typedef fcppt::optional<
		sge::renderer::state::core::blend::write_mask
	> optional_extra_parameters;

	SGE_SPRITE_DETAIL_SYMBOL
	static
	sge::renderer::state::core::blend::object_unique_ptr
	make(
		sge::renderer::device::core &,
		sge::sprite::state::with_blend::optional_extra_parameters const &
	);

	SGE_SPRITE_DETAIL_SYMBOL
	static
	void
	set(
		sge::renderer::context::core &,
		sge::sprite::state::with_blend::state_type const &
	);

	SGE_SPRITE_DETAIL_SYMBOL
	static
	void
	unset(
		sge::renderer::context::core &
	);
};

}
}
}

#endif
