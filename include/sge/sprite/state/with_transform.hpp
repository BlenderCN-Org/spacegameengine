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


#ifndef SGE_SPRITE_STATE_WITH_TRANSFORM_HPP_INCLUDED
#define SGE_SPRITE_STATE_WITH_TRANSFORM_HPP_INCLUDED

#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/state/ffp/transform/object.hpp>
#include <sge/renderer/state/ffp/transform/object_unique_ptr.hpp>
#include <sge/sprite/detail/symbol.hpp>
#include <sge/sprite/state/with_transform_fwd.hpp>
#include <sge/sprite/state/roles/transform.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/bool.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace state
{

struct with_transform
{
	typedef sge::sprite::state::roles::transform role;

	typedef boost::mpl::true_ needs_ffp;

	typedef boost::mpl::false_ persistent;

	typedef boost::mpl::false_ has_parameter;

	typedef sge::renderer::state::ffp::transform::object state_type;

	SGE_SPRITE_DETAIL_SYMBOL
	static
	sge::renderer::state::ffp::transform::object_unique_ptr
	make(
		sge::renderer::device::ffp &,
		sge::renderer::context::ffp &
	);

	SGE_SPRITE_DETAIL_SYMBOL
	static
	void
	set(
		sge::renderer::context::ffp &,
		sge::sprite::state::with_transform::state_type const &
	);

	SGE_SPRITE_DETAIL_SYMBOL
	static
	void
	unset(
		sge::renderer::context::ffp &
	);
};

}
}
}

#endif
