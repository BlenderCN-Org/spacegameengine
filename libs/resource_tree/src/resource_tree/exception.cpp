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


#include <sge/core/exception.hpp>
#include <sge/resource_tree/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/information_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::resource_tree::exception::exception(
	fcppt::string &&_what
)
:
	sge::core::exception(
		FCPPT_TEXT("resource_tree: ")
		+
		std::move(
			_what
		)
	)
{
}

sge::resource_tree::exception::exception(
	fcppt::assert_::information const &_info
)
:
	sge::core::exception(
		_info
	)
{
}

sge::resource_tree::exception::exception(
	exception &&
)
= default;

sge::resource_tree::exception::exception(
	exception const &
)
= default;

sge::resource_tree::exception &
sge::resource_tree::exception::operator=(
	exception &&
)
= default;

sge::resource_tree::exception &
sge::resource_tree::exception::operator=(
	exception const &
)
= default;

sge::resource_tree::exception::~exception() noexcept
{
}
