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


#ifndef SGE_MULTI_LOADER_HPP_INCLUDED
#define SGE_MULTI_LOADER_HPP_INCLUDED

#include <sge/noncopyable.hpp>
#include <sge/shared_ptr.hpp>
#include <sge/plugin/manager_fwd.hpp>
#include <sge/plugin/context.hpp>
#include <sge/filesystem/path.hpp>
#include <vector>

namespace sge
{

template<
	typename Loader,
	typename File,
	typename Exception
>
class multi_loader
{
	SGE_NONCOPYABLE(multi_loader)
public:
	typedef Loader loader;
	typedef File file;
	typedef shared_ptr<loader> loader_ptr;
	typedef shared_ptr<file> file_ptr;
	typedef Exception exception;

	explicit multi_loader(
		plugin::manager &
	);

	file_ptr const
	load(
		filesystem::path const &
	);
private:
	typedef std::vector<
		typename plugin::context<
			loader
		>::ptr_type
	> plugin_container;

	typedef std::vector<
		loader_ptr
	> loader_container;

	plugin_container plugins;
	loader_container loaders;

	file_ptr const
	brute_load(
		filesystem::path const &
	);
};

}

#endif
