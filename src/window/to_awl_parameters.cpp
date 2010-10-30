/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/window/to_awl_parameters.hpp>
#include <sge/window/parameters.hpp>
#include <awl/window/dim.hpp>
#include <awl/window/parameters.hpp>
#include <fcppt/assert.hpp>
#include <fcppt/optional_impl.hpp>

awl::window::parameters const
sge::window::to_awl_parameters(
	sge::window::parameters const &_param
)
{
	FCPPT_ASSERT(
		_param.dim()
	)

	// TODO: add the io_service!
	return
		awl::window::parameters()
		.title(
			_param.title()
		)
		.class_name(
			_param.class_name()
		)
		.size(
			awl::window::dim(
				static_cast<
					awl::window::scalar
				>(
					_param.dim()->w()
				),
				static_cast<
					awl::window::scalar
				>(
					_param.dim()->h()
				)
			)
		);
}
