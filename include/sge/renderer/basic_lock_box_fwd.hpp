/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RENDERER_BASIC_LOCK_BOX_FWD_HPP_INCLUDED
#define SGE_RENDERER_BASIC_LOCK_BOX_FWD_HPP_INCLUDED

#include <sge/renderer/size_type.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/math/box/object_fwd.hpp>


namespace sge
{
namespace renderer
{

/**
 * \brief Typedef helper for renderer::lock_rect and renderer::lock_box
 *
 * Creates a box with value type renderer::size_type.
 *
 * \tparam Size The dimension to use
*/
template<
	fcppt::math::size_type Size
>
struct basic_lock_box
{
	typedef fcppt::math::box::object<
		sge::renderer::size_type,
		Size
	> type;
};

}
}

#endif
