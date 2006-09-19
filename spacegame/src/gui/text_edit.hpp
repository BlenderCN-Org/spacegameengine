#ifndef SGE_GUI_TEXT_EDIT_HPP_INCLUDED
#define SGE_GUI_TEXT_EDIT_HPP_INCLUDED

#include "./types.hpp"
#include "./rectangle.hpp"
#include "./text_cursor.hpp"
#include "../core/renderer/font_types.hpp"

namespace sge
{
class font;

namespace gui
{

class manager;

class text_edit : public rectangle {
public:
	text_edit(manager& m, element* parent, point pos, dim sz, const std::string& text = "", color text_color = colors::white, bool visible = true, bool enabled = true);
	const std::string& text() const { return _text; }
	void text(const std::string& text);
	color text_color() const { return _text_color; }
	void text_color(const color c) { _text_color = c; }
private:
	virtual void on_key_press(const keyboard_button_event& event);
	virtual void on_click(const mouse_button_event& event);
	virtual void on_draw(const draw_event& event);
	void increase_cursor_pos();
	void decrease_cursor_pos();
	unit text_width() const;
	unit text_height() const;
	void set_height();
	
	font&                  my_font;
	std::string            _text;
	color                  _text_color;
	std::string::size_type text_start,
	                       cursor_pos;
	text_cursor            cur;
	static const font_flag_t flags = FTF_AlignLeft | FTF_AlignVCenter | FTF_NoMultiLine;
};

typedef shared_ptr<text_edit> text_edit_ptr;

}
}

#endif
