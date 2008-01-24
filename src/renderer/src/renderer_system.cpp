/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../renderer_system.hpp"

sge::renderer_parameters::renderer_parameters(const display_mode& mode,
                                              const bool windowed,
                                              const multi_sample_type samples,
                                              const bool vsync)
: mode(mode),
  windowed(windowed),
  samples(samples),
  vsync(vsync)
{}

sge::detail::address_name sge::detail::plugin_traits<sge::renderer_system>::plugin_loader_name()
{
	return SGE_ADDRESS_NAME("create_renderer_system");
}

sge::plugin_type::type sge::detail::plugin_traits<sge::renderer_system>::get_plugin_type()
{
	return plugin_type::renderer;
}

