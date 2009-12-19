/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "unlimited_text_size.hpp"
#include <sge/gui/dim.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <sge/font/object.hpp>
#include <sge/font/dim.hpp>
#include <sge/font/unit.hpp>
#include <sge/font/text_size.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <limits>

sge::gui::dim const sge::gui::utility::unlimited_text_size(
	font::metrics_ptr const f,
	string const &t)
{
	return math::dim::structure_cast<dim>(
		font::object(f).text_size(
			t,
			font::dim(
				std::numeric_limits<font::unit>::max(),
				std::numeric_limits<font::unit>::max()
			)
		).size()
	);
}
