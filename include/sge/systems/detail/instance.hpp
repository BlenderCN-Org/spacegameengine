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


#ifndef SGE_SYSTEMS_DETAIL_INSTANCE_HPP_INCLUDED
#define SGE_SYSTEMS_DETAIL_INSTANCE_HPP_INCLUDED

#include <sge/audio/loader_fwd.hpp>
#include <sge/audio/player_fwd.hpp>
#include <sge/font/system_fwd.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/input/processor_fwd.hpp>
#include <sge/input/system_fwd.hpp>
#include <sge/input/cursor/object_fwd.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/input/mouse/device_fwd.hpp>
#include <sge/plugin/manager_fwd.hpp>
#include <sge/renderer/core_fwd.hpp>
#include <sge/renderer/system_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/systems/symbol.hpp>
#include <sge/systems/detail/instance_impl_fwd.hpp>
#include <sge/systems/detail/list_fwd.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/window/system_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr_impl.hpp>


namespace sge
{
namespace systems
{
namespace detail
{

class instance
{
	FCPPT_NONCOPYABLE(
		instance
	);
public:
	SGE_SYSTEMS_SYMBOL
	explicit
	instance(
		sge::systems::detail::list const &
	);

	SGE_SYSTEMS_SYMBOL
	~instance();

	SGE_SYSTEMS_SYMBOL
	sge::plugin::manager &
	plugin_manager();

	SGE_SYSTEMS_SYMBOL
	sge::renderer::core &
	renderer_core() const;

	SGE_SYSTEMS_SYMBOL
	sge::renderer::system &
	renderer_system() const;

	SGE_SYSTEMS_SYMBOL
	sge::renderer::device::ffp &
	renderer_device_ffp() const;

	SGE_SYSTEMS_SYMBOL
	sge::renderer::device::core &
	renderer_device_core() const;

	SGE_SYSTEMS_SYMBOL
	sge::input::system &
	input_system() const;

	SGE_SYSTEMS_SYMBOL
	sge::input::processor &
	input_processor() const;

	SGE_SYSTEMS_SYMBOL
	sge::input::cursor::object &
	cursor_demuxer() const;

	SGE_SYSTEMS_SYMBOL
	sge::input::keyboard::device &
	keyboard_collector() const;

	SGE_SYSTEMS_SYMBOL
	sge::input::mouse::device &
	mouse_collector() const;

	SGE_SYSTEMS_SYMBOL
	sge::image2d::system &
	image_system() const;

	SGE_SYSTEMS_SYMBOL
	sge::audio::loader &
	audio_loader() const;

	SGE_SYSTEMS_SYMBOL
	sge::audio::player &
	audio_player() const;

	SGE_SYSTEMS_SYMBOL
	sge::font::system &
	font_system() const;

	SGE_SYSTEMS_SYMBOL
	sge::window::system &
	window_system() const;

	SGE_SYSTEMS_SYMBOL
	sge::window::object &
	window() const;

	SGE_SYSTEMS_SYMBOL
	sge::viewport::manager &
	viewport_manager() const;
private:
	typedef
	fcppt::scoped_ptr<
		sge::systems::detail::instance_impl
	> impl_ptr;

	impl_ptr const impl_;
};

}
}
}

#endif
