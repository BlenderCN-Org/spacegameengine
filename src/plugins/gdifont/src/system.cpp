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


#include <sge/font/object.hpp>
#include <sge/font/object_unique_ptr.hpp>
#include <sge/font/parameters_fwd.hpp>
#include <sge/font/system.hpp>
#include <sge/gdifont/object.hpp>
#include <sge/gdifont/system.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>


sge::gdifont::system::system()
:
	sge::font::system(),
	device_context_()
{
}

sge::gdifont::system::~system()
{
}

sge::font::object_unique_ptr
sge::gdifont::system::create_font(
	sge::font::parameters const &_parameters
)
{
	return
		sge::font::object_unique_ptr(
			fcppt::make_unique_ptr<
				sge::gdifont::object
			>(
				fcppt::cref(
					device_context_
				),
				fcppt::cref(
					_parameters
				)
			)
		);
}
