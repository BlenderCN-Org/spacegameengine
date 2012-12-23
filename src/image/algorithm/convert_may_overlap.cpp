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


#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/src/image/algorithm/convert_may_overlap.hpp>
#include <mizuiro/image/algorithm/may_overlap.hpp>
#include <fcppt/assert/unreachable.hpp>


mizuiro::image::algorithm::may_overlap::type
sge::image::algorithm::convert_may_overlap(
	sge::image::algorithm::may_overlap const _may_overlap
)
{
	switch(
		_may_overlap
	)
	{
	case sge::image::algorithm::may_overlap::no:
		return mizuiro::image::algorithm::may_overlap::no;
	case sge::image::algorithm::may_overlap::yes:
		return mizuiro::image::algorithm::may_overlap::yes;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
