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


#ifndef SGE_TEXTURE_AREA_TEXC_HPP_INCLUDED
#define SGE_TEXTURE_AREA_TEXC_HPP_INCLUDED

#include <sge/texture/part_fwd.hpp>
#include <sge/texture/part.hpp>
#include <sge/renderer/lock_rect_to_coords.hpp>
#include <sge/renderer/texture.hpp>
#include <sge/math/dim/arithmetic.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/math/box/basic_impl.hpp>
#include <sge/math/box/rect.hpp>
#include <sge/math/compare.hpp>
#include <sge/log/headers.hpp>
#include <sge/log/global.hpp>
#include <ostream>

namespace sge
{
namespace texture
{

template<
	typename T
>
typename math::box::rect<T>::type const
area_texc(
	const_part_ptr const part,
	T const repeat
)
{
	if(
		!math::compare(
			repeat,
			static_cast<T>(1)
		)
		&& !part->repeatable()
	)
		SGE_LOG_WARNING(
			log::global(),
			log::_
				<< SGE_TEXT("texture not repeatable but repetition is ")
				<< repeat
				<< SGE_TEXT('!')
		);

	typedef typename math::box::rect<
		T
	>::type ret_type;
	
	ret_type ret_(
		renderer::lock_rect_to_coords<
			T
		>(
			part->area(),
			part->texture()->dim()
		)
	);

	ret_.dim(
		ret_.dim() * repeat
	);

	return ret_;
}

}
}

#endif
