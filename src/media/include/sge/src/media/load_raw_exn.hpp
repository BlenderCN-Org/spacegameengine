/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SRC_MEDIA_LOAD_RAW_EXN_HPP_INCLUDED
#define SGE_SRC_MEDIA_LOAD_RAW_EXN_HPP_INCLUDED

#include <sge/media/const_raw_range.hpp>
#include <sge/media/optional_extension_fwd.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace media
{

template<
	typename Result,
	typename Exception,
	typename System
>
Result
load_raw_exn(
	System &_system,
	sge::media::const_raw_range const &_range,
	sge::media::optional_extension const &_extension
)
{
	typedef
	fcppt::optional<
		Result
	>
	optional_result;

	optional_result result(
		_system.load_raw(
			_range,
			_extension
		)
	);

	if(
		!result
	)
		throw
			Exception(
				FCPPT_TEXT("load_raw_exn failed")
			);

	return
		std::move(
			*result
		);
}

}
}

#endif
