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


#ifndef SGE_SRC_SYSTEMS_MODULES_RENDERER_SYSTEM_HPP_INCLUDED
#define SGE_SRC_SYSTEMS_MODULES_RENDERER_SYSTEM_HPP_INCLUDED

#include <sge/parse/ini/start_fwd.hpp>
#include <sge/renderer/system_fwd.hpp>
#include <sge/renderer/pixel_format/object.hpp>
#include <sge/renderer/plugin/collection_fwd.hpp>
#include <sge/src/systems/modules/renderer/system_fwd.hpp>
#include <sge/src/systems/modules/renderer/system_pair.hpp>
#include <sge/systems/detail/renderer_fwd.hpp>
#include <awl/system/object_fwd.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace systems
{
namespace modules
{
namespace renderer
{

class system
{
	FCPPT_NONCOPYABLE(
		system
	);
public:
	system(
		sge::renderer::plugin::collection const &,
		sge::systems::detail::renderer const &,
		sge::parse::ini::start const &
	);

	~system();

	awl::visual::object_unique_ptr
	create_visual(
		awl::system::object &
	);

	sge::renderer::system &
	get() const;
private:
	sge::renderer::pixel_format::object const pixel_format_;

	sge::systems::modules::renderer::system_pair const system_pair_;
};

}
}
}
}

#endif
