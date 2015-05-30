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


#ifndef SGE_IMAGE_COLOR_ANY_OBJECT_HPP_INCLUDED
#define SGE_IMAGE_COLOR_ANY_OBJECT_HPP_INCLUDED

#include <sge/image/mizuiro_color.hpp>
#include <sge/image/color/any/elements.hpp>
#include <sge/image/color/any/object_fwd.hpp>
#include <sge/image/color/detail/symbol.hpp>
#include <fcppt/variant/object_impl.hpp>


namespace sge
{
namespace image
{
namespace color
{
namespace any
{

class object
{
public:
	typedef fcppt::variant::object<
		sge::image::color::any::elements
	> variant;

	SGE_IMAGE_COLOR_DETAIL_SYMBOL
	explicit
	object(
		variant const &
	);

	SGE_IMAGE_COLOR_DETAIL_SYMBOL
	object(
		object const &
	);

	SGE_IMAGE_COLOR_DETAIL_SYMBOL
	object &
	operator=(
		object const &
	);

	SGE_IMAGE_COLOR_DETAIL_SYMBOL
	~object();

	SGE_IMAGE_COLOR_DETAIL_SYMBOL
	variant const &
	get() const;
private:
	variant variant_;
};

}
}
}
}

#endif
