/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RESOURCE_TREE_OBJECT_IMPL_HPP_INCLUDED
#define SGE_RESOURCE_TREE_OBJECT_IMPL_HPP_INCLUDED

#include <sge/resource_tree/exception.hpp>
#include <sge/resource_tree/object_decl.hpp>
#include <sge/resource_tree/path.hpp>
#include <sge/resource_tree/path_to_resource_function.hpp>
#include <sge/resource_tree/detail/base_path.hpp>
#include <sge/resource_tree/detail/element_impl.hpp>
#include <sge/resource_tree/detail/path_with_resource_impl.hpp>
#include <sge/resource_tree/detail/strip_file_extension.hpp>
#include <sge/resource_tree/detail/strip_path_prefix.hpp>
#include <sge/resource_tree/detail/sub_path.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/throw_message.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <algorithm>
#include <iterator>
#include <vector>
#include <fcppt/config/external_end.hpp>


template<
	typename T,
	typename Rng
>
sge::resource_tree::object<
	T,
	Rng
>::object(
	boost::filesystem::path const &_path,
	path_to_resource_function const &_path_to_resource,
	rng_type &_random_generator)
:
	elements_()
{
	FCPPT_ASSERT_THROW_MESSAGE(
		boost::filesystem::exists(
			_path
		),
		sge::resource_tree::exception,
		fcppt::filesystem::path_to_string(
			_path
		)
		+
		FCPPT_TEXT(" does not exist!")
	);

	FCPPT_ASSERT_THROW_MESSAGE(
		boost::filesystem::is_directory(
			_path
		),
		sge::resource_tree::exception,
		fcppt::filesystem::path_to_string(
			_path.string()
		)
		+
		FCPPT_TEXT(" is not a directory!")
	);

	typedef
	std::vector<
		boost::filesystem::path
	>
	path_vector;

	path_vector directories;

	directories.push_back(
		_path);

	std::copy_if(
		boost::filesystem::recursive_directory_iterator(
			_path),
		boost::filesystem::recursive_directory_iterator(),
		std::back_inserter<
			path_vector
		>(
			directories
		),
		[](
			boost::filesystem::path const &path
		)
		{
			return
				boost::filesystem::is_directory(
					path
				);
		}
	);

	for(
		auto const &cur_path
		:
		directories
	)
		this->add_directory(
			sge::resource_tree::detail::base_path(
				_path),
			sge::resource_tree::detail::sub_path(
				cur_path),
			_path_to_resource,
			_random_generator);
}

template<
	typename T,
	typename Rng
>
void
sge::resource_tree::object<
	T,
	Rng
>::add_directory(
	sge::resource_tree::detail::base_path const &_base_path,
	sge::resource_tree::detail::sub_path const &_sub_path,
	path_to_resource_function const &_path_to_resource,
	rng_type &_random_generator)
{
	typename
	element_type::resource_container
	resources;

	// First, collect ALL the files inside the given directory
	for(
		boost::filesystem::directory_iterator it(
			_sub_path.get());
		it != boost::filesystem::directory_iterator();
		++it)
	{
		if(!boost::filesystem::is_regular_file(*it))
			continue;

		resources.push_back(
			sge::resource_tree::detail::path_with_resource<T>(
				sge::resource_tree::detail::strip_file_extension(
					sge::resource_tree::detail::strip_path_prefix(
						sge::resource_tree::detail::base_path(
							_sub_path.get()),
						sge::resource_tree::detail::sub_path(
							*it))),
				_path_to_resource(
					*it)));
	}

	// Second, create the element structure containing the files
	fcppt::container::ptr::push_back_unique_ptr(
		elements_,
		fcppt::make_unique_ptr<element_type>(
			sge::resource_tree::detail::strip_path_prefix(
				_base_path,
				_sub_path),
			resources,
			_random_generator));
}

template<
	typename T,
	typename Rng
>
typename
sge::resource_tree::object<
	T,
	Rng
>::value_type
sge::resource_tree::object<
	T,
	Rng
>::get(
	sge::resource_tree::path const &_path)
{
	// Two choices: Either the specified path is a _file_ or a _directory_.
	//
	// If it's a _directory_, we can find it directly. It'll be the
	// base_path member of the element.
	//
	// If it's a _file_, it will be contained inside an element with the
	// according prefix.
	for(
		auto const &elem : elements_
	)
	{
		if(
			elem.base_path()
			==
			_path
		)
			return
				elem.get_random();

		if(
			elem.contains(
				_path
			)
		)
			return
				elem.get(
					_path
				);
	}

	throw sge::resource_tree::exception(
		FCPPT_TEXT("Tried to access the location \"")+
		_path.string()+
		FCPPT_TEXT("\" which could not be found in the resource tree."));
}
template<
	typename T,
	typename Rng
>
sge::resource_tree::object<
	T,
	Rng
>::~object()
{
}

#endif
