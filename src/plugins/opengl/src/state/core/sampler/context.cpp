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


#include <sge/opengl/context/device/base.hpp>
#include <sge/opengl/context/device/id.hpp>
#include <sge/opengl/context/device/make_id.hpp>
#include <sge/opengl/state/core/sampler/context.hpp>
#include <sge/opengl/state/core/sampler/make_actors.hpp>
#include <sge/opengl/state/core/sampler/object.hpp>
#include <sge/renderer/state/core/sampler/const_optional_object_ref_map.hpp>
#include <sge/renderer/state/core/sampler/default.hpp>
#include <sge/renderer/state/core/sampler/object.hpp>
#include <sge/renderer/state/core/sampler/parameters.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/from_optional.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/optional_join.hpp>
#include <fcppt/static_optional_cast.hpp>
#include <fcppt/container/find_opt_mapped.hpp>


sge::opengl::state::core::sampler::context::context(
	sge::opengl::state::core::sampler::context::parameter _system_context
)
:
	sge::opengl::context::device::base(),
	defaults_(
		fcppt::make_unique_ptr<
			sge::opengl::state::core::sampler::object
		>(
			sge::opengl::state::core::sampler::make_actors(
				_system_context,
				sge::renderer::state::core::sampler::default_()
			)
		)
	),
	objects_()
{
}

sge::opengl::state::core::sampler::context::~context()
{
}

void
sge::opengl::state::core::sampler::context::set(
	sge::renderer::state::core::sampler::const_optional_object_ref_map const &_samplers
)
{
	for(
		auto const &sampler
		:
		_samplers
	)
	{
		objects_[
			sampler.first
		] =
			fcppt::static_optional_cast<
				sge::opengl::state::core::sampler::object const
			>(
				sampler.second
			);
	}
}

sge::opengl::state::core::sampler::object const &
sge::opengl::state::core::sampler::context::get(
	sge::renderer::texture::stage const _stage
) const
{
	return
		fcppt::from_optional(
			fcppt::optional_join(
				fcppt::container::find_opt_mapped(
					objects_,
					_stage
				)
			),
			[
				this
			]()
			-> sge::opengl::state::core::sampler::object const &
			{
				return
					*defaults_;
			}
		);
}

void
sge::opengl::state::core::sampler::context::reset()
{
	objects_.clear();
}

sge::opengl::context::device::id const
sge::opengl::state::core::sampler::context::static_id(
	sge::opengl::context::device::make_id()
);
