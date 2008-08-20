/**
\page tutorial_2 Handling input in sge

I don't know how you managed to our program from \ref tut_begin "part 1" but I
hope you realized it's not The Right Way to just choke a program when it's in
the middle of a loop (especially because none of the destructors are called).

So let's add the possibility to close the program by pressing the escape key.
First, we need an <em>input system</em> which handles all types of input
(keyboard, mouse, joystick). We get it the same way we retrieved the renderer
and the image loader: by using <tt>sys</tt>, the initialization class:

\code
sys.init<sge::init::input>();
\endcode

Now we can use the input system to register an <em>input callback</em> which is
called each time the mouse is moved or some key is pressed. We want this
callback to end the main loop. We certainly have more than one choice to do
this, but we'll discuss only one of the solutions to the problem. First, we
modify the main loop:

\code
bool running = true;

// insert callback stuff here - later ;)

while (running)
{
	// original main loop content here
}
\endcode

Now all the callback has to do is set <tt>running</tt> to <tt>false</tt>. We can
pass any functor as a callback to the input system, as long as it's callable via
<tt>operator()</tt> and it accepts a <tt>sge::input::key_pair</tt> argument.
Here's the code for our functor:

\code
class input_functor
{
	public:
	input_functor(bool &running) 
		: running(running) 
	{
	}

	void operator()(sge::input::key_pair const &k) const
	{
		if (k.key().code() == sge::input::kc::key_escape)
			running = false;
	}
	private:
	bool &running;
};
\endcode

Headers to include <sge/input/key_type.hpp>

The functor gets the bool <tt>running</tt> as a reference so any change inside
the class will have an effect on the "outside world". In <tt>operator()</tt>,
we check the key code against a predefined constant
<tt>sge::input::kc::key_escape</tt> which should match the escape key on your
keyboard. The sge::input::kc enum contains all the keys sge supports, as well
as mouse and joystick axes. 

Insert the functor somewhere in your code before <tt>main</tt> (maybe you
choose to put it a seperate header) and insert the following snippet just
before <tt>while (running)</tt>:

\code
sge::scoped_connection conn = 
	sys.input_system->register_callback(input_functor(running));
\endcode

Headers to include <sge/scoped_connection.hpp>

You can now compile and run the program <em>and</em> - close it with the escape key!

The sge::scoped_connection tracks your input connection and closes it when the
<tt>conn</tt> is destroyed (which is incidentally the point where your
input_functor is destroyed as well). 

Now, just for the fun of it, lets make tux follow your mouse. We could use the
same input functor again, but let's write another one - it serves a completely
different purpose, after all:

\code
class sprite_functor
{
	public:
	sprite_functor(sge::sprite::object &s) : s(s) {}

	void operator()(sge::input::key_pair const &k) const
	{
		switch (k.key().code())
		{
			case sge::input::kc::mouse_x_axis:
			s.pos().x() += k.value();
			break;
			case sge::input::kc::mouse_y_axis:
			s.pos().y() += k.value();
			break;
			default: break;
		}
	}
	private:
	sge::sprite::object &s;
};
\endcode

This time, we not only use sge::input::key_pair::key but also
sge::input::key_pair::value to measure how many pixels the mouse moved. We update the sprite's position according to this value. Insert the following somewhere before <tt>while (running)</tt>:

\code
sge::scoped_connection conn_other =
	sys.input_system->register_callback(sprite_functor(my_object));
\endcode

And watch tux move as your mouse moves. That's it for the input tutorial,
there's nothing more to be said, basically. Here's the complete program for your
copy and pasting pleasure:

\code
#include <sge/systems.hpp>
#include <sge/init.hpp>
#include <sge/sprite/system.hpp>
#include <sge/sprite/system_impl.hpp>
#include <sge/sprite/object.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/texture_filter.hpp>
#include <sge/input/key_type.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/exception.hpp>
#include <sge/iostream.hpp>
#include <sge/text.hpp>
#include <sge/scoped_connection.hpp>
#include <exception>
#include <iostream>

namespace
{
class input_functor
{
    public:
    input_functor(bool &running) 
        : running(running) 
    {
    }

    void operator()(sge::input::key_pair const &k) const
    {
        if (k.key().code() == sge::input::kc::key_escape)
            running = false;
    }
    private:
    bool &running;
};

class sprite_functor
{
    public:
    sprite_functor(sge::sprite::object &s) 
			: s(s) 
		{}

    void operator()(sge::input::key_pair const &k) const
    {
        switch (k.key().code())
        {
            case sge::input::kc::mouse_x_axis:
            s.pos().x() += k.value();
            break;
            case sge::input::kc::mouse_y_axis:
            s.pos().y() += k.value();
            break;
            default: break;
        }
    }
    private:
    sge::sprite::object &s;
};
}

int main()
try
{
    sge::systems sys;
    sys.init<sge::init::core>();
    sys.init<sge::init::image_loader>();
    sys.init<sge::init::renderer>(sge::renderer::screen_size_t(640,480));
		sys.init<sge::init::input>();

    sge::sprite::system ss(sys.renderer);
    sge::image::object_ptr image = 
        sys.image_loader->load_image(SGE_TEXT("tux.png"));
    sge::renderer::texture_ptr image_texture = 
        sys.renderer->create_texture(image->view(),sge::renderer::linear_filter);
    sge::sprite::object my_object(
            sge::sprite::point(0,0),
            sge::texture::part_ptr(new sge::texture::part_raw(image_texture)),
            sge::sprite::texture_dim);

    bool running = true;

    sge::scoped_connection conn = 
        sys.input_system->register_callback(input_functor(running));

    sge::scoped_connection conn_other =
        sys.input_system->register_callback(sprite_functor(my_object));

    while (running)
    {
            sge::window::dispatch();
            sge::renderer::scoped_block block_(sys.renderer);
            ss.render(my_object);
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
\endcode

In case you're wondering why I break long lines, that's because the pdf
converter can't handle those properly.

*/
