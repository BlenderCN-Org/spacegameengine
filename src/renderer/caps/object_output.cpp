/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/image/color/format_to_string.hpp>
#include <sge/renderer/caps/object.hpp>
#include <sge/renderer/caps/object_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/ostream.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ostream>
#include <fcppt/config/external_end.hpp>


fcppt::io::ostream &
sge::renderer::caps::operator<<(
	fcppt::io::ostream &_stream,
	sge::renderer::caps::object const &_caps
)
{
	return
		_stream
		<< FCPPT_TEXT("caps: adapter = ")
		<< _caps.adapter()
		<< FCPPT_TEXT(", driver_name = \"")
		<< _caps.driver_name()
		<< FCPPT_TEXT("\", description = \"")
		<< _caps.description()
		<< FCPPT_TEXT("\", max_texture_size = ")
		<< _caps.max_texture_size()
		<< FCPPT_TEXT(", max_volume_texture_extent = ")
		<< _caps.max_volume_texture_extent()
		<< FCPPT_TEXT(", max_anisotropy = ")
		<< _caps.max_anisotropy()
		<< FCPPT_TEXT(", preferred_texture_format = ")
		<< sge::image::color::format_to_string(
			_caps.preferred_texture_format().get()
		)
		<< FCPPT_TEXT(", clip_plane_indices = ")
		<< _caps.clip_plane_indices()
		<< FCPPT_TEXT(", light_indices = ")
		<< _caps.light_indices()
		<< FCPPT_TEXT(", texture_stages = ")
		<< _caps.texture_stages();
}
