#include <sge/gui/canvas/font_drawer.hpp>
#include <sge/math/rect.hpp>
#include <sge/renderer/transform_pixels.hpp>
#include <sge/renderer/make_const_image_view.hpp>
#include <sge/renderer/subimage_view.hpp>
#include <sge/iostream.hpp>
#include "log.hpp"
#include "utility/font_blitter.hpp"

namespace
{
sge::gui::logger mylogger(sge::gui::canvas::global_log(),SGE_TEXT("font_drawer"),true);
}

sge::gui::canvas::font_drawer::font_drawer(
	image_view &texture_,
	color c,
	boost::optional<string::size_type> character_pos,
	point *p)
	: texture_(texture_),
	  c(c),
		counter(0),
		character_pos(character_pos),
		p(p)
{
	SGE_LOG_DEBUG(mylogger,log::_1 << SGE_TEXT("instantiated"));
}

void sge::gui::canvas::font_drawer::begin_rendering(
	size_type const /*buffer_chars*/,
	font::pos const &/*pos*/,
	font::dim const /*size*/)
{
}

void sge::gui::canvas::font_drawer::draw_char(
	char_type const, 
	font::pos const &pos, 
	font::const_image_view const &data)
{
	SGE_LOG_DEBUG(mylogger,log::_1 << SGE_TEXT("drawing char"));

	image_view const sub_view = renderer::subimage_view(
			texture_,
			renderer::lock_rect(
				static_cast<renderer::size_type>(pos.x()),
				static_cast<renderer::size_type>(pos.y()),
				static_cast<renderer::size_type>(pos.x()+data.width()),
				static_cast<renderer::size_type>(pos.y()+data.height())));
	
	if (character_pos)
		sge::cerr << "counter: " << counter 
		          << " | character pos: " << *character_pos << "\n";
	else
		sge::cerr << "character position invalid\n";

	if (character_pos && counter++ == *character_pos)
		*p = math::structure_cast<unit>(pos);
	
	renderer::transform_pixels(
		data,
		renderer::make_const_image_view(sub_view),
		sub_view,
		utility::font_blitter(c));
}

void sge::gui::canvas::font_drawer::end_rendering()
{
}
