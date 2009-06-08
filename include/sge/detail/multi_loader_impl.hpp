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


#ifndef SGE_DETAIL_MULTI_LOADER_IMPL_HPP_INCLUDED
#define SGE_DETAIL_MULTI_LOADER_IMPL_HPP_INCLUDED

#include <sge/audio/loader_plugin.hpp>
#include <sge/plugin/iterator.hpp>
#include <sge/plugin/manager.hpp>
#include <sge/plugin/plugin.hpp>
#include <sge/filesystem/exists.hpp>
#include <sge/log/headers.hpp>
#include <sge/text.hpp>
#include <sge/type_name.hpp>

template<
	typename A,
	typename B,
	typename C>
sge::multi_loader<A,B,C>::multi_loader(
	plugin::manager &pm)
{
	for (plugin::iterator<loader> i = pm.begin<loader>(); i != pm.end<loader>(); ++i)
	{
		plugins.push_back(
			i->load());
		loaders.push_back(
			loader_ptr(
				plugins.back()->get()()));
	}
}	

template<
	typename A,
	typename B,
	typename C>
typename sge::multi_loader<A,B,C>::file_ptr const
sge::multi_loader<A,B,C>::load(
	sge::filesystem::path const &file)
{
	if (!filesystem::exists(file))
		throw exception(
			SGE_TEXT("file \"")
			+ file.string()
			+ SGE_TEXT("\" does not exist"));

	for (typename loader_container::iterator i = loaders.begin(); i != loaders.end(); ++i)
	{
		SGE_LOG_DEBUG(
			log::global(),
			log::_1 
				<< SGE_TEXT("loader ")
				<< type_name(typeid(loader))
				<< SGE_TEXT(": trying to load audio file"));

		if (!(*i)->is_valid_file(file))
			continue;

		return (*i)->load(file);
	}

	throw exception(
		SGE_TEXT("couldn't find any audio loaders for file \"")
		+ file.string()
		+ SGE_TEXT('"'));
}

#endif
