/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_FONT_TEXT_DRAWER_3D_HPP_INCLUDED
#define SGE_FONT_TEXT_DRAWER_3D_HPP_INCLUDED

#include <sge/font/dim.hpp>
#include <sge/font/image_view.hpp>
#include <sge/font/pos.hpp>
#include <sge/font/text/char_type.hpp>
#include <sge/font/text/drawer.hpp>
#include <sge/font/text/drawer_3d_fwd.hpp>
#include <sge/font/text/symbol.hpp>
#include <sge/image/color/bgra8_format.hpp>
#include <sge/image/color/object_impl.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/context/object_fwd.hpp>
#include <sge/sprite/object_decl.hpp>
#include <sge/sprite/buffers/single_decl.hpp>
#include <sge/sprite/buffers/with_declaration_decl.hpp>
#include <sge/sprite/config/choices.hpp>
#include <sge/sprite/config/float_type.hpp>
#include <sge/sprite/config/normal_size.hpp>
#include <sge/sprite/config/texture_coordinates.hpp>
#include <sge/sprite/config/texture_level_count.hpp>
#include <sge/sprite/config/texture_ownership.hpp>
#include <sge/sprite/config/type_choices.hpp>
#include <sge/sprite/config/unit_type.hpp>
#include <sge/sprite/config/with_color.hpp>
#include <sge/sprite/config/with_texture.hpp>
#include <sge/texture/manager.hpp>
#include <sge/texture/part_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace font
{
namespace text
{

class SGE_CLASS_SYMBOL drawer_3d
:
	public text::drawer
{
	FCPPT_NONCOPYABLE(
		drawer_3d
	);
public:
	SGE_FONT_TEXT_SYMBOL
	drawer_3d(
		renderer::device &,
		image::color::any::object const &
	);

	SGE_FONT_TEXT_SYMBOL
	~drawer_3d();

	SGE_FONT_TEXT_SYMBOL
	void
	begin_rendering(
		sge::renderer::context::object &,
		drawer::size_type buffer_chars,
		font::pos const &start,
		font::dim const &size
	);

	SGE_FONT_TEXT_SYMBOL
	void
	draw_char(
		sge::renderer::context::object &,
		font::text::char_type,
		font::pos const &,
		font::const_image_view const &
	);

	SGE_FONT_TEXT_SYMBOL
	void
	end_rendering(
		sge::renderer::context::object &
	);

	SGE_FONT_TEXT_SYMBOL
	void
	color(
		image::color::any::object const &
	);
private:
	texture::part const &
	cached_texture(
		font::text::char_type,
		font::const_image_view const &
	);

	typedef image::color::bgra8_format color_format;

	typedef sge::image::color::object<
		color_format
	>::type color_object;

	color_object col_;

	texture::manager texman_;

	typedef boost::ptr_map<
		font::text::char_type,
		texture::part
	> texture_map;

	texture_map textures_;

	typedef sge::sprite::config::choices<
		sge::sprite::config::type_choices<
			sge::sprite::config::unit_type<
				int
			>,
			sge::sprite::config::float_type<
				float
			>
		>,
		sge::sprite::config::normal_size,
		boost::mpl::vector2<
			sge::sprite::config::with_color<
				color_format
			>,
			sge::sprite::config::with_texture<
				sge::sprite::config::texture_level_count<
					1u
				>,
				sge::sprite::config::texture_coordinates::automatic,
				sge::sprite::config::texture_ownership::reference
			>
		>
	> sprite_choices;

	typedef sge::sprite::object<
		sprite_choices
	> sprite_object;

	typedef std::vector<
		sprite_object
	> sprite_container;

	typedef sge::sprite::buffers::with_declaration<
		sge::sprite::buffers::single<
			sprite_choices
		>
	> sprite_buffers;

	sprite_buffers sprite_buffers_;

	sprite_container sprites_;
};

}
}
}

#endif
