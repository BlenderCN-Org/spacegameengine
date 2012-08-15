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


#ifndef SGE_OPENGL_TEXTURE_INIT_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_INIT_HPP_INCLUDED

#include <sge/image/color/format.hpp>
#include <sge/opengl/color_format.hpp>
#include <sge/opengl/color_format_type.hpp>
#include <sge/opengl/internal_color_format.hpp>
#include <sge/opengl/convert/color_to_format.hpp>
#include <sge/opengl/convert/color_to_format_type.hpp>
#include <sge/opengl/convert/color_to_internal_format.hpp>
#include <sge/opengl/texture/basic_buffer.hpp>
#include <sge/opengl/texture/basic_buffer_parameters.hpp>
#include <sge/opengl/texture/basic_parameters.hpp>
#include <sge/opengl/texture/best_color_format.hpp>
#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/opengl/texture/buffer_type.hpp>
#include <sge/opengl/texture/check_dim.hpp>
#include <sge/opengl/texture/extend_size.hpp>
#include <sge/opengl/texture/id.hpp>
#include <sge/opengl/texture/is_render_target.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/opengl/texture/mipmap/create.hpp>
#include <sge/opengl/texture/mipmap/get_levels.hpp>
#include <sge/opengl/texture/mipmap/parameters.hpp>
#include <sge/renderer/basic_dim.hpp>
#include <sge/renderer/texture/capabilities.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <sge/renderer/texture/mipmap/level_count.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/null_ptr.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

template<
	typename Types
>
void
init(
	sge::opengl::texture::binding const &_binding,
	boost::ptr_vector<
		typename Types::buffer_base
	> &_levels,
	sge::opengl::texture::basic_parameters const &_basic_parameters,
	typename Types::parameters const &_parameters,
	sge::opengl::texture::type const _type,
	sge::opengl::texture::buffer_type const _buffer_type,
	sge::opengl::texture::id const _id
)
{
	typedef typename sge::renderer::basic_dim<
		Types::num_dims
	>::type extended_dim;

	typedef typename extended_dim::dim_wrapper dim_wrapper;

	extended_dim const size(
		sge::opengl::texture::extend_size(
			_parameters.size()
		)
	);

	sge::opengl::texture::check_dim<
		dim_wrapper::value
	>(
		size,
		Types::min_size(),
		Types::name()
	);

	sge::image::color::format::type const format(
		sge::opengl::texture::best_color_format(
			_parameters.format()
		)
	);

	sge::opengl::color_format const color_format(
		sge::opengl::convert::color_to_format(
			format
		)
	);

	sge::opengl::color_format_type const color_format_type(
		sge::opengl::convert::color_to_format_type(
			format
		)
	);

	sge::opengl::internal_color_format const internal_color_format(
		sge::opengl::convert::color_to_internal_format(
			format
		)
	);

	Types::init_function()(
		_binding,
		_basic_parameters.system_context(),
		_buffer_type,
		color_format,
		color_format_type,
		internal_color_format,
		sge::renderer::texture::mipmap::level(
			0u
		),
		size,
		fcppt::null_ptr()
	);

	sge::opengl::texture::mipmap::create<
		dim_wrapper::value
	>(
		sge::opengl::texture::mipmap::parameters<
			dim_wrapper::value
		>(
			_binding,
			_basic_parameters.system_context(),
			_type,
			_buffer_type,
			color_format,
			color_format_type,
			internal_color_format,
			size,
			Types::init_function()
		),
		_parameters.mipmap()
	);

	sge::renderer::texture::mipmap::level_count const mip_levels(
		sge::opengl::texture::mipmap::get_levels<
			dim_wrapper::value
		>(
			_parameters.mipmap(),
			size
		)
	);

	sge::opengl::texture::is_render_target const is_target(
		_parameters.capabilities()
		&
		sge::renderer::texture::capabilities::render_target
	);

	typedef sge::opengl::texture::basic_buffer<
		Types
	> gl_buffer;

	for(
		sge::renderer::texture::mipmap::level index(
			0u
		);
		index.get() < mip_levels.get();
		++index
	)
		fcppt::container::ptr::push_back_unique_ptr(
			_levels,
			fcppt::make_unique_ptr<
				gl_buffer
			>(
				sge::opengl::texture::basic_buffer_parameters(
					_binding,
					_basic_parameters.system_context(),
					_basic_parameters.device_context(),
					index,
					_type,
					_buffer_type,
					_id,
					_parameters.resource_flags(),
					format,
					color_format,
					color_format_type,
					internal_color_format,
					is_target
				)
			)
		);
}

}
}
}

#endif