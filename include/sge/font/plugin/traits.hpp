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


#ifndef SGE_FONT_PLUGIN_TRAITS_HPP_INCLUDED
#define SGE_FONT_PLUGIN_TRAITS_HPP_INCLUDED

#include <sge/font/symbol.hpp>
#include <sge/font/system_fwd.hpp>
#include <sge/font/system_unique_ptr.hpp>
#include <sge/plugin/capabilities_fwd.hpp>
#include <sge/plugin/detail/address_name.hpp>
#include <sge/plugin/detail/traits.hpp>


namespace sge
{
namespace plugin
{
namespace detail
{

template<>
struct traits<
	sge::font::system
>
{
	SGE_FONT_SYMBOL
	static
	sge::plugin::detail::address_name
	plugin_loader_name();

	SGE_FONT_SYMBOL
	static
	sge::plugin::capabilities
	plugin_type();

	typedef sge::font::system_unique_ptr
	(*loader_fun)();
};

}
}
}

#endif
