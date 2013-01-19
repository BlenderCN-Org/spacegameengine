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


#ifndef SGE_SPRITE_DEFAULTS_COLOR_HPP_INCLUDED
#define SGE_SPRITE_DEFAULTS_COLOR_HPP_INCLUDED

#include <sge/image/color/init.hpp>
#include <sge/sprite/color.hpp>
#include <sge/sprite/defaults/fwd.hpp>
#include <sge/sprite/roles/color.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/bool.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{

template<
	typename Choices
>
struct defaults<
	Choices,
	sge::sprite::roles::color
>
{
	typedef boost::mpl::true_ use;

	typedef typename sge::sprite::color<
		Choices
	>::type type;

	static type const
	get()
	{
		return
			type(
				(sge::image::color::init::red() %= 1.0)
				(sge::image::color::init::green() %= 1.0)
				(sge::image::color::init::blue() %= 1.0)
				(sge::image::color::init::alpha() %= 1.0)
			);
	}
};

}
}

#endif
