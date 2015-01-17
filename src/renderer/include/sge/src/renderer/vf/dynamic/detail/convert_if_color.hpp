/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SRC_RENDERER_VF_DYNAMIC_DETAIL_CONVERT_IF_COLOR_HPP_INCLUDED
#define SGE_SRC_RENDERER_VF_DYNAMIC_DETAIL_CONVERT_IF_COLOR_HPP_INCLUDED

#include <sge/image/color/format.hpp>
#include <sge/renderer/vf/dynamic/color.hpp>
#include <sge/renderer/vf/dynamic/color_format_vector.hpp>
#include <sge/renderer/vf/dynamic/offset.hpp>
#include <sge/renderer/vf/dynamic/stride.hpp>
#include <sge/src/renderer/vf/dynamic/detail/element_converter.hpp>
#include <sge/src/renderer/vf/dynamic/detail/element_converter_vector.hpp>
#include <sge/src/renderer/vf/dynamic/detail/matching_color_format.hpp>
#include <fcppt/variant/holds_type.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{
namespace dynamic
{
namespace detail
{

template<
	typename Variant
>
void
convert_if_color(
	sge::renderer::vf::dynamic::detail::element_converter_vector &_converters,
	Variant const &_variant,
	sge::renderer::vf::dynamic::color_format_vector const &_formats,
	sge::renderer::vf::dynamic::stride const _stride,
	sge::renderer::vf::dynamic::offset const _offset
)
{
	if(
		!fcppt::variant::holds_type<
			sge::renderer::vf::dynamic::color
		>(
			_variant
		)
	)
		return;

	sge::image::color::format const format(
		_variant. template get<
			sge::renderer::vf::dynamic::color
		>().color_format()
	);

	_converters.push_back(
		sge::renderer::vf::dynamic::detail::element_converter{
			format,
			sge::renderer::vf::dynamic::detail::matching_color_format(
				format,
				_formats
			),
			_stride,
			_offset
		}
	);
}

}
}
}
}
}

#endif
