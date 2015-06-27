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


#include <sge/opengl/egl/version.hpp>
#include <sge/opengl/egl/version_output.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/ostream.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ostream>
#include <fcppt/config/external_end.hpp>


fcppt::io::ostream &
sge::opengl::egl::operator<<(
	fcppt::io::ostream &_stream,
	sge::opengl::egl::version const &_version
)
{
	return
		_stream
			<< _version.major()
			<< FCPPT_TEXT('.')
			<< _version.minor();
}
