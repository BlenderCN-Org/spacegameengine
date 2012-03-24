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


#include <sge/cegui/from_cegui_string.hpp>
#include <sge/cegui/load_context.hpp>
#include <sge/cegui/structure_cast.hpp>
#include <sge/cegui/system.hpp>
#include <sge/cegui/to_cegui_string.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/onscreen_target.hpp>
#include <sge/renderer/viewport.hpp>
#include <sge/viewport/manager.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/math/box/object_impl.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <elements/CEGUIEditbox.h>
#include <elements/CEGUIFrameWindow.h>
#include <falagard/CEGUIFalWidgetLookManager.h>
#include <CEGUIAnimationManager.h>
#include <CEGUIDefaultResourceProvider.h>
#include <CEGUIFont.h>
#include <CEGUIFontManager.h>
#include <CEGUIImageset.h>
#include <CEGUIScheme.h>
#include <CEGUIScriptModule.h>
#include <CEGUISystem.h>
#include <CEGUIWindow.h>
#include <CEGUIWindowManager.h>
#include <CEGUIXMLParser.h>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
sge::cegui::system::system(
	load_context const &_load_context,
	sge::renderer::device &_renderer,
	sge::image2d::system &_image_system,
	sge::charconv::system &_charconv_system,
	sge::viewport::manager &_viewport,
	cursor_visibility::type const _cursor_visibility)
:
	charconv_system_(
		_charconv_system),
	prefix_(
		_load_context.scheme_file().parent_path()),
	cegui_logger_(),
	renderer_(
		*this,
		_renderer),
	image_codec_(
		_image_system),
	resource_provider_(
		_charconv_system),
	system_(
		renderer_,
		image_codec_,
		resource_provider_),
	viewport_change_connection_(
		_viewport.manage_callback(
			std::tr1::bind(
				&system::viewport_change,
				this))),
	old_viewport_(
		sge::renderer::pixel_rect::null())
{
	CEGUI::WidgetLookManager::setDefaultResourceGroup(
		to_cegui_string(
			fcppt::filesystem::path_to_string(
				_load_context.looknfeel_directory()
				?
					*_load_context.looknfeel_directory()
				:
					prefix_),
			_charconv_system));

	CEGUI::Font::setDefaultResourceGroup(
		to_cegui_string(
			fcppt::filesystem::path_to_string(
				_load_context.font_directory()
				?
					*_load_context.font_directory()
				:
					prefix_),
			_charconv_system));

	CEGUI::Imageset::setDefaultResourceGroup(
		to_cegui_string(
			fcppt::filesystem::path_to_string(
				_load_context.imageset_directory()
				?
					*_load_context.imageset_directory()
				:
					prefix_),
			_charconv_system));

	CEGUI::Scheme::setDefaultResourceGroup(
		to_cegui_string(
			fcppt::filesystem::path_to_string(
				prefix_),
			_charconv_system));

	CEGUI::SchemeManager::getSingleton().create(
		to_cegui_string(
			fcppt::filesystem::path_to_string(
				_load_context.scheme_file().filename()),
			_charconv_system));

	switch(_cursor_visibility)
	{
		case cursor_visibility::visible:
			CEGUI::System::getSingleton().setDefaultMouseCursor(
				CEGUI::ImagesetManager::getSingleton().getIterator().getCurrentValue()->getName(),
				"MouseArrow");
		break;
		case cursor_visibility::invisible:
			CEGUI::MouseCursor::getSingleton().hide();
		break;
	}

	if(_load_context.default_font())
		CEGUI::System::getSingleton().setDefaultFont(
			&CEGUI::FontManager::getSingleton().createFreeTypeFont(
				"",
				_load_context.default_font()->font_size(),
				true,
				cegui::to_cegui_string(
					fcppt::filesystem::path_to_string(
						_load_context.default_font()->path()),
					_charconv_system)));

	viewport_change();
}
FCPPT_PP_POP_WARNING

void
sge::cegui::system::update(
	cegui::duration const &d)
{
	CEGUI::System::getSingleton().injectTimePulse(
		d.count());
}

void
sge::cegui::system::render()
{
	CEGUI::System::getSingleton().renderGUI();
}

CEGUI::WindowManager &
sge::cegui::system::window_manager()
{
	return CEGUI::WindowManager::getSingleton();
}

CEGUI::WindowManager const &
sge::cegui::system::window_manager() const
{
	return CEGUI::WindowManager::getSingleton();
}

sge::cegui::system::~system()
{
}

void
sge::cegui::system::viewport_change()
{
	sge::renderer::pixel_rect new_area_fcppt =
		renderer_.impl().onscreen_target().viewport().get();
	// Calling notifyDisplaySizeChanged with a null rect causes a strange problem
	if(!new_area_fcppt.content() || old_viewport_ == new_area_fcppt)
		return;
	CEGUI::Rect const new_area_cegui =
		structure_cast(
			new_area_fcppt);
	CEGUI::System::getSingleton().notifyDisplaySizeChanged(
		new_area_cegui.getSize());
	// We have to reset this manually. The cursor does receive its own
	// "notifyDisplaySizeChanged" but that (deliberately?) doesn't
	// update the constraint area
	CEGUI::MouseCursor::getSingleton().setConstraintArea(
		&new_area_cegui);
	old_viewport_ = new_area_fcppt;
}

sge::charconv::system &
sge::cegui::system::charconv_system() const
{
	return charconv_system_;
}

sge::image2d::system &
sge::cegui::system::image_system() const
{
	return image_codec_.image_system();
}

sge::renderer::device &
sge::cegui::system::renderer() const
{
	return renderer_.impl();
}

boost::filesystem::path const
sge::cegui::system::to_absolute_path(
	CEGUI::String const &filename,
	CEGUI::String const &)
{
	return prefix_ / from_cegui_string(filename,charconv_system_);
}

