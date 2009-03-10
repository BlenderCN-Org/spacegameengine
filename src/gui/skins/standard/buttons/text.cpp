#include "../../../utility/max_dim.hpp"
#include <sge/gui/skins/standard.hpp>
#include <sge/gui/canvas.hpp>
#include <sge/gui/log.hpp>
#include <sge/gui/widgets/buttons/text.hpp>
#include <sge/gui/events/invalid_area.hpp>
#include <sge/math/dim/output.hpp>
#include <sge/font/object.hpp>
#include <sge/font/text_size_t.hpp>
#include <sge/renderer/colors.hpp>
#include <sge/media.hpp>
#include <sge/assert.hpp>
#include <sge/structure_cast.hpp>

namespace
{
sge::gui::logger mylogger(
	sge::gui::global_log(),
	SGE_TEXT("skins: standard: buttons: text"),
	false);
}

void sge::gui::skins::standard::draw(
	widgets::buttons::text const &b,
	events::invalid_area const &e)
{
	if (b.size() == dim::null())
		return;

	resize_buffer(b);

	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("creating canvas from buffer"));
	canvas::object c(b.buffer());

	// Background
	c.draw_rect(
		rect(c.size()),
		b.mouse_over() 
			? internal_color(0xee,0xeb,0xe7,0xff)
			: internal_color(0xdc,0xda,0xd5,0xff),
		canvas::rect_type::solid);
	
	c.draw_line(
		point(0,0),
		point(c.size().w()-1,0),
		internal_color(0xff,0xff,0xff,0xff));

	c.draw_line(
		point(0,0),
		point(0,c.size().h()-1),
		internal_color(0xff,0xff,0xff,0xff));

	c.draw_line(
		point(c.size().w()-2,1),
		point(c.size().w()-2,c.size().h()-2),
		internal_color(0x9e,0x9a,0x91,0xff));

	c.draw_line(
		point(1,c.size().h()-2),
		point(c.size().w()-2,c.size().h()-2),
		internal_color(0x9e,0x9a,0x91,0xff));

	c.draw_line(
		point(c.size().w()-1,0),
		point(c.size().w()-1,c.size().h()-1),
		internal_color(0x00,0x00,0x00,0xff));

	c.draw_line(
		point(0,c.size().h()-1),
		point(c.size().w()-1,c.size().h()-1),
		internal_color(0x00,0x00,0x00,0xff));
	
	if (b.key_over())
	{
		c.draw_line(
			point(2,2),
			point(c.size().w()-3,2),
			internal_color(0x00,0x00,0x00,0xff),
			canvas::line_type::dashed);

		c.draw_line(
			point(c.size().w()-3,2),
			point(c.size().w()-3,c.size().h()-3),
			internal_color(0x00,0x00,0x00,0xff),
			canvas::line_type::dashed);

		c.draw_line(
			point(c.size().w()-3,c.size().h()-3),
			point(2,c.size().h()-3),
			internal_color(0x00,0x00,0x00,0xff),
			canvas::line_type::dashed);

		c.draw_line(
			point(2,c.size().h()-3),
			point(2,2),
			internal_color(0x00,0x00,0x00,0xff),
			canvas::line_type::dashed);
	}

	SGE_ASSERT_MESSAGE(
		b.font(),
		SGE_TEXT("button: font missing while drawing button"));

	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("drawing text (button \"")
		        << b.caption()
		        << SGE_TEXT("\")"));

	// draw text centered
	c.draw_text(
		b.font(),
		renderer::colors::black(),
		b.caption(),
		point::null(),
		c.size(),
		font::align_h::center,
		font::align_v::center);

	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("blitting (button \"")
		        << b.caption()
		        << SGE_TEXT("\")"));

	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("source rect is \"")
		        << rect(b.absolute_pos(),c.size())
		        << SGE_TEXT(", invalid rect is ")
						<< e.area());

	blit_invalid(b,c,e);
}

sge::gui::dim const sge::gui::skins::standard::size_hint(
	widgets::buttons::text const &b) const
{
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("calling size hint for button"));

	font::object fn(b.font());	

	// NOTE: we have to give text_size a huge rectangle because it won't
	// return a valid rectangle otherwise
	dim const font_dim = structure_cast<dim>(
		fn.text_size(b.caption(),utility::max_dim<font::unit>()).size());

	return dim(static_cast<unit>(font_dim.w()+2),static_cast<unit>(font_dim.h()+2));
}
