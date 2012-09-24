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


#include <sge/cegui/cursor_visibility.hpp>
#include <sge/cegui/duration.hpp>
#include <sge/cegui/load_context_fwd.hpp>
#include <sge/cegui/system.hpp>
#include <sge/charconv/system_fwd.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/src/cegui/detail/system_impl.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/WindowManager.h>
#include <fcppt/config/external_end.hpp>


sge::cegui::system::system(
	sge::cegui::load_context const &_load_context,
	sge::renderer::device::ffp &_renderer,
	sge::image2d::system &_image_system,
	sge::charconv::system &_charconv_system,
	sge::viewport::manager &_viewport_manager,
	sge::cegui::cursor_visibility::type const _cursor_visibility
)
:
	impl_(
		fcppt::make_unique_ptr<
			sge::cegui::detail::system_impl
		>(
			fcppt::cref(
				_load_context
			),
			fcppt::ref(
				_renderer
			),
			fcppt::ref(
				_image_system
			),
			fcppt::ref(
				_charconv_system
			),
			fcppt::ref(
				_viewport_manager
			),
			_cursor_visibility
		)
	)
{
}

sge::cegui::system::~system()
{
}

void
sge::cegui::system::update(
	sge::cegui::duration const &_duration
)
{
	impl_->update(
		_duration
	);
}

void
sge::cegui::system::render(
	sge::renderer::context::ffp &_context
)
{
	impl_->render(
		_context
	);
}

CEGUI::WindowManager &
sge::cegui::system::window_manager()
{
	return
		CEGUI::WindowManager::getSingleton();
}

CEGUI::WindowManager const &
sge::cegui::system::window_manager() const
{
	return
		CEGUI::WindowManager::getSingleton();
}

CEGUI::GUIContext &
sge::cegui::system::gui_context()
{
	return
		impl_->gui_context();
}

CEGUI::GUIContext const &
sge::cegui::system::gui_context() const
{
	return
		impl_->gui_context();
}

sge::charconv::system &
sge::cegui::system::charconv_system() const
{
	return
		impl_->charconv_system();
}
