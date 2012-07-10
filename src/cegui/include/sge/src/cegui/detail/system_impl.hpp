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


#ifndef SGE_SRC_CEGUI_DETAIL_SYSTEM_IMPL_HPP_INCLUDED
#define SGE_SRC_CEGUI_DETAIL_SYSTEM_IMPL_HPP_INCLUDED

#include <sge/cegui/cursor_visibility.hpp>
#include <sge/cegui/duration.hpp>
#include <sge/cegui/load_context_fwd.hpp>
#include <sge/cegui/detail/system_impl_fwd.hpp>
#include <sge/charconv/system_fwd.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/pixel_rect.hpp>
#include <sge/renderer/context/object_fwd.hpp>
#include <sge/src/cegui/cegui_logger.hpp>
#include <sge/src/cegui/image_codec.hpp>
#include <sge/src/cegui/prefix.hpp>
#include <sge/src/cegui/renderer.hpp>
#include <sge/src/cegui/resource_provider.hpp>
#include <sge/src/cegui/scoped_system.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/GUIContext.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace cegui
{
namespace detail
{

class system_impl
{
	FCPPT_NONCOPYABLE(
		system_impl
	);
public:
	system_impl(
		sge::cegui::load_context const &,
		sge::renderer::device &,
		sge::image2d::system &,
		sge::charconv::system &,
		sge::viewport::manager &,
		sge::cegui::cursor_visibility::type
	);

	~system_impl();

	void
	update(
		sge::cegui::duration const &
	);

	void
	render(
		sge::renderer::context::object &
	);

	CEGUI::GUIContext &
	gui_context();

	sge::charconv::system &
	charconv_system() const;
private:
	void
	viewport_change();

	sge::charconv::system &charconv_system_;

	sge::cegui::prefix const prefix_;

	sge::cegui::cegui_logger cegui_logger_;

	sge::cegui::renderer renderer_;

	sge::cegui::image_codec image_codec_;

	sge::cegui::resource_provider resource_provider_;

	sge::cegui::scoped_system const scoped_system_;

	CEGUI::GUIContext gui_context_;

	fcppt::signal::scoped_connection const viewport_change_connection_;

	// We have to memorize the old viewport so we don't call
	// notifyDisplaySizeChanged if old == new (costs performance)
	sge::renderer::pixel_rect old_viewport_;
};

}
}
}

#endif