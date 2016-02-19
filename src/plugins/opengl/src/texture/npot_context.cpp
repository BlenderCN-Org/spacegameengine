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


#include <sge/opengl/common.hpp>
#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/context/make_id.hpp>
#include <sge/opengl/info/context.hpp>
#include <sge/opengl/info/extension.hpp>
#include <sge/opengl/info/extension_supported.hpp>
#include <sge/opengl/info/major_version.hpp>
#include <sge/opengl/info/minor_version.hpp>
#include <sge/opengl/info/version_at_least.hpp>
#include <sge/opengl/texture/npot_context.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


sge::opengl::texture::npot_context::npot_context(
	sge::opengl::info::context const &_info
)
:
	sge::opengl::context::base(),
	is_supported_(
		sge::opengl::info::version_at_least(
			_info.version(),
			sge::opengl::info::major_version{
				2u
			},
			sge::opengl::info::minor_version{
				0u
			}
		)
		||
		sge::opengl::info::extension_supported(
			_info.extensions(),
			sge::opengl::info::extension{
				"GL_ARB_texture_non_power_of_two"
			}
		)
	)
{
}

sge::opengl::texture::npot_context::~npot_context()
{
}

bool
sge::opengl::texture::npot_context::is_supported() const
{
	return
		is_supported_;
}

sge::opengl::context::id const
sge::opengl::texture::npot_context::static_id(
	sge::opengl::context::make_id()
);
