/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/systems/name_dont_care.hpp>
#include <sge/plugin/manager.hpp>
#include <sge/plugin/plugin.hpp>
#include <sge/plugin/iterator.hpp>
#include <sge/plugin/context.hpp>
#include <sge/plugin/context_base.hpp>
#include <sge/renderer/system.hpp>
#include <sge/renderer/plugin.hpp>
#include <sge/renderer/device.hpp>
#include <sge/input/system.hpp>
#include <sge/input/plugin.hpp>
#include <sge/image/loader.hpp>
#include <sge/image/plugin.hpp>
#include <sge/audio/player.hpp>
#include <sge/audio/player_plugin.hpp>
#include <sge/collision/system.hpp>
#include <sge/collision/plugin.hpp>
#include <sge/font/system.hpp>
#include <sge/font/plugin.hpp>
#include <sge/window/instance.hpp>
#include <sge/window/create.hpp>
#include <sge/log/global.hpp>
#include <sge/exception.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/optional.hpp>
#include <fcppt/text.hpp>
#include <fcppt/type_info.hpp>
#include <fcppt/string.hpp>
#include <boost/foreach.hpp>
#include <typeinfo>

class sge::systems::instance::impl
{
public:
	plugin::manager                                 plugin_manager;

	plugin::plugin<sge::renderer::system>::ptr_type renderer_plugin;
	sge::renderer::system_ptr                       renderer_system;
	sge::renderer::device_ptr                       renderer;

	plugin::plugin<input::system>::ptr_type         input_plugin;
	input::system_ptr                               input_system;

	plugin::plugin<image::loader>::ptr_type         image_loader_plugin;
	image::loader_ptr                               image_loader;

	plugin::plugin<audio::player>::ptr_type         audio_player_plugin;
	audio::player_ptr                               audio_player;

	plugin::plugin<collision::system>::ptr_type     collision_plugin;
	collision::system_ptr                           collision_system;

	plugin::plugin<font::system>::ptr_type          font_plugin;
	font::system_ptr                                font_system;

	window::instance_ptr                            window_;

	fcppt::optional<window::parameters>             wparam_;

	void
	init_renderer(
		renderer::parameters const &,
		fcppt::string const &name
	);

	void
	init_window(
		window::parameters const &,
		fcppt::string const &name
	);

	void
	init_input(
		fcppt::string const &name
	);

	void
	init_collision_system(
		fcppt::string const &name
	);

	void
	init_image(
		fcppt::string const &name
	);

	void
	init_audio_player(
		fcppt::string const &name
	);

	void
	init_font(
		fcppt::string const &name
	);
private:
	template<
		typename T
	>
	typename plugin::plugin<T>::ptr_type const
	load_plugin(
		fcppt::string const &name
	);

	template<
		typename T
	>
	typename plugin::plugin<T>::ptr_type const
	default_plugin();
};

namespace
{

class visitor
{
public:
	typedef void result_type;

	visitor(
		sge::systems::instance::impl &,
		fcppt::string const &name
	);

	result_type
	operator()(
		sge::renderer::parameters const &
	) const;

	result_type
	operator()(
		sge::window::parameters const &
	) const;

	result_type
	operator()(
		sge::systems::parameterless::type
	) const;
private:
	sge::systems::instance::impl &impl_;
	fcppt::string const name;
};

}

sge::systems::instance::instance(
	list const &l
)
:
	impl_(
		new impl()
	)
{
	reinit(l);
}

sge::systems::instance::~instance()
{}

void
sge::systems::instance::reinit(
	list const &l
)
{
	BOOST_FOREACH(
		named const &named_,
		l.get()
	)
		fcppt::variant::apply_unary(
			visitor(
				*impl_,
				named_.name()
			),
			named_.value()
		);
}

sge::plugin::manager &
sge::systems::instance::plugin_manager()
{
	return impl_->plugin_manager;
}

sge::renderer::system_ptr const
sge::systems::instance::renderer_system() const
{
	return impl_->renderer_system;
}

sge::renderer::device_ptr const
sge::systems::instance::renderer() const
{
	return impl_->renderer;
}

sge::input::system_ptr const
sge::systems::instance::input_system() const
{
	return impl_->input_system;
}

sge::image::loader_ptr const
sge::systems::instance::image_loader() const
{
	return impl_->image_loader;
}

sge::audio::player_ptr const
sge::systems::instance::audio_player() const
{
	return impl_->audio_player;
}

