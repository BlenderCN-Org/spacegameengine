/** 
\page tut_01 Beginner tutorial
\section abstract Abstract
In this small tutorial we'll first write a program which displays an image
on the screen. We'll then modify this program to move the image on the
screen using the arrow keys on your keyboard or the mouse.

\section sec2 Initializing sge subsystems
We want to draw an image on the screen, so we need at least two things: An
<em>image loader</em> and a <em>renderer</em>. We also need to initialize the
sge "core". 

Normally, you would have to get a renderer and an image loader plugin, load
them and create the according renderers and image loaders from those plugins,
but there's a shortcut which we'll take here since it's probably your first
glance at sge. 

To initialize sge we create a sge::systems::instance object, which will handle
the dirty details of initialization for us. The systems::instance object needs
a list of things we want it to initialize. For the renderer we pass a
renderer::parameters structure since we have to tell the renderer a few
settings. The image plugin can be initialized just by passing
systems::parameterless::image. Also the window::parameters structure is
needed because the renderer needs an initialized window.

\code
sge::systems::instance const sys(
	sge::systems::list()
	(sge::window::parameters(
		SGE_TEXT("sge tutorial01")
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
	(sge::systems::parameterless::image));
\endcode

You have to include <sge/systems/instance.hpp>, <sge/systems/list.hpp>,
<sge/window/parameters.hpp>, <sge/text.hpp> and
<sge/renderer/parameters.hpp> for that.

And that's it. If you start the program now you probably see a 640x480 window
popping up for a split second. Our first sge program! Just for convenience,
here's the whole program:

\code
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/window/parameters.hpp>
#include <sge/text.hpp>

int main()
{
	sge::systems::instance const sys(
		sge::systems::list()
		(sge::window::parameters(
			SGE_TEXT("sge tutorial01")
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
		(sge::systems::parameterless::image));
}
\endcode

Now that we've initialized the subsystems, we can access them via
<tt>sys.renderer()</tt> and <tt>sys.image_loader()</tt>.

\section sec3 Drawing an image

The next goal is to draw an image on our newly created window which we can move
around later on. In computer graphics a two dimensional "object" is called a
<em>sprite</em>. To draw one or more sprites in sge you have to create a
sge::sprite::system, which gets the renderer in its constructor.

\code
sge::sprite::system ss(sys.renderer());
\endcode

Files to include: <sge/sprite/system.hpp>, <sge/renderer/device.hpp>

Now for the tricky part, loading the image and attaching it to an
sge::sprite::object.
We'll be using the image called \em tux.png which is located in
the \em image directory under the documentation directory. Just
copy it into the directory of your sample application. First, we use the image
loader to load the image:

\code
sge::image::object_ptr const image = sys.image_loader()->load(SGE_TEXT("tux.png"));
\endcode

Files to include: <sge/text.hpp>, <sge/image/loader.hpp>, <sge/image/object.hpp>

There are a few new things here, first of all <tt>sys.image_loader()</tt> is a
smart pointer, so we cannot use the . (dot) operator to access the \link
sge::image::loader::load load\endlink function. The same applies
to renderer and any other subsystem class.

And what about this strange SGE_TEXT thingy around the string? Well, if you want
to use character literals in sge, they have to be <em>narrow</em> literals and
you have to embrace them with SGE_TEXT; all this macro does is convert the literal to
sge::string's internal format (which is wide or narrow, depending on the
SGE_NARROW_STRING macro which you can specify when you compile sge).

The rest of the code should be pretty clear, the load function returns an
sge::image::object_ptr (again a smart pointer) which we assign to the variable
<em>image</em>.

Okay, now we've got an image, but a sprite needs a <em>texture</em> which is
stored in the fast VRAM of your graphics card instead of the system RAM.
Creating textures is the renderer's job:

\code
sge::renderer::texture_ptr const image_texture = 
	sys.renderer()->create_texture(
		image->view(),
		sge::renderer::linear_filter,
		sge::renderer::resource_flags::none);
\endcode

Files to include: <sge/renderer/texture_filter.hpp>,
<sge/renderer/texture.hpp>

This version of \link sge::renderer::device::create_texture create_texture
\endlink takes a <em>renderer::const_image_view</em>. Luckily, our image object
has a \link sge::image::object::view view \endlink function which returns just
this. The second argument is the filter which is applied to the texture when
it's rendered. Linear filter actually blurs the texture a bit, but it's the
filter you'll most often want to use for sprites. An alternative would be
sge::renderer::point_filter, which does no filtering at all, so with enlarged
low resolution images, pixels can be seen. The last argument just specifies
that we're not interested in changing this texture dynamically.

Anyway, in theory, we would now be able to use the texture to paste it onto a
sprite. If you look at the constructor of sge::sprite::object you'll see that it
doesn't take a <em>texture_ptr</em>, but a <em>const_part_ptr</em>. That's because you
don't have to create a separate texture for each sprite, but you can also create
a big texture containing smaller sub textures and assign those sub textures to
the sprites. This is called "atlasing" and can really boost performance since
changing the current texture on the videocard is considered expensive.

Since we're not going to use atlasing in the tutorial, we create a part which is
just a wrapper for a single texture. Watch!

\code
sge::sprite::object const my_object(
	sge::sprite::point(0, 0),
	sge::texture::const_part_ptr(
		sge::make_shared_ptr<
			sge::texture::part_raw
		>(
			image_texture)),
	sge::sprite::texture_dim);
\endcode

Files to include: <sge/texture/part_raw.hpp>, <sge/sprite/object.hpp>,
<sge/make_shared_ptr.hpp>.

We use make_shared_ptr to create a texture::const_part_ptr from a new
texture::part_raw which takes image_texture as an argument.
The reason behind this is that having a new expression in an argument list
which is given to a shared ptr might leak memory because even the order of
evaluation of subexpressions is unspecified.

The rest of the code should be pretty self explanatory now. Note that
<tt>my_object</tt> is not a smart pointer but a "real" object. We put the
sprite on the top left corner of the screen and give it our test texture. For
the size parameter, we specify the constant <tt>texture_dim</tt> which tells
sge to choose the texture's dimensions for the sprite's size.

\subsection The main loop

Having created all the stuff we need, the program still closes immediately after
starting it. So let's add a main loop which keeps it going!

\code
while (true)
{
	sge::mainloop::dispatch();
	sge::renderer::scoped_block const block_(sys.renderer());
	ss.render(my_object);
}
\endcode

Files to include: <sge/renderer/scoped_block.hpp>,
<sge/mainloop/dispatch.hpp>.

Inside the endless loop (we'll fix that when we introduce the <em>input
system</em>), sge::mainloop::dispatch is called.
This calls the dispatch function for all <em>dispatchable</em> objects
that have been created so far.

If you want to render something on the screen, you have to call
renderer::begin_rendering and renderer::end_rendering. Yet, since we write our code
exception safe (!), we use the renderer::scoped_block class which calls these
functions in its constructor and destructor.

Finally, we tell the sprite system to render our sprite.

Here's the complete program:

\include tutorial_01.cpp

I added code to catch any sge exceptions (the most common one in this piece of
code would be <em>could not find image 'tux.png'</em>) and also standard exceptions,
just to make sure. In case you wonder, yes, it's legal to write <tt>try</tt>
directly after the declaration line of a function. 

Note that there are sge
iostream equivalents (called <tt>sge::cerr</tt>, <tt>sge::cout</tt> and
<tt>sge::clog</tt>) so you don't have to worry if you should use
<tt>std::cout</tt> or <tt>std::wcout</tt>.

When you start the program now you'll see tux on the top left corner of the
screen. To close the program... well, do something radical, it won't close that
easily. But we're working on that in \ref tutorial_2 "part 2" of the tutorial,
where we add input support.
*/
