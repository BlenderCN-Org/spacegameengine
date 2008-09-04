#include <sge/gui/widgets/button.hpp>
#include <sge/gui/manager.hpp>
#include <sge/gui/events/invalid_area.hpp>
#include <sge/gui/max_dim.hpp>
#include <sge/gui/font_drawer_canvas.hpp>
#include <sge/renderer/scoped_lock.hpp>
#include <sge/renderer/image_view_impl.hpp>
#include <sge/iostream.hpp>
#include <sge/assert.hpp>
#include <sge/font/font.hpp>
#include <sge/math/rect_impl.hpp>

sge::gui::widgets::button::button(
	parent_data parent_,
	string const &text_,
	font::metrics_ptr _font)
	: widget(
			parent_,
			size_policy_t(axis_policy::can_grow,axis_policy::none)),
	  text_(text_),
	  font_(_font),
		mouse_over(false)
{
	if (!font_)
		font_ = parent_manager().standard_font();

	SGE_ASSERT_MESSAGE(font_,SGE_TEXT("button: no standard font could be set by manager"));
}

void sge::gui::widgets::button::process(events::invalid_area const &e)
{
	canvas c = e.canvas();
	
	renderer::color const col = 
		mouse_over ? 
			parent_manager().standard_color_focused() : 
			parent_manager().standard_color();

	c.draw_rect(
		relative_area(),
		col,
		rect_type::filled);

	SGE_ASSERT_MESSAGE(font_,SGE_TEXT("button: font missing while drawing button"));

	// reset font
	c.reset_font(
		font_,
		sge::renderer::colors::black,
		col);
	
	// draw text centered
	c.draw_text(
		text_,
		point(),
		widget::size(),
		font::align_h::center,
		font::align_v::center);
}

sge::gui::dim const sge::gui::widgets::button::size_hint() const
{
	font::font fn(font_,font::drawer_ptr());	

	// NOTE: we have to give text_size a huge rectangle because it won't
	// return a valid rectangle otherwise
	dim const font_dim = math::structure_cast<unit>(
		fn.text_size(text_,math::max_dim<font::unit>()).size());

	return dim(static_cast<unit>(font_dim.w()+2),static_cast<unit>(font_dim.h()+2));
}

void sge::gui::widgets::button::process(events::mouse_enter const &)
{
	mouse_over = true;
	parent_manager().invalidate(absolute_area());
}

void sge::gui::widgets::button::process(events::mouse_leave const &)
{
	mouse_over = false;
	parent_manager().invalidate(absolute_area());
}

void sge::gui::widgets::button::process(events::mouse_click const &)
{
	clicked();
}
