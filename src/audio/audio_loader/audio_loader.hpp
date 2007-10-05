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


#ifndef SGE_AUDIO_LOADER_HPP_INCLUDED
#define SGE_AUDIO_LOADER_HPP_INCLUDED

// C++
#include <string>
// sge
#include "../../shared_ptr.hpp"
#include "../../plugin_traits.hpp"
// Own stuff
#include "audio_file.hpp"

namespace sge
{
class audio_loader
{
public:
	virtual shared_ptr<audio_file> load(const std::string &filename) = 0;
	virtual bool is_valid_file(const std::string &filename) const = 0;
	virtual ~audio_loader() {}
};

namespace detail
{

template<> struct plugin_traits<audio_loader> {
	static const char* plugin_loader_name() { return "create_audio_loader"; }
	static plugin_type::type get_plugin_type() { return plugin_type::audio_loader; }
	typedef audio_loader* (*loader_fun)();
};

}

}

#endif // AUDIO_HPP
