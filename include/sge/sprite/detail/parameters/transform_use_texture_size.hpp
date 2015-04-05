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


#ifndef SGE_SPRITE_DETAIL_PARAMETERS_TRANSFORM_USE_TEXTURE_SIZE_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_PARAMETERS_TRANSFORM_USE_TEXTURE_SIZE_HPP_INCLUDED

#include <sge/renderer/lock_rect.hpp>
#include <sge/sprite/deref_texture.hpp>
#include <sge/sprite/texture.hpp>
#include <sge/sprite/detail/config/needs_use_texture_size.hpp>
#include <sge/sprite/detail/roles/use_texture_size.hpp>
#include <sge/sprite/roles/size.hpp>
#include <sge/sprite/roles/texture.hpp>
#include <sge/sprite/types/dim.hpp>
#include <sge/texture/part.hpp>
#include <fcppt/maybe_void.hpp>
#include <fcppt/cast/static_cast_fun.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace parameters
{

template<
	typename Choices,
	typename Parameters
>
typename boost::enable_if<
	sge::sprite::detail::config::needs_use_texture_size<
		Choices
	>,
	Parameters
>::type const
transform_use_texture_size(
	Parameters _parameters
)
{
	fcppt::maybe_void(
		_parameters. template get<
			sge::sprite::roles::texture<
				0
			>
		>(),
		[
			&_parameters
		](
			typename
			sge::sprite::texture<
				Choices
			>::value_type const &_texture
		)
		{
			if(
				_parameters. template get<
					sge::sprite::detail::roles::use_texture_size
				>()
			)
				_parameters. template set<
					sge::sprite::roles::size
				>(
					fcppt::math::dim::structure_cast<
						sge::sprite::types::dim<
							typename Choices::type_choices
						>,
						fcppt::cast::static_cast_fun
					>(
						sge::sprite::deref_texture(
							_texture
						).area().size()
					)
				);
		}
	);

	return
		_parameters;
}

template<
	typename Choices,
	typename Parameters
>
typename boost::disable_if<
	sge::sprite::detail::config::needs_use_texture_size<
		Choices
	>,
	Parameters
>::type const
transform_use_texture_size(
	Parameters const &_parameters
)
{
	return
		_parameters;
}

}
}
}
}

#endif
