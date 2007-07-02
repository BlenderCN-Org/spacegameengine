/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <ctime>
#include <cstdlib>
#include <string>
#include <exception>
#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/if.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/lexical_cast.hpp>
#include "../src/math/constants.hpp"
#include "../src/plugin_manager.hpp"
#include "../src/renderer/lock_ptr.hpp"
#include "../src/util.hpp"
#include "../src/sprite/system.hpp"
#include "../src/sprite/sprite.hpp"
#include "../src/renderer/font.hpp"
#include "../src/renderer/renderer.hpp"
#include "../src/renderer/types.hpp"
#include "../src/renderer/renderer_system.hpp"
#include "../src/media.hpp"
#include "../src/gui/manager.hpp"
#include "../src/gui/button.hpp"
#include "../src/gui/text_edit.hpp"
#include "../src/gui/list.hpp"
#include "../src/gui/icon_button.hpp"
#include "../src/gui/frame.hpp"
#include "../src/gui/static_text.hpp"
#include "../src/input/input_system.hpp"
#include "../src/input/key_state_tracker.hpp"
#include "../src/renderer/line_strip.hpp"
#include "../src/renderer/screenshot.hpp"
#include "../src/language.hpp"
#include "../src/endianness.hpp"
#include "../src/audio/audio_loader/audio_loader.hpp"
#include "../src/audio/audio_player/audio_player.hpp"
#include "../src/audio/audio_player/sound.hpp"
#include "../src/exception.hpp"
//#include "../src/console/console_gfx.hpp"
//#include "../src/console/console.hpp"

namespace
{
sge::pos3 rand_point() { return sge::pos3(double(std::rand())/RAND_MAX,double(std::rand())/(RAND_MAX), 0); }

sge::math::vector2 rand_point2() { return sge::math::vector2(double(std::rand())/RAND_MAX,double(std::rand())/(RAND_MAX)); }

struct smallplayer
{
	sge::shared_ptr<sge::sound> sound;
	smallplayer(sge::shared_ptr<sge::sound> sound) : sound(sound) {}
	void operator()() { sound->play(false); } 
};
}

//#define DEBUG std::cout << "Debug mark " << __LINE__ << std::endl;
#define DEBUG

