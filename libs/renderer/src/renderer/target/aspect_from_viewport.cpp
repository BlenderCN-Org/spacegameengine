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


#include <sge/renderer/aspect.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/target/aspect_from_viewport.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <fcppt/cast/to_unsigned_fun.hpp>
#include <fcppt/math/dim/structure_cast.hpp>


sge::renderer::scalar
sge::renderer::target::aspect_from_viewport(
	sge::renderer::target::viewport const &_viewport
)
{
	return
		sge::renderer::aspect(
			fcppt::math::dim::structure_cast<
				sge::renderer::screen_size,
				fcppt::cast::to_unsigned_fun
			>(
				_viewport.get().size()
			)
		);
}
