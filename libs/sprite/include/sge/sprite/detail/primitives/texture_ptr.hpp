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


#ifndef SGE_SPRITE_DETAIL_PRIMITIVES_TEXTURE_PTR_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_PRIMITIVES_TEXTURE_PTR_HPP_INCLUDED

#include <sge/sprite/config/texture_ownership_fwd.hpp>
#include <sge/sprite/detail/transform_texture_levels_static.hpp>
#include <sge/sprite/detail/primitives/texture_ref_type.hpp>
#include <sge/sprite/roles/texture.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/functions/lambda/bind.hpp>
#include <brigand/types/args.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace primitives
{

template<
	typename Choices,
	typename Levels,
	sge::sprite::config::texture_ownership Ownership
>
struct texture_ptr
{
private:
	template<
		typename Level
	>
	using
	make_role
	=
	fcppt::record::element<
		sge::sprite::roles::texture<
			Level::value
		>,
		typename
		sge::sprite::detail::primitives::texture_ref_type<
			Ownership
		>::type
	>;
public:
	typedef
	sge::sprite::detail::transform_texture_levels_static<
		brigand::bind<
			make_role,
			brigand::_1
		>,
		Levels
	>
	type;
};

}
}
}
}

#endif
