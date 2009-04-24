/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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

#ifndef SGE_GUI_DEFAULT_CURSOR_HPP_INCLUDED
#define SGE_GUI_DEFAULT_CURSOR_HPP_INCLUDED

#include <sge/gui/cursor.hpp>
#include <sge/gui/export.hpp>
#include <sge/sprite/object.hpp>
#include <sge/sprite/point.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/texture/no_fragmented.hpp>
#include <sge/image/loader_fwd.hpp>

namespace sge
{
namespace gui
{
class SGE_CLASS_SYMBOL default_cursor : public cursor
{
public:
	SGE_GUI_SYMBOL default_cursor(
		sge::image::loader_ptr,
		sge::renderer::device_ptr);
	SGE_GUI_SYMBOL void pos(point const &);
	SGE_GUI_SYMBOL point const pos() const;
	SGE_GUI_SYMBOL sge::sprite::object const sprite() const;
	SGE_GUI_SYMBOL sge::sprite::object &mutable_sprite();
	SGE_GUI_SYMBOL virtual ~default_cursor();
private:
	sge::texture::no_fragmented texture_;
	sge::sprite::object sprite_;
	sge::sprite::point const click_;
};
}
}

#endif
