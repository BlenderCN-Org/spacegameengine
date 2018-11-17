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


#ifndef SGE_SYSTEMS_IMPL_ANY_VISITOR_HPP_INCLUDED
#define SGE_SYSTEMS_IMPL_ANY_VISITOR_HPP_INCLUDED

#include <sge/systems/audio_loader_fwd.hpp>
#include <sge/systems/audio_player_fwd.hpp>
#include <sge/systems/config_fwd.hpp>
#include <sge/systems/font_fwd.hpp>
#include <sge/systems/image2d_fwd.hpp>
#include <sge/systems/input_fwd.hpp>
#include <sge/systems/window_fwd.hpp>
#include <sge/systems/detail/instance_impl_fwd.hpp>
#include <sge/systems/detail/renderer_fwd.hpp>
#include <fcppt/reference_impl.hpp>


namespace sge
{
namespace systems
{
namespace impl
{

class any_visitor
{
public:
	explicit
	any_visitor(
		sge::systems::detail::instance_impl &
	);

	void
	operator()(
		sge::systems::config const &
	) const;

	void
	operator()(
		sge::systems::detail::renderer const &
	) const;

	void
	operator()(
		sge::systems::window const &
	) const;

	void
	operator()(
		sge::systems::image2d const &
	) const;

	void
	operator()(
		sge::systems::audio_loader const &
	) const;

	void
	operator()(
		sge::systems::audio_player const &
	) const;

	void
	operator()(
		sge::systems::input const &
	) const;

	void
	operator()(
		sge::systems::font const &
	) const;
private:
	fcppt::reference<
		sge::systems::detail::instance_impl
	> impl_;
};

}
}
}

#endif
