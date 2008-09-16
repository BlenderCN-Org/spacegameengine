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


#ifndef SGE_AUDIO_MULTI_LOADER_HPP_INCLUDED
#define SGE_AUDIO_MULTI_LOADER_HPP_INCLUDED

#include "loader.hpp"
#include "../../path.hpp"
#include "../../plugin/manager.hpp"
#include <boost/noncopyable.hpp>
#include <vector>

namespace sge
{
namespace audio
{
class SGE_CLASS_SYMBOL multi_loader : boost::noncopyable 
{
public:
	SGE_SYMBOL multi_loader(plugin::manager&);
	SGE_SYMBOL file_ptr const load(path const&);
private:
	typedef std::vector<plugin::context<loader>::ptr_type> plugin_container;
  typedef std::vector<loader_ptr> loader_container;

	plugin_container plugins;
	loader_container loaders;
};

}
}

#endif // AUDIO_HPP
