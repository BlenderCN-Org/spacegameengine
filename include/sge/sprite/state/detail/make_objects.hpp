/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SPRITE_STATE_DETAIL_MAKE_OBJECTS_HPP_INCLUDED
#define SGE_SPRITE_STATE_DETAIL_MAKE_OBJECTS_HPP_INCLUDED

#include <sge/sprite/state/render_device.hpp>
#include <sge/sprite/state/detail/make_one_object.hpp>
#include <sge/sprite/state/detail/object_class.hpp>
#include <sge/sprite/state/detail/parameters_class.hpp>
#include <fcppt/no_init.hpp>
#include <fcppt/mpl/for_each.hpp>


namespace sge
{
namespace sprite
{
namespace state
{
namespace detail
{

template<
	typename StateChoices
>
sge::sprite::state::detail::object_class<
	StateChoices
>
make_objects(
	sge::sprite::state::render_device<
		StateChoices
	> &_device,
	sge::sprite::state::detail::parameters_class<
		StateChoices
	> const &_parameters
)
{
	// TODO: Initialize this properly!
	sge::sprite::state::detail::object_class<
		StateChoices
	> result{
		fcppt::no_init()
	};

	fcppt::mpl::for_each<
		typename
		StateChoices::optional_elements
	>(
		sge::sprite::state::detail::make_one_object<
			StateChoices
		>(
			result,
			_device,
			_parameters
		)
	);

	return
		result;
}

}
}
}
}

#endif
