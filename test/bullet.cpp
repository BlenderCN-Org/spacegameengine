#include <sge/time/timer.hpp>
#include <sge/time/sleep.hpp>
#include <sge/time/second.hpp>
#include <sge/time/second_f.hpp>
#include <sge/iostream.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/states.hpp>
#include <sge/renderer/colors.hpp>
#include <sge/renderer/device.hpp>
#include <sge/math/vector/io.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/sprite/system.hpp>
#include <sge/sprite/object.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/texture_filter.hpp>
#include <sge/renderer/device.hpp>
#include <sge/image/loader.hpp>
#include <sge/image/object.hpp>
#include <sge/mainloop/dispatch.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/window/parameters.hpp>
#include <sge/collision/sattelite.hpp>
#include <sge/collision/objects/circle.hpp>
#include <sge/collision/system.hpp>
#include <sge/exception.hpp>
#include <sge/iostream.hpp>
#include <sge/text.hpp>
#include <sge/make_shared_ptr.hpp>

#include <boost/bind.hpp>
#include <iostream>
#include <exception>
#include <ostream>
#include <iostream>
#include <cstdlib>

namespace
{
bool dispatch(
	sge::collision::sattelite const &,
	sge::collision::sattelite const &)
{
	std::cerr << "dispatch called\n";
	return true;
}

void collision(sge::collision::sattelite &,sge::collision::sattelite &)
{
	std::cerr << "a collision!\n";
}

class object : public sge::collision::sattelite
{
	public:
	object(sge::sprite::object &sprite_)
			: sprite_(sprite_)
	{
	}

	void position_change(sge::collision::point const &p)
	{
		sge::cerr << "position_change to " << p << "\n";
		sprite_.x() = static_cast<sge::sprite::unit>(p.x());
		sprite_.y() = static_cast<sge::sprite::unit>(p.y());
	}
	private:
	sge::sprite::object &sprite_;
};
}

int main()
try
{
	sge::systems::instance const sys(
		sge::systems::list()
		(sge::window::parameters(
			SGE_TEXT("sge physics")
		))
		(sge::renderer::parameters(
			sge::renderer::display_mode(
				sge::renderer::screen_size_t(
					640,
					480),
				sge::renderer::bit_depth::depth32,
				sge::renderer::refresh_rate_dont_care),
			sge::renderer::depth_buffer::off,
			sge::renderer::stencil_buffer::off,
			sge::renderer::window_mode::windowed))
		(sge::systems::parameterless::collision_system)
		(sge::systems::parameterless::image));
	
	sys.collision_system()->test_callback(&dispatch);

	sge::signals::connection c = sys.collision_system()->register_callback(&collision);

	sge::sprite::object s_a(
		sge::sprite::point(100,100),
		sge::sprite::defaults::texture_,
		sge::sprite::dim(10,10));

	sge::sprite::object s_b(
		sge::sprite::point(200,100),
		sge::sprite::defaults::texture_,
		sge::sprite::dim(10,10));
	
	sge::collision::objects::circle_ptr o_a = 
		sys.collision_system()->create_circle(
			sge::collision::sattelite_ptr(
				new object(s_a)),
			static_cast<sge::collision::unit>(5));

	sge::collision::objects::circle_ptr o_b = 
		sys.collision_system()->create_circle(
			sge::collision::sattelite_ptr(
				new object(s_b)),
			static_cast<sge::collision::unit>(5));

	o_a->center(sge::collision::point(100,100,0));
	o_b->center(sge::collision::point(200,100,0));
	o_a->speed(sge::collision::point(20,0,0));
	o_b->speed(sge::collision::point(-20,0,0));


	sge::sprite::system ss(sys.renderer());
	
	sys.renderer()->state(
		sge::renderer::state::list
			(sge::renderer::state::bool_::clear_backbuffer = true)
			(sge::renderer::state::color_::clear_color = sge::renderer::colors::black())
		);

	bool running = true;
	sge::time::timer frame_timer(sge::time::second(1));
	while (running)
	{
		sys.collision_system()->update(frame_timer.elapsed_frames());

		sge::time::sleep(sge::time::second_f(1.0f/60.0f));

		sge::mainloop::dispatch();
		sge::renderer::scoped_block const block_(sys.renderer());

		sge::sprite::container sprites;
		sprites.push_back(s_a);
		sprites.push_back(s_b);
		ss.render(sprites.begin(),sprites.end());
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
