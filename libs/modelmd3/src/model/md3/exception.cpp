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
#include <sge/model/md3/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::model::md3::exception::exception(
	fcppt::string &&_what
)
:
	sge::core::exception(
		FCPPT_TEXT("md3: ")
		+
		std::move(
			_what
		)
	)
{
}

sge::model::md3::exception::exception(
	exception &&
)
= default;

sge::model::md3::exception::exception(
	exception const &
)
= default;

sge::model::md3::exception &
sge::model::md3::exception::operator=(
	exception &&
)
= default;

sge::model::md3::exception &
sge::model::md3::exception::operator=(
	exception const &
)
= default;

sge::model::md3::exception::~exception() noexcept
{
}
