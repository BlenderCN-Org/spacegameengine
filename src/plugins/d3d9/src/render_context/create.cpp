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


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/render_context/create.hpp>
#include <sge/d3d9/render_context/object.hpp>
#include <sge/d3d9/state/core/defaults_fwd.hpp>
#include <sge/d3d9/state/ffp/defaults_fwd.hpp>
#include <sge/renderer/caps/texture_stages.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/context/ffp_unique_ptr.hpp>
#include <sge/renderer/target/base_fwd.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>


sge::renderer::context::ffp_unique_ptr
sge::d3d9::render_context::create(
	IDirect3DDevice9 &_device,
	sge::renderer::target::base &_target,
	sge::renderer::caps::texture_stages const _texture_stages,
	sge::d3d9::state::core::defaults const &_core_defaults,
	sge::d3d9::state::ffp::defaults const &_ffp_defaults
)
{
	return
		sge::renderer::context::ffp_unique_ptr(
			fcppt::make_unique_ptr<
				sge::d3d9::render_context::object
			>(
				fcppt::ref(
					_device
				),
				fcppt::ref(
					_target
				),
				_texture_stages,
				fcppt::cref(
					_core_defaults
				),
				fcppt::cref(
					_ffp_defaults
				)
			)
		);
}
