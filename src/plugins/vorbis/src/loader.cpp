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


#include "../file.hpp"
#include "../loader.hpp"
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/text.hpp>

sge::audio::file_ptr const
sge::vorbis::loader::load(
	fcppt::filesystem::path const &filename
)
{
	return
		fcppt::make_shared_ptr<
			file
		>(
			filename
		);
}

sge::audio::loader_capabilities_field const
sge::vorbis::loader::capabilities() const
{
	return audio::loader_capabilities_field::null();
}

sge::extension_set const
sge::vorbis::loader::extensions() const
{
	static extension_set s(
		fcppt::assign::make_container<
			extension_set
		>(
			FCPPT_TEXT("ogg")
		)
	);

	return s;
}
