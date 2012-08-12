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


#include <sge/graph/baseline.hpp>
#include <sge/graph/object.hpp>
#include <sge/graph/position.hpp>
#include <sge/graph/scalar.hpp>
#include <sge/image/colors.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/image/size_type.hpp>
#include <sge/graph/axis_constraint.hpp>
#include <sge/graph/color_scheme.hpp>
#include <sge/graph/optional_axis_constraint.hpp>
#include <sge/image2d/vector.hpp>
#include <sge/image2d/algorithm/bresenham.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/vector2.hpp>
#include <sge/renderer/context/object.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/planar_parameters.hpp>
#include <sge/renderer/texture/planar_scoped_ptr.hpp>
#include <sge/renderer/texture/scoped_planar_lock.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/process/one.hpp>
#include <sge/texture/part_raw_ref.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/math/clamp.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/circular_buffer.hpp>
#include <boost/algorithm/minmax_element.hpp>
#include <algorithm>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace
{
sge::graph::scalar
normalize(
	sge::graph::scalar const &t,
	sge::graph::scalar const &min,
	sge::graph::scalar const &max
)
{
	if (min >= max)
		return 0.;
	return
		(t - min) /
		(max - min);
}

void
draw_rectangle(
	sge::image2d::view::object const &_view,
	sge::image2d::vector const &_corner1,
	sge::image2d::vector const &_corner2,
	sge::image::color::any::object const &_color
)
{
sge::image2d::algorithm::bresenham(
	_view,
	_corner1,
	sge::image2d::vector(_corner1.x(), _corner2.y()),
	_color,
	_color
);
sge::image2d::algorithm::bresenham(
	_view,
	_corner1,
	sge::image2d::vector(_corner2.x(), _corner1.y()),
	_color,
	_color
);
sge::image2d::algorithm::bresenham(
	_view,
	sge::image2d::vector(_corner1.x(), _corner2.y()),
	_corner2,
	_color,
	_color
);
sge::image2d::algorithm::bresenham(
	_view,
	sge::image2d::vector(_corner2.x(), _corner1.y()),
	_corner2,
	_color,
	_color
);
}

sge::image2d::vector::value_type
fit_into_scale(
	sge::graph::scalar _value,
	sge::graph::scalar _min,
	sge::graph::scalar _max,
	sge::renderer::dim2::value_type _height
)
{
	typedef
	sge::image2d::vector::value_type
	value_type;

	return
	static_cast<
		value_type
	>(
		fcppt::math::clamp(
			static_cast<
				sge::graph::scalar
			>
			(
				_height - 1
			) *
			(
				1.0 -
				normalize(
					_value,
					_min,
					_max
				)
			),
			0.0,
			static_cast<
				sge::graph::scalar
			>
			(
				_height - 1
			)
		)
	);

}

}

sge::graph::object::object(
	sge::graph::position const &_position,
	sge::renderer::dim2 const &_dim,
	sge::renderer::device &_renderer,
	sge::graph::baseline _baseline,
	sge::graph::optional_axis_constraint const &_axis_constraint,
	sge::graph::color_scheme const &_color_scheme
)
:
dim_(
	_dim),
texture_(
	_renderer.create_planar_texture(
		sge::renderer::texture::planar_parameters(
			_dim,
			sge::image::color::format::rgba8,
			sge::renderer::texture::mipmap::off(),
			sge::renderer::resource_flags_field::null(),
			sge::renderer::texture::capabilities_field(
				sge::renderer::texture::capabilities_field::null()
			)
		)
	)
),
sprite_object_(
	sprite_parameters()
	.pos(
		fcppt::math::vector::structure_cast<
			sprite_object::vector>(
				_position.get()))
	.texture(
		fcppt::make_shared_ptr<
			sge::texture::part_raw_ref
		>(
			fcppt::ref(
				*texture_
			)
		)
	)
	.texture_size()
),
sprite_buffers_(
	_renderer,
	sge::sprite::buffers::option::dynamic
),
data_buffer_(
	dim_.w()),
baseline_(
	_baseline.get()),
color_scheme_(
	_color_scheme),
axis_constraint_(
	_axis_constraint),
