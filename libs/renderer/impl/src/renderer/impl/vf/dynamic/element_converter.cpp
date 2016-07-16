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


#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/color/format_stride.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/pitch.hpp>
#include <sge/image2d/algorithm/copy_and_convert.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/make.hpp>
#include <sge/image2d/view/make_const.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/renderer/raw_pointer.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <sge/renderer/vf/dynamic/offset.hpp>
#include <sge/renderer/vf/dynamic/stride.hpp>
#include <sge/renderer/impl/vf/dynamic/element_converter.hpp>
#include <sge/renderer/impl/vf/dynamic/lock_interval.hpp>
#include <fcppt/assert/pre.hpp>


sge::renderer::impl::vf::dynamic::element_converter::element_converter(
	sge::image::color::format const _original_color,
	sge::image::color::format const _backend_color,
	sge::renderer::vf::dynamic::stride const _stride,
	sge::renderer::vf::dynamic::offset const _offset
)
:
	original_color_(
		_original_color
	),
	backend_color_(
		_backend_color
	),
	stride_(
		_stride
	),
	offset_(
		_offset
	)
{
	FCPPT_ASSERT_PRE(
		sge::image::color::format_stride(
			original_color_
		)
		==
		sge::image::color::format_stride(
			backend_color_
		)
	);
}

void
sge::renderer::impl::vf::dynamic::element_converter::convert(
	sge::renderer::impl::vf::dynamic::lock_interval const &_interval,
	sge::renderer::raw_pointer const _data,
	sge::renderer::vertex::first const _pos,
	bool const _unlock
)
{
	if(
		original_color_
		==
		backend_color_
	)
		return;

	// pos refers to the beginning of the lock
	FCPPT_ASSERT_PRE(
		_interval.lower()
		>= _pos.get()
	);

	sge::renderer::raw_pointer const begin(
		_data
		+
		(
			_interval.lower()
			- _pos.get()
		)
		* stride_.get()
		+ offset_.get()
	);

	sge::image2d::dim const dim(
		1u,
		_interval.upper()
		-
		_interval.lower()
	);

	sge::image2d::pitch const pitch(
		static_cast<
			sge::image2d::pitch::value_type
		>(
			stride_.get()
			-
			sge::image::color::format_stride(
				original_color_
			)
		)
	);

	sge::image2d::algorithm::copy_and_convert(
		sge::image2d::view::make_const(
			begin,
			dim,
			_unlock
			?
				original_color_
			:
				backend_color_
			,
			pitch
		),
		sge::image2d::view::make(
			begin,
			dim,
			_unlock
			?
				backend_color_
			:
				original_color_
			,
			pitch
		),
		sge::image::algorithm::may_overlap::yes,
		sge::image::algorithm::uninitialized::no
	);
}
