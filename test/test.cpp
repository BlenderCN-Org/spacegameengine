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


#include <ctime>
#include <cstdlib>
#include <string>
#include <exception>
#include <iostream>
#include <ostream>
#include <utility>
#include <vector>
#include <fstream>
#include <algorithm>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/if.hpp>
#include <boost/bind.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream_buffer.hpp>
#include <boost/iostreams/stream.hpp>
#include <sge/math/constants.hpp>
#include <sge/texture/default_creator.hpp>
#include <sge/texture/util.hpp>
#include <sge/texture/default_creator_impl.hpp>
#include <sge/texture/no_fragmented_texture.hpp>
#include <sge/plugin_manager.hpp>
#include <sge/renderer/scoped_lock.hpp>
#include <sge/util.hpp>
#include <sge/font/font.hpp>
#include <sge/font/font_drawer_3d.hpp>
#include <sge/renderer/renderer.hpp>
#include <sge/renderer/types.hpp>
#include <sge/renderer/renderer_system.hpp>
#include <sge/renderer/transform.hpp>
#include <sge/media.hpp>
#include <sge/input/input_system.hpp>
#include <sge/input/key_state_tracker.hpp>
#include <sge/renderer/line_strip.hpp>
#include <sge/renderer/screenshot.hpp>
#include <sge/renderer/renderer_parameters.hpp>
#include <sge/language.hpp>
#include <sge/endianness.hpp>
#include <sge/audio/audio_loader/audio_loader.hpp>
//#include <sge/audio/audio_player/audio_player.hpp>
//#include <sge/audio/audio_player/sound.hpp>
#include <sge/exception.hpp>
#include <sge/console/console_gfx.hpp>
#include <sge/console/console.hpp>
#include <sge/console/stdlib.hpp>
#include <sge/vector.hpp>
#include <sge/codecvt.hpp>
#include <sge/image/util.hpp>
#include <sge/multitree.hpp>
#include <sge/field.hpp>
#include <sge/language.hpp>
#include <sge/scoped_connection.hpp>
#include <sge/frames_counter.hpp>
#include <sge/fstream.hpp>
#include <sge/sstream.hpp>
#include <sge/iostream.hpp>

namespace
{

/*sge::space_unit randf() { return double(std::rand())/RAND_MAX; }

sge::math::vector2 rand_point2() { return sge::math::vector2(randf(),randf()); }

sge::pos3 rand_point() { return sge::pos3(rand_point2(), 0); }*/

/*struct smallplayer
{
	sge::shared_ptr<sge::sound> sound;
	smallplayer(sge::shared_ptr<sge::sound> sound) : sound(sound) {}
	void operator()() { sound->play(false); }
};*/

struct console_activator
{
	sge::con::console_gfx &con;

	console_activator(sge::con::console_gfx &con) : con(con) {}

	void callback(const sge::key_pair &pair)
	{
		if (pair.key().code() == sge::kc::key_tab && pair.value())
			con.toggle();
	}
};
}

int main()
try
{
	bool running = true;
	sge::plugin_manager pm;

	const sge::plugin<sge::renderer_system>::ptr_type renderer_plugin = pm.get_plugin<sge::renderer_system>().load();
	const sge::plugin<sge::input_system>::ptr_type input_plugin = pm.get_plugin<sge::input_system>().load();

	const sge::renderer_system_ptr rs(renderer_plugin->get()());
	const sge::renderer_caps_array caps(rs->caps());

	const sge::renderer_parameters param(sge::display_mode(1280,1024,sge::bit_depth::depth32,100), true);
	const sge::renderer_ptr rend = rs->create_renderer(param);

	const sge::input_system_ptr is(input_plugin->get()(rend->get_window()));

	const sge::plugin<sge::image_loader>::ptr_type image_loader_plugin = pm.get_plugin<sge::image_loader>().load();
	const sge::image_loader_ptr pl(image_loader_plugin->get()());

	const sge::plugin<sge::font_system>::ptr_type font_plugin = pm.get_plugin<sge::font_system>().load();
	const sge::font_system_ptr fs(font_plugin->get()());

	const sge::font_metrics_ptr metrics = fs->create_font(sge::media_path() / SGE_TEXT("fonts/default.ttf"), 15);
	const sge::font_drawer_ptr fn_drawer(new sge::font_drawer_3d(rend));

	sge::font_ptr fn(new sge::font(metrics,fn_drawer));

	sge::texture_manager texman(rend,sge::default_texture_creator<sge::no_fragmented_texture>(rend,sge::linear_filter));
//	const sge::image_ptr console_image = pl->load_image(sge::media_path() / SGE_TEXT("black.jpg"));
//	const sge::virtual_texture_ptr console_texture = sge::add_texture(texman,console_image);
//	sge::con::console_gfx console(rend,console_texture,fn,is,pos,console_size);

	using boost::lambda::var;
	using boost::lambda::bind;
//	using boost::lambda::_1;
	using boost::lambda::if_;

//	console_activator activator(console);

	const sge::scoped_connection cb(is->register_callback(if_(bind(&sge::key_type::code, bind(&sge::key_pair::key,boost::lambda::_1)) == sge::kc::key_escape)[var(running)=false]));
//	const sge::scoped_connection cb2(is->register_callback(boost::bind(&console_activator::callback,&activator,_1)));

	sge::key_state_tracker ks(is);

	rend->set_state((
		sge::bool_state::enable_lighting = true,
		sge::cull_mode::off,
		sge::bool_state::clear_zbuffer = true,
		sge::bool_state::clear_backbuffer = true,
		sge::cull_mode::front,
		sge::float_state::zbuffer_clear_val = 0,
		sge::depth_func::greater));

//	rend->set_light(0, sge::light(sge::color4(1, 0.5, 0, 0), sge::color4(1, 0.5, 0, 0), sge::color4(1, 0, 0, 0), sge::light::position_type(0, 0, 0), sge::light::direction_type(0, 0, -1), 0.2, 0, 0, 1, 90));
//	rend->enable_light(0, true);

	sge::frames_counter frames;

	const sge::string some_text(SGE_TEXT("abc\n\nasadgasdgsadg ahsfh ashsdg sadgfas d asd\n asdgg asdg asdg asg asdg sa\nb"));
	while(running)
	{
		frames.update();
		
//		if(ks[sge::kc::key_return])
//			sge::screenshot(rend,pl,"shot.png");

		rend->begin_rendering();

		rend->get_window()->dispatch();
		sge::window::dispatch();
		is->dispatch();
		fn->draw_text(some_text, sge::font_pos(100,100), sge::font_dim(20,500), sge::font_align_h::right, sge::font_align_v::bottom);
		
		//if (console.active())
		//	console.draw();
		rend->end_rendering();
	}
	return EXIT_SUCCESS;
}
catch(const sge::exception& e)
{
	sge::cerr << "Program terminated (sge::exception caught): " << e.what() << '\n';
	return EXIT_FAILURE;
}
/*catch(const std::exception& e)
{
	std::wcerr << "Program terminated (std::exception caught): " << e.what() << '\n';
	return EXIT_FAILURE;
}*/
/*catch(...)
{
	std::cerr << "Program terminated (unknown exception caught)!\n";
	return EXIT_FAILURE;
}*/
