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


#ifndef SGE_OPENGL_TEXTURE_BASIC_LOCKABLE_BUFFER_IMPL_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_BASIC_LOCKABLE_BUFFER_IMPL_HPP_INCLUDED

#include <sge/image/algorithm/copy.hpp>
#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image/traits/format_stride.hpp>
#include <sge/image/view/flipped.hpp>
#include <sge/image/view/make.hpp>
#include <sge/image/view/sub.hpp>
#include <sge/image/view/to_const.hpp>
#include <sge/opengl/range_check.hpp>
#include <sge/opengl/set_unpack_alignment.hpp>
#include <sge/opengl/stride_to_unpack_alignment.hpp>
#include <sge/opengl/texture/basic_buffer_parameters.hpp>
#include <sge/opengl/texture/basic_lockable_buffer.hpp>
#include <sge/opengl/texture/create_lock.hpp>
#include <sge/opengl/texture/is_render_target.hpp>
#include <sge/opengl/texture/scoped_work_binding.hpp>
#include <sge/opengl/texture/funcs/get_image.hpp>
#include <sge/opengl/texture/mipmap/create.hpp>
#include <sge/opengl/texture/mipmap/parameters.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/lock_flags/from_mode.hpp>
#include <sge/renderer/lock_flags/method.hpp>
#include <sge/renderer/lock_flags/read.hpp>
#include <sge/renderer/lock_flags/write.hpp>
#include <fcppt/const.hpp>
#include <fcppt/format.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/math/box/object_impl.hpp>
#include <fcppt/math/box/output.hpp>
#include <fcppt/math/dim/comparison.hpp>
#include <fcppt/math/dim/contents.hpp>
#include <fcppt/math/dim/null.hpp>
#include <fcppt/math/dim/object_impl.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/optional/assign.hpp>
#include <fcppt/optional/from.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/object_impl.hpp>


template<
	typename Types
>
sge::opengl::texture::basic_lockable_buffer<
	Types
>::basic_lockable_buffer(
	format_type const _format,
	sge::opengl::texture::basic_buffer_parameters const &_parameters
)
:
	gl_base(
		_format,
		_parameters
	),
	log_{
		_parameters.log()
	},
	context_(
		_parameters.context()
	),
	type_(
		_parameters.type()
	),
	resource_flags_(
		_parameters.resource_flags()
	),
	color_format_(
		_parameters.color_format()
	),
	color_format_type_(
		_parameters.color_format_type()
	),
	internal_color_format_(
		_parameters.internal_color_format()
	),
	stride_(
		sge::image::traits::format_stride<
			color_tag
		>::execute(
			this->format()
		)
	),
	lock_(),
	lock_area_()
{
}

template<
	typename Types
>
sge::opengl::texture::basic_lockable_buffer<
	Types
>::~basic_lockable_buffer()
{
}

template<
	typename Types
>
typename
sge::opengl::texture::basic_lockable_buffer<
	Types
>::view
sge::opengl::texture::basic_lockable_buffer<
	Types
>::lock(
	lock_area const &_area,
	sge::renderer::lock_mode const _mode
)
{
	this->lock_me(
		_area,
		sge::renderer::lock_flags::from_mode(
			_mode
		)
	);

	return
		this->lock_view();
}

template<
	typename Types
>
typename
sge::opengl::texture::basic_lockable_buffer<
	Types
>::const_view
sge::opengl::texture::basic_lockable_buffer<
	Types
>::lock_c(
	lock_area const &_area
) const
{
	this->lock_me(
		_area,
		sge::renderer::lock_flags::method::read
	);

	return
		this->lock_view();
}

template<
	typename Types
>
void
sge::opengl::texture::basic_lockable_buffer<
	Types
