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


#include <sge/audio/exception.hpp>
#include <sge/openal/al.hpp>
#include <sge/openal/check_state.hpp>
#include <sge/openal/source_id.hpp>
#include <sge/openal/funcs/source_int.hpp>
#include <fcppt/text.hpp>


void
sge::openal::funcs::source_int(
	sge::openal::source_id const _source,
	ALenum const _what,
	ALint const _value
)
{
	::alSourcei(
		_source.get(),
		_what,
		_value
	);

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alSourcei failed"),
		sge::audio::exception
	)
}
