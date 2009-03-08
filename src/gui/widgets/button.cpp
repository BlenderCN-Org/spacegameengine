#include <sge/gui/widgets/button.hpp>
#include <sge/gui/events/key.hpp>
#include <sge/gui/manager.hpp>
#include <sge/gui/widgets/log.hpp>
#include <sge/input/key_type.hpp>
#include <sge/assert.hpp>

namespace
{
sge::gui::logger mylogger(sge::gui::widgets::global_log(),SGE_TEXT("button"),true);
}

sge::gui::widgets::button::button(
	parent_data const &_parent,
	parameters _params,
	string const &_text,
	font::metrics_ptr _font)
	: widget(
			_parent,
			_params.size_policy(
				size_policy_t(
					axis_policy::can_grow,
					axis_policy::none)).
				keyboard_focus(
					keyboard_focus::receive)),
	  text_(_text),
	  font_(_font),
		mouse_over_(false),
		key_over_(false)
{
	if (!font_)
		font_ = parent_manager().standard_font();
	
	SGE_ASSERT_MESSAGE(font_,SGE_TEXT("button: no standard font could be set by manager"));
}

void sge::gui::widgets::button::process(events::mouse_enter const &)
{
	mouse_over_ = true;
	parent_manager().invalidate(*this,absolute_area());
}

void sge::gui::widgets::button::process(events::mouse_leave const &)
{
	mouse_over_ = false;
	parent_manager().invalidate(*this,absolute_area());
}

void sge::gui::widgets::button::process(events::mouse_click const &)
{
	clicked_();
}

sge::gui::key_handling::type sge::gui::widgets::button::process(
	events::key const &k)
{
	if (k.value().key().code() == input::kc::key_return)
	{
		clicked_();
		return key_handling::ignore;
	}
	return key_handling::process;
}

void sge::gui::widgets::button::process(events::keyboard_enter const &)
{
	SGE_LOG_DEBUG(mylogger,log::_1 << SGE_TEXT("got keyboard_enter"));
	key_over_ = true;
	parent_manager().invalidate(*this,absolute_area());
}

void sge::gui::widgets::button::process(events::keyboard_leave const &)
{
	SGE_LOG_DEBUG(mylogger,log::_1 << SGE_TEXT("got keyboard_leave"));
	key_over_ = false;
	parent_manager().invalidate(*this,absolute_area());
}

sge::signals::connection const sge::gui::widgets::button::register_clicked(
	clicked_fn const &_clicked)
{
	return clicked_.connect(_clicked);
}
