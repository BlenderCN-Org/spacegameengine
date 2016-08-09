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


#ifndef SGE_SYSTEMS_IMPL_RENDERER_FIND_PLUGIN_HPP_INCLUDED
#define SGE_SYSTEMS_IMPL_RENDERER_FIND_PLUGIN_HPP_INCLUDED

#include <sge/renderer/caps/system_field_fwd.hpp>
#include <sge/renderer/plugin/collection_fwd.hpp>
#include <sge/systems/optional_name_fwd.hpp>
#include <sge/systems/renderer_caps_fwd.hpp>
#include <sge/systems/impl/renderer/plugin_core_pair_fwd.hpp>
#include <fcppt/log/context_fwd.hpp>


namespace sge
{
namespace systems
{
namespace impl
{
namespace renderer
{

sge::systems::impl::renderer::plugin_core_pair
find_plugin(
	fcppt::log::context &,
	sge::renderer::plugin::collection const &,
	sge::systems::optional_name const &,
	sge::renderer::caps::system_field const &,
	sge::systems::renderer_caps
);

}
}
}
}

#endif