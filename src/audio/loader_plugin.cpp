/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/audio/loader.hpp>
#include <sge/audio/loader_plugin.hpp>
#include <sge/src/plugin/address_name.hpp>
#include <sge/src/plugin/instantiate_types.hpp>


sge::plugin::detail::address_name
sge::plugin::detail::traits<sge::audio::loader>::plugin_loader_name()
{
	return SGE_PLUGIN_ADDRESS_NAME("create_audio_loader");
}

sge::plugin::capabilities::type
sge::plugin::detail::traits<sge::audio::loader>::plugin_type()
{
	return capabilities::audio_loader;
}

#if 0
SGE_PLUGIN_INSTANTIATE_TYPES(
	sge::audio::loader
)

#endif

template __attribute__ ((visibility("default"))) sge::plugin::iterator<sge::audio::loader> sge::plugin::manager::begin<sge::audio::loader>();

template __attribute__ ((visibility("default"))) sge::plugin::iterator<sge::audio::loader> sge::plugin::manager::end<sge::audio::loader>();

template __attribute__ ((visibility("default"))) sge::plugin::context<sge::audio::loader> sge::plugin::manager::plugin<sge::audio::loader>( sge::plugin::manager::size_type);

template __attribute__ ((visibility("default"))) sge::plugin::manager::size_type sge::plugin::manager::size<sge::audio::loader>() const;

template class __attribute__ ((visibility("default"))) sge::plugin::iterator<sge::audio::loader>;

template class __attribute__ ((visibility("default"))) sge::plugin::object<sge::audio::loader>;

template class __attribute__ ((visibility("default"))) sge::plugin::context<sge::audio::loader>;
