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


#ifndef SGE_MULTI_LOADER_IMPL_HPP_INCLUDED
#define SGE_MULTI_LOADER_IMPL_HPP_INCLUDED

#include <sge/plugin/iterator.hpp>
#include <sge/plugin/manager.hpp>
#include <sge/plugin/plugin.hpp>
#include <sge/loaders_exhausted.hpp>
#include <sge/log/global.hpp>
#include <sge/multi_loader.hpp>
#include <sge/all_extensions.hpp>
#include <fcppt/algorithm/contains.hpp>
#include <fcppt/algorithm/set_intersection.hpp>
#include <fcppt/filesystem/exists.hpp>
#include <fcppt/filesystem/is_regular.hpp>
#include <fcppt/filesystem/extension.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/text.hpp>
#include <fcppt/type_name.hpp>
#include <boost/foreach.hpp>
#include <typeinfo>

template<
	typename Loader,
	typename File,
	typename Exception 
>
sge::multi_loader<Loader, File, Exception>::multi_loader(
	plugin::manager &pm,
	extension_set const &extensions
)
{
	for (
		plugin::iterator<loader> i = pm.begin<loader>();
		i != pm.end<loader>();
		++i
	)
	{
		plugin_ptr const plugin_(
			i->load()
		);

		loader_ptr const loader_(
			loader_ptr(
				plugins.back()->get()()
			)
		);

		// check if this plugin might be useful
		if(
			extensions == sge::all_extensions
			||
			!fcppt::algorithm::set_intersection(
				extensions,
				loader_->extensions()
			).empty()
		)
		{
			plugins.push_back(
				plugin_
			);

			loaders.push_back(
				loader_
			);
		}
	}
}

template<
	typename Loader,
	typename File,
	typename Exception
>
sge::multi_loader<Loader, File, Exception>::~multi_loader()
{}

template<
	typename Loader,
	typename File,
	typename Exception 
>
typename sge::multi_loader<Loader, File, Exception>::file_ptr const
sge::multi_loader<Loader, File, Exception>::load(
	fcppt::filesystem::path const &file
) const
{
	if (!fcppt::filesystem::exists(file))
		throw exception(
			FCPPT_TEXT("file \"")
			+ file.string()
			+ FCPPT_TEXT("\" does not exist")
		);

	if (!fcppt::filesystem::is_regular(file))
		throw exception(
			FCPPT_TEXT("file \"")
			+ file.string()
			+ FCPPT_TEXT("\" is not a regular file")
		);

	fcppt::string const extension(
		fcppt::filesystem::extension(
			file
		)
	);

	if (extension.empty())
		throw loaders_exhausted(
			file
		);

	BOOST_FOREACH(
		typename loader_container::const_reference ref,
		loaders
	)
	{
		if (
			!fcppt::algorithm::contains(
				ref->extensions(),
				extension
			)
		)
			continue;

		FCPPT_LOG_DEBUG(
			log::global(),
			fcppt::log::_
				<< FCPPT_TEXT("loader ")
				<< fcppt::type_name(typeid(loader))
				<< FCPPT_TEXT(": trying to load audio file")
			);

		return
			ref->load(
				file
			);
	}

	throw loaders_exhausted(
		file
	);
}

#endif
