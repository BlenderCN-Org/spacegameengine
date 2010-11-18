/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_FONT_DRAWER_3D_HPP_INCLUDED
#define SGE_FONT_DRAWER_3D_HPP_INCLUDED

#include <sge/font/drawer.hpp>
#include <sge/font/pos.hpp>
#include <sge/font/dim.hpp>
#include <sge/font/image_view.hpp>
#include <sge/font/char_type.hpp>
#include <sge/texture/manager.hpp>
#include <sge/texture/const_part_ptr.hpp>
#include <sge/renderer/device_ptr.hpp>
#include <sge/sprite/system.hpp>
#include <sge/sprite/external_system_decl.hpp>
#include <sge/sprite/object_decl.hpp>
#include <sge/sprite/with_color.hpp>
#include <sge/sprite/with_texture.hpp>
#include <sge/sprite/type_choices.hpp>
#include <sge/sprite/choices.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/image/color/rgba8_format.hpp>
#include <sge/symbol.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/noncopyable.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <map>
#include <vector>

namespace sge
{
namespace font
{

class SGE_CLASS_SYMBOL drawer_3d
:
	public drawer
{
	FCPPT_NONCOPYABLE(drawer_3d)
public:
	SGE_SYMBOL drawer_3d(
		renderer::device_ptr rend,
		image::color::any::object const &
	);

	SGE_SYMBOL ~drawer_3d();

	SGE_SYMBOL void
	begin_rendering(
		size_type buffer_chars,
		pos const &start,
		dim const &size
	);

	SGE_SYMBOL void
	draw_char(
		font::char_type,
		pos const &,
		const_image_view const &data
	);

	SGE_SYMBOL void
	end_rendering();

	SGE_SYMBOL void
	color(
		image::color::any::object const &col
	);
private:
	texture::const_part_ptr const
	cached_texture(
		font::char_type,
		const_image_view const &
	);

	renderer::device_ptr const rend_;

	image::color::any::object col_;

	texture::manager texman_;

	typedef std::map<
		font::char_type,
		texture::const_part_ptr
	> texture_map;

	texture_map textures_;

	typedef sge::sprite::choices<
		sge::sprite::type_choices<
			int,
			float,
			image::color::rgba8_format
		>,
		boost::mpl::vector2<
			sprite::with_color,
			sprite::with_texture
		>
	> sprite_choices;

	typedef sprite::system<
		sprite_choices
	>::type sprite_system;

	typedef sprite::object<
		sprite_choices
	> sprite_object;

	typedef std::vector<
		sprite_object
	> sprite_container;

	sprite_system sys_;

	sprite_container sprites_;
};

}
}

#endif
