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


#ifndef SGE_SPRITE_CONFIG_INTRUSIVE_HPP_INCLUDED
#define SGE_SPRITE_CONFIG_INTRUSIVE_HPP_INCLUDED

#include <sge/sprite/config/intrusive_fwd.hpp>
#include <sge/sprite/intrusive/connection_ref.hpp>
#include <sge/sprite/roles/connection.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/sequences/list.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace config
{

struct intrusive
{
	template<
		typename Choices
	>
	struct apply
	{
		typedef
		brigand::list<
			fcppt::record::element<
				sge::sprite::roles::connection,
				sge::sprite::intrusive::connection_ref<
					Choices
				>
			>
		>
		type;
	};
};

}
}
}

#endif
