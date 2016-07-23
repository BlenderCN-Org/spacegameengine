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


#include <sge/renderer/exception.hpp>
#include <sge/renderer/impl/is_epsilon_equal.hpp>
#include <sge/renderer/impl/projection/check_near.hpp>
#include <sge/renderer/projection/near.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/text.hpp>


void
sge::renderer::impl::projection::check_near(
	sge::renderer::projection::near const _near
)
{
	if(
		sge::renderer::impl::is_epsilon_equal(
			_near.get(),
			fcppt::literal<
				sge::renderer::scalar
			>(
				0
			)
		)
	)
		throw
			sge::renderer::exception{
				FCPPT_TEXT("projection: near must not be 0!")
			};
}
