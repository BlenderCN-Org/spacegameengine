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


#ifndef SGE_IMAGE_VIEW_ELEMENTS_HPP_INCLUDED
#define SGE_IMAGE_VIEW_ELEMENTS_HPP_INCLUDED

#include <sge/image/view/detail/view_types.hpp>
#include <sge/image/color/elements.hpp>
#include <sge/image/raw_pointer.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/mpl/back_inserter.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/copy.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/quote.hpp>
#include <boost/mpl/bind.hpp>

namespace sge
{
namespace image
{
namespace view
{

// TODO: gcc-4.5: Check if this is a gcc bug

typedef boost::mpl::fold<
	color::elements,
	boost::mpl::vector0<>,
	boost::mpl::bind<
		boost::mpl::quote2<
			boost::mpl::copy
		>,
		boost::mpl::bind<
			boost::mpl::quote1<
				detail::view_types
			>,
			boost::mpl::_2
		>,
		boost::mpl::bind<
			boost::mpl::quote1<
				boost::mpl::back_inserter
			>,
			boost::mpl::_1
		>
	>
>::type elements;

}
}
}

#endif
