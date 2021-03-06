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


#include <sge/log/default_level.hpp>
#include <sge/log/default_level_streams.hpp>
#include <sge/systems/optional_log_context_ref.hpp>
#include <sge/systems/impl/log_context.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/log/context.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/variant/match.hpp>


sge::systems::impl::log_context::log_context(
	sge::systems::optional_log_context_ref const _log_context
)
:
	impl_{
		fcppt::optional::maybe(
			_log_context,
			[]{
				return
					variant{
						fcppt::make_unique_ptr<
							fcppt::log::context
						>(
							sge::log::default_level(),
							sge::log::default_level_streams()
						)
					};
			},
			[](
				fcppt::reference<
					fcppt::log::context
				> const _ref
			)
			{
				return
					variant{
						_ref
					};
			}
		)
	}
{
}

sge::systems::impl::log_context::~log_context()
{
}

fcppt::log::context &
sge::systems::impl::log_context::get() const
{
	return
		fcppt::variant::match(
			impl_,
			[](
				fcppt::unique_ptr<
					fcppt::log::context
				> const &_context
			)
			->
			fcppt::log::context &
			{
				return
					*_context;
			},
			[](
				fcppt::reference<
					fcppt::log::context
				> const &_context
			)
			->
			fcppt::log::context &
			{
				return
					_context.get();
			}
		);
}