int main()
try
{
	std::srand(std::time(0));
	bool running = true;
	sge::plugin_manager pm;
	const sge::plugin<sge::audio_player>::ptr_type audio_player_plugin = pm.get_plugin<sge::audio_player>().load();

	sge::shared_ptr<sge::audio_player> audio_player(audio_player_plugin->get()());

	typedef std::vector< sge::plugin_manager::plugin_context<sge::audio_loader> > plugin_vector;
  plugin_vector audio_plugins;
  std::copy(pm.begin<sge::audio_loader>(),pm.end<sge::audio_loader>(),
                    std::back_inserter(audio_plugins));

	typedef std::vector<sge::plugin_manager::plugin_context<sge::audio_loader>::ptr_type> loaded_plugins_vector;
	loaded_plugins_vector loaded;

	typedef std::vector< sge::shared_ptr<sge::audio_loader> > audio_loader_vector;
	audio_loader_vector loaders;
	
	sge::shared_ptr<sge::audio_file> soundfile;
	for (plugin_vector::iterator i = audio_plugins.begin(); i != audio_plugins.end(); ++i)
	{
		sge::plugin_manager::plugin_context<sge::audio_loader>::ptr_type np = i->load();
		loaded.push_back(np);
		sge::shared_ptr<sge::audio_loader> j(np->get()());
		loaders.push_back(j);
		const std::string path = sge::media_path()+"/ding.wav";
		if (j->is_valid_file(path))
			soundfile = j->load(path);
	}
	if(!soundfile)
		throw std::runtime_error("ding.wav not found!");
	sge::shared_ptr<sge::sound> sound = audio_player->create_nonstream_sound(soundfile);

	const sge::plugin<sge::renderer_system>::ptr_type renderer_plugin = pm.get_plugin<sge::renderer_system>().load();
	const sge::plugin<sge::input_system>::ptr_type input_plugin = pm.get_plugin<sge::input_system>().load();

	const sge::renderer_system_ptr rs(renderer_plugin->get()());
	sge::renderer_caps_array caps;
	rs->caps(caps);
	/*for(sge::display_mode_array::size_type i = 0; i < caps.at(0).display_modes.size(); ++i)
	{
		const sge::display_mode& mode = caps.at(0).display_modes[i];
		std::cerr << mode.width << ' ' << mode.height << ' ' << sge::bit_depth_bit_count(mode.depth) << ' ' << mode.refresh_rate << '\n';
	}*/

	const sge::renderer_parameters param(sge::display_mode(1024,768,sge::BD_32,100), true);
	const sge::renderer_ptr rend = rs->create_renderer(param);

	const sge::input_system_ptr is(input_plugin->get()(rend->get_window()));

	const sge::plugin<sge::image_loader>::ptr_type image_loader_plugin = pm.get_plugin<sge::image_loader>().load();
	const sge::image_loader_ptr pl(image_loader_plugin->get()());

	const sge::plugin<sge::font_system>::ptr_type font_plugin = pm.get_plugin<sge::font_system>().load();
	const sge::font_system_ptr fs(font_plugin->get()());
	sge::font fn(rend, fs, sge::media_path() + "/fonts/default.ttf", 32);
	sge::sprite_system ss(rend, 0, 2);
	sge::image_ptr im = pl->load_image(sge::media_path() + "/mainskin/cancel_0.png");
	sge::image_ptr im2 = pl->load_image(sge::media_path() + "/mainskin/button.png");
	sge::image_ptr im3 = pl->load_image(sge::media_path() + "/mainskin/clickbox_quad_pressed.png");
	const std::string tex[] = { "bender", "tex2", "tex3" };

	sge::texture_map_ptr tex_map = ss.get_texture_map();
	tex_map->add_texture(im,tex[0]);
	tex_map->add_texture(im2,tex[1]);
	tex_map->add_texture(im3,tex[2]);
//	boost::ptr_vector<sge::sprite> sprites;
//	for(unsigned i = 0; i < 4; ++i)
//		sprites.push_back(new sge::sprite(ss,sge::point(0,i*0.3),sge::dim(0.3,0.3),0,tex[i % 3]));
//	sprites.back().set_color(sge::colors::red);

	std::vector<sge::sprite> sprites;
	for(unsigned i = 0; i < 100; ++i)
		sprites.push_back(sge::sprite(ss,rand_point2(),sge::math::dim2(0.3,0.3),tex[i % 3], sge::colors::white));

	for(unsigned i = 0; i < 100; ++i)
		sprites[i] = sge::sprite(ss,rand_point2(),sge::math::dim2(0.3,0.3),tex[i % 3], sge::colors::white);


	sge::sprite spr(ss, sge::math::vector2(0.25,0.25), sge::math::dim2(0.5,0.5), /*tex[0]*/sge::texture_map::no_texture, sge::colors::yellow);
//	spr.set_texture(tex[1],1);
	sge::sprite spr2(ss, sge::math::vector2(0.25,-0.25), sge::math::dim2(0.25,3), tex[1], sge::colors::red);
	spr2.set_texture(tex[2],1);

	sge::gui::manager man(rend, is, fn, pl, sge::media_path() + "/mainskin/", 0.05);
	sge::gui::frame fr1(man,0,sge::gui::point(0,0),sge::gui::dim(1,1),"cancel_0");
	sge::gui::button btn1(man,&fr1,"Beenden!",sge::gui::point(0,0.1),sge::gui::dim(0.45,0.1));
	sge::gui::button btn2(man,&fr1,"Abspielen!",sge::gui::point(0,0.3),sge::gui::dim(0.45,0.1));
	sge::gui::list list1(man,&fr1,sge::gui::point(0.5,0.1),sge::gui::dim(0.2,0.8));
	sge::gui::icon_button icbtn1(man,&fr1,sge::gui::point(0,0.8),sge::gui::dim(0.5,0.1),"newgame_0","newgame_1","newgame_2");
	sge::gui::text_edit te1(man,&fr1,sge::gui::point(0,0.5),sge::gui::dim(0.7,0.3),"abc");
	list1.push_back("LOL");
	list1.push_back("BAR");
	list1.push_back("ROFL!");

	for(unsigned i = 0; i < 20; ++i)
		list1.push_back(std::string("jgAB") + boost::lexical_cast<std::string>(i));

	sge::gui::static_text st(man, &fr1, "hellothere,i'mamultiline dstatic_text", sge::gui::point(0.5,0.8), sge::gui::dim(0.3,0.1), sge::colors::red);

	using boost::lambda::var;
	using boost::lambda::bind;
	using boost::lambda::_1;
	using boost::lambda::if_;

	boost::signals::scoped_connection cb(is->register_callback(if_(bind(&sge::key_type::code, bind(&sge::key_pair::first,_1)) == sge::KC_ESC)[var(running)=false]));
	boost::signals::scoped_connection cb2(btn1.click_signal.connect(var(running) = false));
	boost::signals::scoped_connection cb3(btn2.click_signal.connect(smallplayer(sound)));

	sge::timer timer(30);
	sge::timer frames(1000);

	unsigned fps = 0, cur_fps = 0;
	sge::space_unit angle = 0;

	sge::key_state_tracker ks(is);

	sge::math::vector3 translation;

	sge::line_strip ls(rend, sge::colors::red);
	for(int i = 0; i < 5; ++i)
		ls.add(rand_point());
	ls.loop(true);

	const std::string some_text("abcdefgh\ni\njklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789\ntesttest");

//	sge::con::console_gfx con(rend, is, fn, sge::image_loader_handler(sge::media_path(), pl));

	while(running)
	{
		if (sound->status() != sge::sound::status_stopped)
			sound->update();

		if(frames.update())
		{
			cur_fps = fps;
			fps = 0;
		}
		translation.x() -= ks[sge::KC_LEFT] * 0.001;
		translation.x() += ks[sge::KC_RIGHT] * 0.001;
		translation.y() -= ks[sge::KC_UP] * 0.001;
		translation.y() += ks[sge::KC_DOWN] * 0.001;
		if(ks[sge::KC_RETURN])
			sge::screenshot(rend,pl,"./shot.png");
		if(timer.update())
			angle += sge::math::PI*0.01;

		spr.rotation(angle);

		rend->begin_rendering();
		rend->get_window()->dispatch();
		sge::window::dispatch();
		is->dispatch();
		ss.transform(sge::math::matrix_translation(translation));
		ss.render();
		man.process();
//		fn.transform(sge::math::matrix_rotation_x(angle));
//		fn.projection(sge::math::transpose(sge::math::matrix_perspective(sge::space_unit(rend->screen_height())/rend->screen_width(),sge::math::PI,0,1)));
//		fn.internal_transformation(sge::math::matrix_identity());
		fn.height_pixel_scale(1);
		fn.height(0.05);
		fn.draw_text(some_text,sge::font_pos(0.2,0.2),sge::font_size(0.8,0.8),sge::colors::green/*, sge::FTF_NoLineWrap*/);
		fn.transform(sge::math::matrix_identity());
		fn.draw_text(boost::lexical_cast<std::string>(cur_fps),sge::font_pos(0.1,0),sge::font_size(1,1),sge::colors::purple);
		ls.render();
//		con.draw();
//		con.tick();
		rend->end_rendering();
		++fps;
	}
	return EXIT_SUCCESS;
}
catch(const std::exception& e)
{
	std::cerr << "Program terminated (std::exception caught): " << e.what() << '\n';
	return EXIT_FAILURE;
}
catch(...)
{
	std::cerr << "Program terminated (unknown exception caught)!\n";
	return EXIT_FAILURE;
}
