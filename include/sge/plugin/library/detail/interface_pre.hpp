/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_PLUGIN_LIBRARY_DETAIL_INTERFACE_PRE_HPP_INCLUDED
#define SGE_PLUGIN_LIBRARY_DETAIL_INTERFACE_PRE_HPP_INCLUDED

#include <sge/plugin/library/function_map.hpp>
#include <fcppt/config/platform.hpp>


#if defined(FCPPT_CONFIG_POSIX_PLATFORM)
#include <fcppt/symbol/export.hpp>

#define SGE_PLUGIN_LIBRARY_DETAIL_INTERFACE_PRE \
extern "C" \
{ \
FCPPT_SYMBOL_EXPORT \
sge::plugin::library::function_map sge_plugin_functions(

#elif defined(FCPPT_CONFIG_WINDOWS_PLATFORM)

#define SGE_PLUGIN_LIBRARY_DETAIL_INTERFACE_PRE \
namespace \
{ \
sge::plugin::library::function_map sge_plugin_functions_global(

#else
#error "Don't know what the library interface should look like!"
#endif

#endif
