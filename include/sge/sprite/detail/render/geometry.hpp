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


#ifndef SGE_SPRITE_DETAIL_RENDER_GEOMETRY_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_RENDER_GEOMETRY_HPP_INCLUDED

#include <sge/sprite/geometry/sort_and_update.hpp>
#include <sge/sprite/geometry/update.hpp>
#include <sge/sprite/detail/render/is_same_geometry_options.hpp>
#include <sge/sprite/render/geometry_options.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace render
{

template<
	sge::sprite::render::geometry_options::type Options,
	typename Range,
	typename Buffers,
	typename Compare
>
typename boost::enable_if<
	sge::sprite::detail::render::is_same_geometry_options<
		Options,
		sge::sprite::render::geometry_options::sort_and_fill
	>,
	void
>::type
geometry(
	Range const &_range,
	Buffers &_buffers,
	Compare const &_compare
)
{
	sge::sprite::geometry::sort_and_update(
		_range,
		_buffers,
		_compare
	);
}

template<
	sge::sprite::render::geometry_options::type Options,
	typename Range,
	typename Buffers,
	typename Compare
>
typename boost::enable_if<
	sge::sprite::detail::render::is_same_geometry_options<
		Options,
		sge::sprite::render::geometry_options::fill
	>,
	void
>::type
geometry(
	Range const &_range,
	Buffers &_buffers,
	Compare const &
)
{
	sge::sprite::geometry::update(
		_range,
		_buffers
	);
}

template<
	sge::sprite::render::geometry_options::type Options,
	typename Range,
	typename Buffers,
	typename Compare
>
typename boost::enable_if<
	sge::sprite::detail::render::is_same_geometry_options<
		Options,
		sge::sprite::render::geometry_options::nothing
	>,
	void
>::type
geometry(
	Range const &,
	Buffers &,
	Compare const &
)
{
}

}
}
}
}

#endif
