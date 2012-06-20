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


#ifndef SGE_OPENGL_TEXTURE_BASIC_IMPL_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_BASIC_IMPL_HPP_INCLUDED

#include <sge/image/algorithm/copy_and_convert.hpp>
#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/color/format_stride.hpp>
#include <sge/image/view/flipped.hpp>
#include <sge/image/view/make.hpp>
#include <sge/image/view/sub.hpp>
#include <sge/image/view/to_const.hpp>
#include <sge/opengl/range_check.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/convert/best_color_format.hpp>
#include <sge/opengl/convert/color_to_format.hpp>
#include <sge/opengl/convert/color_to_format_type.hpp>
#include <sge/opengl/convert/color_to_internal_format.hpp>
#include <sge/opengl/texture/basic.hpp>
#include <sge/opengl/texture/check_dim.hpp>
#include <sge/opengl/texture/create_lock.hpp>
#include <sge/opengl/texture/scoped_work_binding.hpp>
#include <sge/opengl/texture/funcs/get_image.hpp>
#include <sge/opengl/texture/mipmap/create.hpp>
#include <sge/opengl/texture/mipmap/parameters.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/lock_flags/from_mode.hpp>
#include <sge/renderer/lock_flags/method.hpp>
#include <sge/renderer/lock_flags/read.hpp>
#include <sge/renderer/lock_flags/write.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <fcppt/format.hpp>
#include <fcppt/null_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/bitfield/object_impl.hpp>
#include <fcppt/math/box/object_impl.hpp>
#include <fcppt/math/box/output.hpp>
#include <fcppt/math/dim/object_impl.hpp>
#include <fcppt/math/dim/output.hpp>


template<
	typename Types
>
typename sge::opengl::texture::basic<Types>::dim const
sge::opengl::texture::basic<Types>::size() const
{
	return dim_;
}

template<
	typename Types
>
typename sge::opengl::texture::basic<Types>::view const
sge::opengl::texture::basic<Types>::lock(
	lock_area const &_area,
	renderer::lock_mode::type const _mode
)
{
	this->lock_me(
		_area,
		renderer::lock_flags::from_mode(
			_mode
		)
	);

	return this->lock_view();
}

template<
	typename Types
>
typename sge::opengl::texture::basic<Types>::const_view const
sge::opengl::texture::basic<Types>::lock(
	lock_area const &_area
) const
{
	this->lock_me(
		_area,
		renderer::lock_flags::method::read
	);

	return this->lock_view();
}

template<
	typename Types
>
void
sge::opengl::texture::basic<Types>::unlock() const
{
	this->check_locked();

	lock_->pre_unlock();

	if(
		renderer::lock_flags::write(
			lock_->method()
		)
	)
	{
		// If this is also a read lock
		// we must copy the current view, which is
		// a slice into the whole texture retrieved,
		// to the destination buffer.
		if(
			renderer::lock_flags::read(
				lock_->method()
			)
		)
		{
			// this will only copy, not convert!
			sge::image::algorithm::copy_and_convert<
				image_tag
			>(
				this->lock_view(),
				sge::image::view::make<
					image_tag
				>(
					lock_->write_view_pointer(),
					this->lock_dim(),
					color_type_,
					basic::optional_pitch()
				),
				sge::image::algorithm::may_overlap::no
			);

			lock_->post_copy();
		}

		lock_->unlock();

		opengl::texture::scoped_work_binding const binding(
			this->system_context(),
			this->type(),
			this->id()
		);

		Types::sub_function()(
			binding,
			this->system_context(),
			this->type(),
			format_,
			format_type_,
			sge::renderer::texture::mipmap::level(
				0u
			),
			this->size(),
			lock_area_
			?
				*lock_area_
			:
				lock_area(
					lock_area::vector::null(),
					this->size()
				)
			,
			lock_->write_pointer()
		);
	}

	lock_.reset();
}

template<
	typename Types
>
void
sge::opengl::texture::basic<Types>::lock_me(
	lock_area const &_lock_area,
	renderer::lock_flags::method::type const _method
) const
{
	if(
		!opengl::range_check(
			this->size(),
			_lock_area
		)
	)
		throw renderer::exception(
			(
				fcppt::format(
					FCPPT_TEXT("ogl: lock (%1%) out of range! dim is %2%!")
				)
				% _lock_area
				% this->size()
			).str()
		);

	lock_.take(
		opengl::texture::create_lock(
			this->system_context(),
			_method,
			this->size().content(),
			_lock_area.content(),
			this->stride(),
			this->resource_flags()
		)
	);

	if(
		renderer::lock_flags::read(
			_method
		)
	)
	{
		opengl::texture::scoped_work_binding const binding(
			this->system_context(),
			this->type(),
			this->id()
		);

		opengl::texture::funcs::get_image(
			binding,
			this->type(),
			this->format(),
			this->format_type(),
			lock_->read_pointer(),
			sge::renderer::texture::mipmap::level(
				0u
			)
		);
	}

	lock_->lock();

	if(
		_lock_area == this->area()
	)
		lock_area_.reset();
	else
		lock_area_ = _lock_area;
}

template<
	typename Types
