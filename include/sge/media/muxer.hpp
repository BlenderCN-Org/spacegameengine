/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_MEDIA_MUXER_HPP_INCLUDED
#define SGE_MEDIA_MUXER_HPP_INCLUDED

#include <sge/media/extension_set.hpp>
#include <sge/media/muxer_fwd.hpp>
#include <sge/media/muxer_parameters_fwd.hpp>
#include <sge/media/optional_extension_fwd.hpp>
#include <sge/media/detail/muxer_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <functional>
#include <memory>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace media
{

template<
	typename System,
	typename File
>
class muxer
{
	FCPPT_NONCOPYABLE(
		muxer
	);
public:
	typedef
	System
	system;

	typedef
	File
	file;

	typedef
	sge::media::muxer_parameters<
		system
	>
	parameters;

	typedef
	std::unique_ptr<
		file
	>
	file_unique_ptr;

	typedef
	fcppt::optional<
		file_unique_ptr
	>
	optional_file_unique_ptr;

	typedef
	std::function<
		optional_file_unique_ptr (
			system &
		)
	>
	load_function;

	explicit
	muxer(
		parameters const &
	);

	~muxer();

	optional_file_unique_ptr
	mux_path(
		boost::filesystem::path const &,
		load_function const &
	) const;

	optional_file_unique_ptr
	mux_extension(
		media::optional_extension const &,
		load_function const &
	) const;

	sge::media::extension_set
	extensions() const;
private:
	typedef
	sge::media::detail::muxer<
		System,
		File
	>
	muxer_impl;

	typedef
	std::unique_ptr<
		muxer_impl
	>
	muxer_impl_unique_ptr;

	muxer_impl_unique_ptr const impl_;
};

}
}

#endif
