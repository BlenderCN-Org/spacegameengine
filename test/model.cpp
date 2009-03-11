/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/plugin/manager.hpp>
#include <sge/plugin/plugin.hpp>
#include <sge/plugin/context.hpp>
#include <sge/model/plugin.hpp>
#include <sge/model/loader.hpp>
#include <sge/model/loader_fwd.hpp>
#include <sge/model/object.hpp>
#include <sge/text.hpp>
#include <sge/media.hpp>
#include <fstream>

int main()
{
	sge::systems::instance sys(
		sge::systems::list()
		(sge::window::parameters(
			SGE_TEXT("sge animtest")
		))
		(sge::renderer::parameters(
			sge::renderer::display_mode(
				sge::renderer::screen_size(
					1024,
					768),
				sge::renderer::bit_depth::depth32,
				sge::renderer::refresh_rate_dont_care),
			sge::renderer::depth_buffer::off,
			sge::renderer::stencil_buffer::off,
			sge::renderer::window_mode::windowed))
		(sge::systems::parameterless::input)
	);
	
//	sge::plugin::manager plugin_manager;
//	plugin_manager.plugin<sge::model::loader>();

/*
	sge::plugin::plugin<
		sge::model::loader
	>::ptr_type const  model_plugin(
		plugin_manager.plugin<sge::model::loader>()
		.load()
	);

	sge::model::loader_ptr const loader(
		model_plugin->get()()
	);

	std::ifstream ifs(
		(sge::media_path() / SGE_TEXT("european_fnt_v2.md3")).string().c_str(),
		std::ios_base::binary
	);

	sge::model::object_ptr const object(
		loader->load(
			ifs
		)
	);
	*/

}
