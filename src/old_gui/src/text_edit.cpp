/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <limits>
#include <locale>
#include "../text_edit.hpp"
#include "../manager.hpp"
#include "../skin.hpp"
#include "../../unicode.hpp"
#include "../../renderer/font.hpp"

const sge::font_flag_t flags = sge::font_flags::align_left | sge::font_flags::align_vcenter | sge::font_flags::no_multi_line;

sge::gui::text_edit::text_edit(manager& m, element* const parent, const point pos, const dim sz, const string& _text, const color _text_color, const bool visible, const bool enabled)
: rectangle(m, parent, pos, sz, skin::textedit_name, visible, enabled),
  my_font(m.get_font()),
  _text(_text),
  _text_color(_text_color),
  text_start(0),
  cursor_pos(0),
  cur(m.get_sprite_system(),point(0,0),dim(0,0), 500)
{}

void sge::gui::text_edit::on_key_press(const keyboard_button_event& event)
{
	const key_code key = event.code();
	const key_type::char_type char_code = event.char_code();

	switch(key) {
	case KC_LEFT:
		if(cursor_pos > 0)
			decrease_cursor_pos();
		break;
	case KC_RIGHT:
		if(cursor_pos < _text.size())
			increase_cursor_pos();
		break;
	case KC_HOME:
		cursor_pos = 0;
		break;
	case KC_END:
		cursor_pos = _text.size();
		break;
	case KC_BACK:
		if(cursor_pos > 0)
		{
			_text.erase(cursor_pos-1,1);
			decrease_cursor_pos();
		}
		break;
	case KC_DEL:
		if(cursor_pos < _text.size())
			_text.erase(cursor_pos,1);
		break;
	default:
		if(isprint(char_code))
		{
			_text.insert(cursor_pos,1,char_code);
			increase_cursor_pos();
		}
		break;
	}
}

void sge::gui::text_edit::on_click(const mouse_button_event& event)
{
	const unit x = event.pos().x();
	cursor_pos = text_start;
	string::size_type& i = cursor_pos;
	for(unit sz = 0; i < _text.size(); ++i)
	{
		const unit delta = my_font.char_space(_text.at(i));
		if(sz + delta > x || sz + delta + cur.width() > width())
			break;
		sz += delta;
	}
}

void sge::gui::text_edit::increase_cursor_pos()
{
	++cursor_pos;
	while(text_start < text().size() && my_font.text_size(_text.begin() + text_start, _text.begin() + cursor_pos, std::numeric_limits<unit>::max(), flags).w() > text_width())
		++text_start;
}

void sge::gui::text_edit::decrease_cursor_pos()
{
	--cursor_pos;
	if(cursor_pos <  text_start)
		text_start = cursor_pos;
}

void sge::gui::text_edit::on_draw(const draw_event& event)
{
	cur.size() = dim(my_font.char_space(' ') / 2, height() * unit(0.9));
	rectangle::on_draw(event);
	my_font.draw_text(_text.substr(text_start,_text.size()-text_start), event.pos(), size(), _text_color, flags);
	if(m.focus() == this)
	{
		point pos = event.pos();
		pos.x() += my_font.line_width(_text.begin() + text_start, _text.begin() + cursor_pos, width(), flags).width;

		pos.y() += height() / 2 - cur.height() / 2;
		cur.pos() = pos;
		cur.draw();
	}
}

void sge::gui::text_edit::text(const string& ntext)
{
	cursor_pos = text_start = 0;
	_text = ntext;
}

sge::gui::unit sge::gui::text_edit::text_height() const
{
	return height()*0.8f;
}

sge::gui::unit sge::gui::text_edit::text_width() const
{
	return width()-0.01f;
}

const sge::string& sge::gui::text_edit::text() const
{
	return _text;
}

sge::color sge::gui::text_edit::text_color() const
{
	return _text_color;
}

void sge::gui::text_edit::text_color(const color c)
{
	_text_color = c;
}
