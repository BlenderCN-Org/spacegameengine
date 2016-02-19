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


#include <sge/log/option_container.hpp>
#include <sge/src/systems/any_visitor.hpp>
#include <sge/src/systems/detail/instance_impl.hpp>
#include <sge/systems/audio_loader_fwd.hpp>
#include <sge/systems/audio_player_fwd.hpp>
#include <sge/systems/config_fwd.hpp>
#include <sge/systems/font_fwd.hpp>
#include <sge/systems/image2d_fwd.hpp>
#include <sge/systems/window_fwd.hpp>
#include <sge/systems/detail/input_fwd.hpp>
#include <sge/systems/detail/renderer_fwd.hpp>


sge::systems::any_visitor::any_visitor(
	sge::systems::detail::instance_impl &_impl,
	sge::log::option_container const &_log_options
)
:
	impl_(
		_impl
	),
	log_options_(
		_log_options
	)
{
}

sge::systems::any_visitor::result_type
sge::systems::any_visitor::operator()(
	sge::systems::config const &
) const
{
}

sge::systems::any_visitor::result_type
sge::systems::any_visitor::operator()(
	sge::systems::detail::renderer const &_param
) const
{
	impl_.init_renderer(
		_param
	);
}

sge::systems::any_visitor::result_type
sge::systems::any_visitor::operator()(
	sge::systems::window const &_param
) const
{
	impl_.init_window_object(
		_param
	);
}

sge::systems::any_visitor::result_type
sge::systems::any_visitor::operator()(
	sge::systems::image2d const &_param
) const
{
	impl_.init_image2d(
		_param,
		log_options_
	);
}

sge::systems::any_visitor::result_type
sge::systems::any_visitor::operator()(
	sge::systems::audio_loader const &_param
) const
{
	impl_.init_audio_loader(
		_param,
		log_options_
	);
}

sge::systems::any_visitor::result_type
sge::systems::any_visitor::operator()(
	sge::systems::audio_player const &_param
) const
{
	impl_.init_audio_player(
		_param,
		log_options_
	);
}

sge::systems::any_visitor::result_type
sge::systems::any_visitor::operator()(
	sge::systems::detail::input const &_param
) const
{
	impl_.init_input(
		_param,
		log_options_
	);
}

sge::systems::any_visitor::result_type
sge::systems::any_visitor::operator()(
	sge::systems::font const &_param
) const
{
	impl_.init_font(
		_param,
		log_options_
	);
}
