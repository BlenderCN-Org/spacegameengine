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


#ifndef SGE_XCB_WINDOW_ATTRIBUTE_LIST_HPP_INCLUDED
#define SGE_XCB_WINDOW_ATTRIBUTE_LIST_HPP_INCLUDED

#include <sge/xcb/window/attribute_list_fwd.hpp>
#include <sge/xcb/window/attribute.hpp>
#include <sge/xcb/value_mask.hpp>
#include <sge/xcb/symbol.hpp>
#include <fcppt/container/raw_vector_decl.hpp>

namespace sge
{
namespace xcb
{
namespace window
{

class attribute_list
{
public:
	SGE_XCB_SYMBOL
	explicit attribute_list();

	SGE_XCB_SYMBOL
	~attribute_list();

	SGE_XCB_SYMBOL
	attribute const *
	data() const;

	SGE_XCB_SYMBOL
	xcb::value_mask const
	value_mask() const;
private:
	typedef fcppt::container::raw_vector<
		attribute
	> attribute_container;

	attribute_container container_;
};

}
}
}

#endif