>::unlock() const
{
	lock_unique_ptr const &cur_lock(
		FCPPT_ASSERT_OPTIONAL_ERROR(
			lock_
		)
	);

	cur_lock->pre_unlock();

	if(
		sge::renderer::lock_flags::write(
			cur_lock->method()
		)
	)
	{
		// If this is also a read lock
		// we must copy the current view, which is
		// a slice into the whole texture retrieved,
		// to the destination buffer.
		if(
			sge::renderer::lock_flags::read(
				cur_lock->method()
			)
		)
		{
			// this will only copy, not convert!
			sge::image::algorithm::copy<
				image_tag
			>(
				this->lock_view(),
				sge::image::view::make<
					image_tag
				>(
					cur_lock->write_view_pointer(),
					this->lock_dim(),
					this->format(),
					fcppt::math::dim::null<
						pitch
					>()
				),
				sge::image::algorithm::may_overlap::no,
				sge::image::algorithm::uninitialized::yes
			);

			cur_lock->post_copy();
		}

		cur_lock->unlock();

		sge::opengl::texture::scoped_work_binding const binding(
			log_,
			context_,
			type_,
			this->id()
		);

		sge::opengl::set_unpack_alignment(
			context_,
			sge::opengl::stride_to_unpack_alignment(
				stride_
			)
		);

		Types::dim_types::sub_function()(
			binding,
			context_,
			this->buffer_type(),
			color_format_,
			color_format_type_,
			this->level(),
			this->size(),
			fcppt::optional::from(
				lock_area_,
				[
					this
				]{
					return
						lock_area(
							fcppt::math::vector::null<
								typename
								lock_area::vector
							>(),
							this->size()
						);
				}
			),
			cur_lock->write_pointer()
		);
	}

	lock_ =
		optional_lock_unique_ptr();
}

template<
	typename Types
>
void
sge::opengl::texture::basic_lockable_buffer<
	Types
>::lock_me(
	lock_area const &_lock_area,
	sge::renderer::lock_flags::method const _method
) const
{
	if(
		!sge::opengl::range_check(
			this->size(),
			_lock_area
		)
	)
		throw sge::renderer::exception(
			(
				fcppt::format(
					FCPPT_TEXT("ogl: lock (%1%) out of range! dim is %2%!")
				)
				% _lock_area
				% this->size()
			).str()
		);

	lock_unique_ptr const &cur_lock(
		fcppt::optional::assign(
			lock_,
			sge::opengl::texture::create_lock(
				context_,
				_method,
				fcppt::math::dim::contents(
					this->size()
				),
				fcppt::math::dim::contents(
					_lock_area.size()
				),
				stride_,
				resource_flags_
			)
		)
	);

	if(
		sge::renderer::lock_flags::read(
			_method
		)
	)
	{
		sge::opengl::texture::scoped_work_binding const binding(
			log_,
			context_,
			type_,
			this->id()
		);

		sge::opengl::texture::funcs::get_image(
			binding,
			this->buffer_type(),
			color_format_,
			color_format_type_,
			cur_lock->read_pointer(),
			this->level()
		);
	}

	cur_lock->lock();

	lock_area_ =
		// TODO: Change this
		_lock_area.size()
		==
		this->size()
		?
			optional_lock_area()
		:
			optional_lock_area(
				_lock_area
			)
		;
}

template<
	typename Types
>
typename
sge::opengl::texture::basic_lockable_buffer<
	Types
>::view
sge::opengl::texture::basic_lockable_buffer<
	Types
>::lock_view()
{
	lock_unique_ptr const &cur_lock(
		FCPPT_ASSERT_OPTIONAL_ERROR(
			lock_
		)
	);

	// If we are currently reading a texture, we have mapped the whole
	// texture and have to take a sub view. Also, opengl reads the image
	// flipped, so we have to flip it too.

	bool const reading(
		sge::renderer::lock_flags::read(
			cur_lock->method()
		)
	);

	view const ret(
		sge::image::view::make<
			image_tag
		>(
			reading
			?
				cur_lock->read_view_pointer()
			:
				cur_lock->write_view_pointer(),
			reading
			?
				this->size()
			:
				this->lock_dim(),
			this->format(),
			fcppt::math::dim::null<
				pitch
			>()
		)
	);

	return
		reading
		?
			fcppt::optional::maybe(
				lock_area_,
				fcppt::const_(
					ret
				),
				[
					&ret
				](
					lock_area const &_area
				)
				{
					return
						sge::image::view::flipped<
							image_tag
						>(
							sge::image::view::sub<
								image_tag
							>(
								ret,
								_area
							)
						);
				}
			)
		:
			ret
		;
}

template<
	typename Types
>
typename sge::opengl::texture::basic_lockable_buffer<
	Types
>::const_view
sge::opengl::texture::basic_lockable_buffer<
	Types
>::lock_view() const
{
	return
		sge::image::view::to_const<
			image_tag
		>(
			const_cast<
				sge::opengl::texture::basic_lockable_buffer<
					Types
				> *
			>(
				this
			)->lock_view()
		);
}

template<
	typename Types
>
typename sge::opengl::texture::basic_lockable_buffer<
	Types
>::dim
sge::opengl::texture::basic_lockable_buffer<
	Types
>::lock_dim() const
{
	return
		fcppt::optional::maybe(
			lock_area_,
			[
				this
			]{
				return
					this->size();
			},
			[](
				lock_area const &_area
			)
			{
				return
					_area.size();
			}
		);
}

#endif
