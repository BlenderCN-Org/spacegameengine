/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SPRITE_DEFAULT_EQUAL_HPP_INCLUDED
#define SGE_SPRITE_DEFAULT_EQUAL_HPP_INCLUDED

#include <sge/sprite/compare_depth.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/with_depth.hpp>
#include <sge/sprite/with_texture.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/or.hpp>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{

struct default_equal
{
	typedef bool result_type;

	template<
		typename Object
	>
	typename boost::enable_if<
		boost::mpl::and_<
			boost::mpl::contains<
				typename Object::elements,
				with_texture
			>,
			boost::mpl::contains<
				typename Object::elements,
				with_depth
			>
		>,
		result_type
	>::type
	operator()(
		Object const &a,
		Object const &b
	) const
	{
		return
			sprite::compare_depth(a, b)
			&& a.texture() == b.texture();

	}

	template<
		typename Object
	>
	typename boost::enable_if<
		boost::mpl::and_<
			boost::mpl::contains<
				typename Object::elements,
				with_depth
			>,
			boost::mpl::not_<
				boost::mpl::contains<
					typename Object::elements,
					with_texture
				>
			>
		>,
		result_type
	>::type
	operator()(
		Object const &a,
		Object const &b
	) const
	{
		return
			sprite::compare_depth(a, b);
	}

	template<
		typename Object
	>
	typename boost::enable_if<
		boost::mpl::and_<
			boost::mpl::contains<
				typename Object::elements,
				with_texture
			>,
			boost::mpl::not_<
				boost::mpl::contains<
					typename Object::elements,
					with_depth
				>
			>
		>,
		result_type
	>::type
	operator()(
		Object const &a,
		Object const &b
	) const
	{
		return
			a.texture() == b.texture();
	}

	template<
		typename Object
	>
	typename boost::enable_if<
		boost::mpl::not_<
			boost::mpl::or_<
				boost::mpl::contains<
					typename Object::elements,
					with_texture
				>,
				boost::mpl::contains<
					typename Object::elements,
					with_depth
				>
			>
		>,
		result_type
	>::type
	operator()(
		Object const &,
		Object const &
	) const
	{
		return true;
	}
};

}
}

#endif
