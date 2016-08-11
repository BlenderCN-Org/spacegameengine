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


#include <sge/x11input/xim/get_im_values.hpp>
#include <sge/x11input/xim/get_supported_styles.hpp>
#include <sge/x11input/xim/method_fwd.hpp>
#include <sge/x11input/xim/supported_styles_unique_ptr.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/X.h>
#include <fcppt/config/external_end.hpp>


sge::x11input::xim::supported_styles_unique_ptr
sge::x11input::xim::get_supported_styles(
	sge::x11input::xim::method const &_method
)
{
	XIMStyles *result{
		nullptr
	};

	sge::x11input::xim::get_im_values(
		_method,
		XNQueryInputStyle,
		&result
	);

	FCPPT_ASSERT_ERROR(
		result
		!=
		nullptr
	);

	return
		sge::x11input::xim::supported_styles_unique_ptr{
			result
		};
}