current_min_(
	std::min(
		0.,
		baseline_)
	),
current_max_(
	1. +
	std::max(
		current_min_,
		baseline_)
	)
{
	sge::renderer::texture::scoped_planar_lock lock(
		*texture_,
		sge::renderer::lock_mode::writeonly);

	clear(
		lock.value());
}

void
sge::graph::object::push(
	sge::graph::scalar _datum)
{
	data_buffer_.push_back(
		_datum);

	typedef
	buffer_type::iterator
	iterator_type;

	std::pair<iterator_type, iterator_type>
	minmax(
		boost::minmax_element(
			data_buffer_.begin(),
			data_buffer_.end()
	));

	current_min_ = *(minmax.first);
	current_max_ = *(minmax.second);

	if (current_max_ <= current_min_)
		current_max_ += 1.0;
}

void
sge::graph::object::render(
	sge::renderer::context::object &_context)
{
	{
		sge::renderer::texture::scoped_planar_lock const lock(
			*texture_,
			sge::renderer::lock_mode::writeonly);

		this->draw_data(lock.value());
	}

	sge::sprite::process::one(
		_context,
		sprite_object_,
		sprite_buffers_
	);
}

void
sge::graph::object::clear(
	sge::image2d::view::object const _view
)
{
	for (sge::image::size_type x = 0; x < dim_.w(); ++x)
	{
		sge::image2d::algorithm::bresenham(
			_view,
			sge::image2d::vector(
				x,
				0
			),
			sge::image2d::vector(
				x,
				dim_.h() - 1
			),
			color_scheme_.background_color(),
			color_scheme_.background_alt_color()
		);
	}

	draw_rectangle(
		_view,
		sge::image2d::vector(
			0,
			0
		),
		sge::image2d::vector(
			dim_.w() - 1,
			dim_.h() - 1
		),
		color_scheme_.foreground_alt_color()
	);
}

void
sge::graph::object::draw_data(
	sge::image2d::view::object const _view
)
{
	clear(
		_view);

	sge::graph::axis_constraint const current_axis_constraint(
		axis_constraint_
		?
			axis_constraint_->min()
		:
			current_min_,
		axis_constraint_
		?
			axis_constraint_->max()
		:
			current_max_);

	typedef
	sge::image2d::vector::value_type
	value_type;

	value_type const
	baseline = fit_into_scale(
		baseline_,
		current_axis_constraint.min(),
		current_axis_constraint.max(),
		dim_.h());

	value_type const
	zero = fit_into_scale(
		0.0,
		current_axis_constraint.min(),
		current_axis_constraint.max(),
		dim_.h());

	for (value_type i = 0; i < data_buffer_.size(); ++i)
	{
		value_type const
		value = fit_into_scale(
			fcppt::math::clamp(
				data_buffer_[i],
				current_axis_constraint.min(),
				current_axis_constraint.max()),
			current_axis_constraint.min(),
			current_axis_constraint.max(),
			dim_.h());

		bool const above =
			data_buffer_[i] > 0.0;

		sge::image::color::any::object const &col1(
				above ?
				color_scheme_.foreground_color()
				:
				color_scheme_.foreground_alt_color());

		sge::image::color::any::object const &col2(
				above ?
				color_scheme_.foreground_alt_color()
				:
				color_scheme_.foreground_color());

		sge::image2d::algorithm::bresenham(
			_view,
			sge::image2d::vector(
				i,
				zero
			),
			sge::image2d::vector(
				i,
				dim_.h() - 1 - value
			),
			col1,
			col2
		);
	}

	// zero line
	sge::image2d::algorithm::bresenham(
		_view,
		sge::image2d::vector(
			0,
			zero
		),
		sge::image2d::vector(
			dim_.w() - 1,
			zero
		),
		color_scheme_.foreground_color(),
		color_scheme_.foreground_color()
	);

	// baseline
	sge::image2d::algorithm::bresenham(
		_view,
		sge::image2d::vector(
			0,
			baseline
		),
		sge::image2d::vector(
			dim_.w() - 1,
			baseline
		),
		color_scheme_.baseline_color(),
		color_scheme_.baseline_color()
	);

}

sge::graph::object::~object()
{
}
