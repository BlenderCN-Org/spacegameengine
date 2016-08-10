/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/charconv/index_vector.hpp>
#include <sge/charconv/utf8_indices.hpp>
#include <sge/charconv/utf8_string.hpp>
#include <sge/font/dim.hpp>
#include <sge/font/index.hpp>
#include <sge/font/optional_index.hpp>
#include <sge/font/rect.hpp>
#include <sge/font/text.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/unit.hpp>
#include <sge/font/vector.hpp>
#include <sge/font/view_fwd.hpp>
#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image/color/a8.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/image/color/init/alpha.hpp>
#include <sge/image2d/algorithm/fill.hpp>
#include <sge/pango/create_text_layout.hpp>
#include <sge/pango/get_extents.hpp>
#include <sge/pango/get_strong_cursor_pos.hpp>
#include <sge/pango/index.hpp>
#include <sge/pango/text.hpp>
#include <sge/pango/xy_to_index.hpp>
#include <sge/pango/convert/from_rect_scale.hpp>
#include <sge/pango/freetype/make_bitmap.hpp>
#include <fcppt/algorithm/binary_search.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/container/at_optional.hpp>
#include <fcppt/optional/bind.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <pango/pango-layout.h>
#include <pango/pangoft2.h>
#include <iterator>
#include <fcppt/config/external_end.hpp>


sge::pango::text::text(
	PangoLayout &_layout,
	sge::charconv::utf8_string const &_string,
	sge::font::text_parameters const &_text_parameters
)
:
	layout_(
		sge::pango::create_text_layout(
			_layout,
			_string,
			_text_parameters
		)
	),
	extents_(
		sge::pango::get_extents(
			*layout_
		)
	),
	indices_(
		sge::charconv::utf8_indices(
			_string
		)
	)
{
}

sge::pango::text::~text()
{
}

void
sge::pango::text::render(
	sge::font::view const &_view
)
{
	FT_Bitmap bitmap(
		sge::pango::freetype::make_bitmap(
			_view
		)
	);

	// TODO: do this properly
	sge::image2d::algorithm::fill(
		_view,
		sge::image::color::any::object(
			sge::image::color::a8(
				sge::image::color::init::alpha() %= 0.f
			)
		),
		sge::image::algorithm::uninitialized::yes
	);

	::pango_ft2_render_layout(
		&bitmap,
		layout_.get_pointer(),
		fcppt::cast::size<
			int
		>(
			- extents_.ink_rect().get().left()
		),
		fcppt::cast::size<
			int
		>(
			- extents_.ink_rect().get().top()
		)
	);
}

sge::font::rect
sge::pango::text::rect() const
{
	return
		extents_.ink_rect().get();
}

sge::font::dim
sge::pango::text::logical_size() const
{
	return
		extents_.logical_rect().get().size();
}

sge::font::rect
sge::pango::text::cursor_rect(
	sge::font::index const _index
) const
{
	return
		sge::pango::convert::from_rect_scale(
			sge::pango::get_strong_cursor_pos(
				*layout_,
				fcppt::cast::size<
					int
				>(
					fcppt::cast::to_signed(
						FCPPT_ASSERT_OPTIONAL_ERROR(
							fcppt::container::at_optional(
								indices_,
								_index
							)
						).get()
					)
				)
			)
		);
}

sge::font::optional_index
sge::pango::text::pos_to_index(
	sge::font::vector const _pos
) const
{
	return
		fcppt::optional::bind(
			sge::pango::xy_to_index(
				*layout_,
				_pos
			),
			[
				this
			](
				sge::pango::index const _index
			)
			{
				return
					fcppt::optional::map(
						fcppt::algorithm::binary_search(
							indices_,
							fcppt::cast::size<
								sge::charconv::index
							>(
								fcppt::cast::to_unsigned(
									_index.trailing().get()
									+
									_index.result().get()
								)
							)
						),
						[
							this
						](
							sge::charconv::index_vector::const_iterator const _it
						)
						{
							return
								fcppt::cast::size<
									sge::font::index
								>(
									fcppt::cast::to_unsigned(
										std::distance(
											indices_.begin(),
											_it
										)
									)
								);
						}
					);
			}
		);
}
