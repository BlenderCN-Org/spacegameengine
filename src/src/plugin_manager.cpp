/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <iostream>
#include <boost/filesystem/convenience.hpp>
#include <boost/filesystem/operations.hpp>
#include "../plugin_manager.hpp"
#include "../library.hpp"

typedef void (*version_function)(sge::plugin_info*);
inline version_function get_version_function(sge::library& lib)
{
	return lib.load_function<version_function>("plugin_version_info");
}

const char* const plugin_path = PLUGIN_PATH;
const char* const plugin_extension =
#ifdef SGE_LINUX_PLATFORM
	".so"
#elif SGE_WINDOWS_PLATFORM
	".dll"
#endif
	;

sge::plugin_manager::plugin_manager()
 : mypath(plugin_path)
{
	boost::filesystem::directory_iterator end;
	for(boost::filesystem::directory_iterator it(mypath); it != end; ++it)
	{
		if(boost::filesystem::is_directory(*it))
			continue;
		if(boost::filesystem::extension(*it)!=plugin_extension)
			continue;
		library lib(it->string());
		version_function vf = get_version_function(lib);
		plugin_infos.push_back(plugin_info());
		plugin_info& i = plugin_infos.back();
		vf(&i);
		i.path = iconv(it->string());
	}	
}

void sge::plugin_manager::get_plugin_info(const plugin_type mask, plugin_info_array& v)
{
	for(plugin_info_array::const_iterator it = plugin_infos.begin(); it != plugin_infos.end(); ++it)
		if(it->type & mask)
			v.push_back(*it);
}

void sge::plugin_manager::load_plugin(const plugin_type mask, const unsigned number)
{
	plugin_info_array v;
	get_plugin_info(mask,v);
	try
	{
		plugin_info_array::const_reference i = v.at(number);
		load_plugin(i.path);
	}
	catch(const std::exception&)
	{
		std::cerr << "No plugin found with mask = " << mask << " and number = " << number << "!\n";
		throw;
	}
}

void sge::plugin_manager::load_plugin(const string& file)
{
	const detail::plugin::library_ptr l(new library(file));
	version_function vf = get_version_function(*l);
	plugin_info i;
	vf(&i);
	detail::plugin p(l,i.type);
	loaded_plugins.push_back(p);
}
