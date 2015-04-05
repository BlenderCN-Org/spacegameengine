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


#include <sge/src/systems/extract_config.hpp>
#include <sge/systems/config.hpp>
#include <sge/systems/detail/any.hpp>
#include <sge/systems/detail/any_key.hpp>
#include <sge/systems/detail/any_map.hpp>
#include <fcppt/maybe.hpp>
#include <fcppt/container/find_opt.hpp>
#include <fcppt/variant/get_exn.hpp>


sge::systems::config
sge::systems::extract_config(
	sge::systems::detail::any_map const &_map
)
{
	return
		fcppt::maybe(
			fcppt::container::find_opt(
				_map,
				sge::systems::detail::any_key::config
			),
			[]{
				return
					sge::systems::config();
			},
			[](
				sge::systems::detail::any const &_config
			)
			{
				return
					fcppt::variant::get_exn<
						sge::systems::config
					>(
						_config
					);
			}

		);
}
