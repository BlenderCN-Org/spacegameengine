/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/renderer/context/core.hpp>
#include <sge/renderer/state/core/sampler/const_optional_object_ref.hpp>
#include <sge/renderer/state/core/sampler/const_optional_object_ref_map.hpp>
#include <sge/renderer/state/core/sampler/single.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/assign/make_map.hpp>


void
sge::renderer::state::core::sampler::single(
	sge::renderer::context::core &_context,
	sge::renderer::texture::stage const _stage,
	sge::renderer::state::core::sampler::const_optional_object_ref const &_object
)
{
	_context.sampler_state(
		fcppt::assign::make_map<
			sge::renderer::state::core::sampler::const_optional_object_ref_map
		>(
			_stage,
			_object
		)
	);
}
