#include <sge/renderer/texture_rw.hpp>
#include <sge/renderer/texture_software.hpp>

#include <sge/gui/manager.hpp>
#include <sge/gui/widgets/button.hpp>
#include <sge/gui/widgets/container.hpp>
#include <sge/gui/layouts/vertical.hpp>
#include <sge/gui/layouts/horizontal.hpp>
#include <sge/gui/font_drawer_canvas.hpp>

#include <sge/iostream.hpp>
#include <sge/string.hpp>
#include <sge/exception.hpp>
#include <sge/systems.hpp>
#include <sge/font/font.hpp>
#include <sge/init.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/font/system.hpp>
#include <sge/renderer/scoped_lock.hpp>
#include <sge/sprite/object.hpp>
#include <sge/sprite/system.hpp>
#include <sge/font/drawer.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/input/key_state_tracker.hpp>
#include <sge/renderer/texture_filter.hpp>

#include <iostream>

namespace
{
struct end_program
{
	end_program(bool &running) : running(running) {}
	void operator()() const { running = false; }
	bool &running;
};
}

int main()
try
{
	sge::systems sys;
	// basic stuff
	sys.init<sge::init::core>();
	sys.init<sge::init::renderer>(sge::renderer::screen_size_t(640,480));
	sys.init<sge::init::input>();
	sys.init<sge::init::image_loader>();
	sys.init<sge::init::font>();
	
	sge::gui::manager m(sys.renderer,sys.image_loader,sys.input_system,sys.font_system);

	sge::gui::widgets::container top(sge::gui::widget::parent_data(m),sge::gui::point(10,10),sge::gui::dim(300,300));
	top.layout<sge::gui::layouts::horizontal>();

	sge::gui::widgets::container left((sge::gui::widget::parent_data(top)));
	left.layout<sge::gui::layouts::vertical>();

	sge::gui::widgets::container right((sge::gui::widget::parent_data(top)));
	right.layout<sge::gui::layouts::vertical>();

	sge::gui::widgets::button left_top(
		sge::gui::widget::parent_data(left),
		SGE_TEXT("(left top) me!"));
	
		
	sge::gui::widgets::button left_bottom(
		sge::gui::widget::parent_data(left),
		SGE_TEXT("(left bottom) me!"));

	sge::gui::widgets::button right_top(
		sge::gui::widget::parent_data(right),
		SGE_TEXT("(right top) me!"));

	sge::gui::widgets::button right_bottom(
		sge::gui::widget::parent_data(right),
		SGE_TEXT("(right bottom) me!"));

	assert(top.layout());
	assert(right.layout());
	assert(left.layout());
	
	// compile the stuff!
	top.compile();
	//top.compile();

	//top.size(sge::gui::dim(500,500));
	
	bool running = true;
	end_program p(running);
	left_top.clicked.connect(p);
	while (running)
	{
		sge::window::dispatch();
		sge::renderer::scoped_block block(sys.renderer);
		m.draw();
	}
} 
catch (sge::exception const &e)
{
	sge::cerr << SGE_TEXT("caught sge exception: ") << e.what() << SGE_TEXT("\n");
}
catch (std::exception const &e)
{
	std::cerr << "caught std exception: " << e.what() << "\n";
}
catch (...)
{
	std::cerr << "caught unknown exception\n";
}
