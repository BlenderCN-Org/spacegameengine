#ifndef SGE_GUI_WIDGETS_BUTTON_HPP_INCLUDED
#define SGE_GUI_WIDGETS_BUTTON_HPP_INCLUDED

#include <sge/gui/widget.hpp>
#include <sge/export.hpp>
#include <sge/font/metrics_fwd.hpp>
#include <sge/signals/signal.hpp>
#include <sge/signals/connection.hpp>
#include <boost/function.hpp>

namespace sge
{
namespace gui
{
namespace widgets
{
class SGE_CLASS_SYMBOL button : public widget
{
	public:
	SGE_SYMBOL button(
		parent_data const &,
		parameters,
		string const &,
		font::metrics_ptr = font::metrics_ptr());

	dim const minimum_size() const { return size_hint(); }
	string const text() const { return text_; }
	font::metrics_ptr const font() const { return font_; }
	bool mouse_over() const { return mouse_over_; }
	bool key_over() const { return key_over_; }
	SGE_SYMBOL void process(events::mouse_enter const &);
	SGE_SYMBOL void process(events::mouse_leave const &);
	SGE_SYMBOL void process(events::mouse_click const &);
	SGE_SYMBOL void process(events::keyboard_enter const &);
	SGE_SYMBOL key_handling::type process(events::key const &);
	SGE_SYMBOL void process(events::keyboard_leave const &);

	typedef boost::function<void ()> clicked_fn;
	signals::connection const register_clicked(
		clicked_fn const &);
	private:
	using widget::process;
	string text_;
	font::metrics_ptr font_;
	bool mouse_over_;
	bool key_over_;
	boost::signal<void ()> clicked_;
};
}
}
}

#endif
