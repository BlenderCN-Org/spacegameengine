/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SRC_MEDIA_MUXER_IMPL_HPP_INCLUDED
#define SGE_SRC_MEDIA_MUXER_IMPL_HPP_INCLUDED

#include <sge/media/extension_fwd.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/load_stream_result.hpp>
#include <sge/media/muxer.hpp>
#include <sge/media/optional_extension_fwd.hpp>
#include <sge/media/optional_name_fwd.hpp>
#include <sge/media/stream_unique_ptr.hpp>
#include <sge/src/media/detail/muxer_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/optional/reference.hpp>


template<
	typename System,
	typename File
>
sge::media::muxer<
	System,
	File
>::muxer(
	parameters const &_parameters
)
:
	impl_(
		fcppt::make_unique_ptr<
			muxer_impl
		>(
			_parameters
		)
	)
{
}

template<
	typename System,
	typename File
>
sge::media::muxer<
	System,
	File
>::~muxer()
{
}

template<
	typename System,
	typename File
>
typename
sge::media::muxer<
	System,
	File
>::load_stream_result
sge::media::muxer<
	System,
	File
>::mux_stream(
	sge::media::stream_unique_ptr &&_stream,
	sge::media::optional_extension const &_extension,
	sge::media::optional_name const &_name
) const
{
	return
		impl_->mux_stream(
			std::move(
				_stream
			),
			_extension,
			_name
		);
}

template<
	typename System,
	typename File
>
typename
sge::media::muxer<
	System,
	File
>::optional_system_ref
sge::media::muxer<
	System,
	File
>::mux_extension(
	sge::media::extension const &_extension
) const
{
	return
		impl_->mux_extension(
			_extension
		);
}

template<
	typename System,
	typename File
>
sge::media::extension_set
sge::media::muxer<
	System,
	File
>::extensions() const
{
	return
		impl_->extensions();
}

#endif