>
typename sge::opengl::texture::basic<Types>::view const
sge::opengl::texture::basic<Types>::lock_view()
{
	// If we are currently reading a texture,
	// we have mapped the whole texture and
	// have to take a sub view.
	// Also, opengl reads the image flipped,
	// so we have to flip it too.

	bool const reading(
		renderer::lock_flags::read(
			lock_->method()
		)
	);

	view const ret(
		image::view::make<
			image_tag
		>(
			reading
			?
				lock_->read_view_pointer()
			:
				lock_->write_view_pointer(),
			reading
			?
				this->size()
			:
				this->lock_dim(),
			color_type_,
			basic::optional_pitch()
		)
	);

	return
		reading && lock_area_
		?
			sge::image::view::flipped<
				image_tag
			>(
				sge::image::view::sub<
					image_tag
				>(
					ret,
					*lock_area_
				)
			)
		:
			ret;
}

template<
	typename Types
>
typename sge::opengl::texture::basic<Types>::const_view const
sge::opengl::texture::basic<Types>::lock_view() const
{
	return
		image::view::to_const<
			image_tag
		>(
			const_cast<
				opengl::texture::basic<Types> *
			>(
				this
			)->lock_view()
		);
}

template<
	typename Types
>
typename sge::opengl::texture::basic<Types>::dim const
sge::opengl::texture::basic<Types>::lock_dim() const
{
	return
		lock_area_
		?
			lock_area_->size()
		:
			this->size();
}

template<
	typename Types
>
sge::renderer::texture::mipmap::object const
sge::opengl::texture::basic<Types>::mipmap() const
{
	return mipmap_;
}

template<
	typename Types
>
sge::renderer::texture::capabilities_field const
sge::opengl::texture::basic<Types>::capabilities() const
{
	return capabilities_;
}

template<
	typename Types
>
typename sge::opengl::texture::basic<Types>::size_type
sge::opengl::texture::basic<Types>::stride() const
{
	return stride_;
}

template<
	typename Types
>
sge::opengl::color_format const
sge::opengl::texture::basic<Types>::format() const
{
	return format_;
}

template<
	typename Types
>
sge::opengl::color_format_type const
sge::opengl::texture::basic<Types>::format_type() const
{
	return format_type_;
}

template<
	typename Types
>
sge::opengl::internal_color_format const
sge::opengl::texture::basic<Types>::internal_format() const
{
	return internal_format_;
}

template<
	typename Types
>
sge::opengl::context::system::object &
sge::opengl::texture::basic<Types>::system_context() const
{
	return system_context_;
}

template<
	typename Types
>
sge::opengl::texture::basic<Types>::basic(
	sge::opengl::context::system::object &_system_context,
	opengl::texture::type const _type,
	parameters_type const &_parameters
)
:
	opengl::texture::base(
		_type
	),
	system_context_(
		_system_context
	),
	mipmap_(
		_parameters.mipmap()
	),
	resource_flags_(
		_parameters.resource_flags()
	),
	capabilities_(
		_parameters.capabilities()
	),
	dim_(
		_parameters.size()
	),
	color_type_(
		opengl::convert::best_color_format(
			_parameters.format()
		)
	),
	format_(
		opengl::convert::color_to_format(
			color_type_
		)
	),
	format_type_(
		opengl::convert::color_to_format_type(
			color_type_
		)
	),
	internal_format_(
		opengl::convert::color_to_internal_format(
			color_type_
		)
	),
	stride_(
		image::color::format_stride(
			color_type_
		)
	),
	lock_(),
	lock_area_()
{
	opengl::texture::check_dim<
		dim::dim_wrapper::value
	>(
		this->size(),
		Types::min_size(),
		Types::name()
	);

	opengl::texture::scoped_work_binding const binding(
		this->system_context(),
		this->type(),
		this->id()
	);

	Types::init_function()(
		binding,
		this->system_context(),
		this->type(),
		this->format(),
		this->format_type(),
		this->internal_format(),
		sge::renderer::texture::mipmap::level(
			0u
		),
		this->size(),
		fcppt::null_ptr()
	);

	opengl::texture::mipmap::create<
		dim::dim_wrapper::value
	>(
		opengl::texture::mipmap::parameters<
			dim::dim_wrapper::value
		>(
			binding,
			this->system_context(),
			this->type(),
			this->format(),
			this->format_type(),
			this->internal_format(),
			this->size(),
			Types::init_function()
		),
		this->mipmap()
	);
}

template<
	typename Types
>
sge::opengl::texture::basic<Types>::~basic()
{
}

template<
	typename Types
>
sge::renderer::resource_flags_field const
sge::opengl::texture::basic<Types>::resource_flags() const
{
	return resource_flags_;
}

template<
	typename Types
>
void
sge::opengl::texture::basic<Types>::check_locked() const
{
	if(
		!lock_
	)
		throw renderer::exception(
			FCPPT_TEXT("opengl::texture::basic not locked!")
		);
}

template<
	typename Types
>
void
sge::opengl::texture::basic<Types>::check_not_locked() const
{
	if(
		lock_
	)
		throw renderer::exception(
			FCPPT_TEXT("opengl::texture::basic already locked!")
		);
}

#endif
