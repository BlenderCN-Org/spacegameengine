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


#include <sge/opengl/enable.hpp>
#include <sge/opengl/init_multi_sampling.hpp>
#include <sge/opengl/multi_sample_context.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/renderer/unsupported.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/text.hpp>


void
sge::opengl::init_multi_sampling(
	sge::opengl::context::object &_context,
	sge::renderer::pixel_format::optional_multi_samples const &_samples
)
{
	if(
		!_samples.has_value()
	)
		return;

	sge::opengl::multi_sample_context const &multi_sample_context(
		sge::opengl::context::use<
			sge::opengl::multi_sample_context
		>(
			_context,
			_context.info()
		)
	);

	sge::opengl::enable(
		fcppt::optional::to_exception(
			multi_sample_context.flag(),
			[]{
				return
					sge::renderer::unsupported{
						FCPPT_TEXT("multi sampling"),
						FCPPT_TEXT("GL_VERSION_1_3"),
						FCPPT_TEXT("GL_ARB_multisample")
					};
			}
		)
	);
}
