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



#ifndef SGE_AUDIO_MULTI_LOADER_HPP_INCLUDED
#define SGE_AUDIO_MULTI_LOADER_HPP_INCLUDED

#include <sge/audio/multi_loader_fwd.hpp>
#include <sge/audio/loader_fwd.hpp>
#include <sge/audio/file_fwd.hpp>
#include <sge/filesystem/path.hpp>
#include <sge/plugin/context.hpp>
#include <sge/noncopyable.hpp>
#include <vector>

namespace sge
{
namespace plugin
{
class manager;
}

namespace audio
{

class SGE_CLASS_SYMBOL multi_loader 
{
	SGE_NONCOPYABLE(multi_loader)
public:
	SGE_SYMBOL explicit multi_loader(
		plugin::manager &);
	SGE_SYMBOL ~multi_loader();

	SGE_SYMBOL file_ptr const
	load(
		filesystem::path const &);
private:
	typedef std::vector<
		plugin::context<
			loader
		>::ptr_type
	> plugin_container;

	typedef std::vector<
		loader_ptr
	> loader_container;

	plugin_container plugins;
	loader_container loaders;
};

}
}

#endif
