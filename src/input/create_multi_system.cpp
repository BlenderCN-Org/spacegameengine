/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/input/create_multi_system.hpp>
#include <sge/input/system_unique_ptr.hpp>
#include <sge/input/plugin/collection_fwd.hpp>
#include <sge/src/input/multi_system.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>


sge::input::system_unique_ptr
sge::input::create_multi_system(
	sge::input::plugin::collection const &_collection
)
{
	return
		sge::input::system_unique_ptr(
			fcppt::make_unique_ptr<
				sge::input::multi_system
			>(
				fcppt::cref(
					_collection
				)
			)
		);
}
