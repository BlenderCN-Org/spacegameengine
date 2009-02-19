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
#include <sge/renderer/parameters.hpp>
#include <sge/window/parameters.hpp>
#include <sge/console/object.hpp>
#include <sge/console/arg_list.hpp>
#include <sge/console/gfx.hpp>
#include <sge/font/system.hpp>
#include <sge/text.hpp>
#include <sge/media.hpp>
#include <sge/exception.hpp>
#include <sge/iostream.hpp>
#include <boost/foreach.hpp>
#include <ostream>
#include <cstdlib>

void fallback(
	sge::string const &arg)
{
	sge::cout << SGE_TEXT("fallback called with argument:") 
                  << arg << SGE_TEXT("\n");
}

void func(
	sge::console::arg_list const &args)
{
	sge::cout << SGE_TEXT("function called with arguments:\n");
	BOOST_FOREACH(sge::console::arg_list::const_reference s,args)
		sge::cout << s << SGE_TEXT("\n");
}

int main()
try
{
	sge::systems::instance const sys(
		sge::systems::list()
		(sge::window::parameters(
			SGE_TEXT("sge console test")
		))
		(sge::renderer::parameters(
			sge::renderer::display_mode(
				sge::renderer::screen_size_t(
					1024,
					768),
				sge::renderer::bit_depth::depth32,
				sge::renderer::refresh_rate_dont_care),
			sge::renderer::depth_buffer::off,
			sge::renderer::stencil_buffer::off,
			sge::renderer::window_mode::windowed))
		(sge::systems::parameterless::input)
		(sge::systems::parameterless::font)
		(sge::systems::parameterless::image));

	sge::console::object o(SGE_TEXT('/'));
	
	sge::signals::connection const c0 = o.insert(
		SGE_TEXT("test"),
		func,
		SGE_TEXT("just a test function"));

	sge::signals::connection const c1 = o.register_fallback(
		&fallback);

	o.eval(SGE_TEXT("/test \"foo bar\" baz quux"));
	o.eval(SGE_TEXT("test \"foo bar\" baz quux"));
	o.eval(SGE_TEXT("/\"test\" \"foo bar\" baz quux"));

	sge::console::gfx gfx_(
		o,
		sys.renderer(),
		sge::renderer::rgba8_color(0,0,0,0),
		sys.font_system()->create_font(
			sge::media_path()/SGE_TEXT("fonts")/SGE_TEXT("default.ttf"),
			15),
		sys.input_system(),
		sge::sprite::object(
			sge::sprite::point(0,0),
			boost::none,
			sge::sprite::dim(400,300)));
	
	gfx_.active(true);
	
	bool running = true;
	while (running)
	{
		gfx_.draw();
	}
}
catch(sge::exception const &e)
{
	sge::cerr << e.what() << SGE_TEXT('\n');
	return EXIT_FAILURE;
}
catch(std::exception const &e)
{
	sge::cerr << e.what() << SGE_TEXT('\n');
	return EXIT_FAILURE;
}