sge::collision::system_ptr const
sge::systems::instance::collision_system() const
{
	return impl_->collision_system;
}

sge::font::system_ptr const
sge::systems::instance::font_system() const
{
	return impl_->font_system;
}

namespace
{

visitor::visitor(
	sge::systems::instance::impl &impl_,
	fcppt::string const &name
)
:
	impl_(impl_),
	name(name)
{}


void
visitor::operator()(
	sge::renderer::parameters const &p
) const
{
	impl_.init_renderer(
		p,
		name
	);
}

void
visitor::operator()(
	sge::window::parameters const &p
) const
{
	impl_.init_window(
		p,
		name
	);
}

void
visitor::operator()(
	sge::systems::parameterless::type const p
) const
{
	switch(p)
	{
	case sge::systems::parameterless::input:
		impl_.init_input(name);
		return;
	case sge::systems::parameterless::image:
		impl_.init_image(name);
		return;
	case sge::systems::parameterless::audio_player:
		impl_.init_audio_player(name);
		return;
	case sge::systems::parameterless::collision_system:
		impl_.init_collision_system(name);
		return;
	case sge::systems::parameterless::font:
		impl_.init_font(name);
		return;
	}

	throw sge::exception(
		FCPPT_TEXT("Invalid systems::parameterless!")
	);
}

}

void
sge::systems::instance::impl::init_window(
	window::parameters const &p,
	fcppt::string const &name
)
{
	wparam_ = p;
}

void
sge::systems::instance::impl::init_renderer(
	renderer::parameters const &p,
	fcppt::string const &name
)
{
	renderer_plugin = load_plugin<renderer::system>(name);
	renderer_system.reset(renderer_plugin->get()());

	if(!window_)
	{
		if(!wparam_)
			throw exception(
				FCPPT_TEXT("systems: renderer device requested, but no window parameter given!")
			);

		if(!wparam_->dim())
			wparam_->dim(
				p.mode().size()
			);

		window_ =
			renderer_system->create_window(
				*wparam_,
				p
			);
	}

	renderer = renderer_system->create_renderer(
		p,
		static_cast<renderer::adapter_type>(0),
		window_
	);
}

void
sge::systems::instance::impl::init_input(
	fcppt::string const &name
)
{
	if(!window_)
	{
		if(!wparam_)
			throw exception(
				FCPPT_TEXT("systems: input system requested, but no window parameter given!")
			);

		window_ = sge::window::create(
			*wparam_
		);
	}


	input_plugin = load_plugin<sge::input::system>(name);
	input_system.reset(input_plugin->get()(window_));
}

void
sge::systems::instance::impl::init_collision_system(
	fcppt::string const &name
)
{
	collision_plugin = load_plugin<sge::collision::system>(name);
	collision_system.reset(collision_plugin->get()());
}

void
sge::systems::instance::impl::init_image(
	fcppt::string const &name
)
{
	image_loader_plugin = load_plugin<sge::image::loader>(name);
	image_loader.reset(image_loader_plugin->get()());
}

void
sge::systems::instance::impl::init_audio_player(
	fcppt::string const &name
)
{
	audio_player_plugin = load_plugin<sge::audio::player>(name);
	audio_player.reset(audio_player_plugin->get()());
}


void
sge::systems::instance::impl::init_font(
	fcppt::string const &name
)
{
	font_plugin = load_plugin<sge::font::system>(name);
	font_system.reset(font_plugin->get()());
}

template<
	typename T
>
typename sge::plugin::plugin<T>::ptr_type const
sge::systems::instance::impl::load_plugin(
	fcppt::string const &name
)
{
	if(name == name_dont_care)
		return default_plugin<T>();

	for(
		sge::plugin::iterator<T> it(plugin_manager.begin<T>());
		it != plugin_manager.end<T>();
		++it
	)
		if(it->info().name() == name)
			return it->load();

	FCPPT_LOG_WARNING(
		log::global(),
		fcppt::log::_
			<< FCPPT_TEXT("Tried to load plugin of type ")
			<< fcppt::type_info(typeid(T)).name()
			<< FCPPT_TEXT(" with name \"")
			<< name
			<< FCPPT_TEXT("\" but it could not be found!")
			<< FCPPT_TEXT(" Trying to load a default plugin instead.")
	);

	return default_plugin<T>();
}

template<
	typename T
>
typename sge::plugin::plugin<T>::ptr_type const
sge::systems::instance::impl::default_plugin()
{
	return plugin_manager.plugin<T>().load();
}
