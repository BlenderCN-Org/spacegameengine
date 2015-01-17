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


#ifndef SGE_OPENGL_EGL_VERSION_HPP_INCLUDED
#define SGE_OPENGL_EGL_VERSION_HPP_INCLUDED

#include <sge/opengl/egl/major_version.hpp>
#include <sge/opengl/egl/minor_version.hpp>
#include <sge/opengl/egl/version_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace egl
{

class version
{
public:
	version(
		sge::opengl::egl::major_version,
		sge::opengl::egl::minor_version
	);

	sge::opengl::egl::major_version const
	major() const;

	sge::opengl::egl::minor_version const
	minor() const;
private:
	sge::opengl::egl::major_version major_;

	sge::opengl::egl::minor_version minor_;
};

}
}
}

#endif
