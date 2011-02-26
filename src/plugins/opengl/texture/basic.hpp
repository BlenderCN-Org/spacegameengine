/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENGL_TEXTURE_BASIC_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_BASIC_HPP_INCLUDED

#include "basic_fwd.hpp"
#include "base.hpp"
#include "lock_base.hpp"
#include "scoped_work_bind_fwd.hpp"
#include "type.hpp"
#include "../color_format.hpp"
#include "../color_format_type.hpp"
#include "../internal_color_format.hpp"
#include "../lock_method.hpp"
#include "../context/object_fwd.hpp"
#include <sge/renderer/texture/filter/object.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/traits/pitch.hpp>
#include <fcppt/container/bitfield/basic_decl.hpp>
#include <fcppt/math/box/basic_decl.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_decl.hpp>
#include <fcppt/scoped_ptr.hpp>

namespace sge
{
namespace opengl
{
namespace texture
{

template<
	typename Types
>
class basic
:
	public Types::base,
	public texture::base
{
	FCPPT_NONCOPYABLE(
		basic
	);
public:
	typedef typename Types::base base_type;

	typedef opengl::texture::lock_base::pointer pointer;

	typedef opengl::texture::lock_base::const_pointer const_pointer;

	typedef typename base_type::size_type size_type;

	typedef typename base_type::dim_type dim_type;

	typedef typename base_type::lock_area lock_area;

	typedef typename base_type::view_type view_type;

	typedef typename base_type::const_view_type const_view_type;

	// implementation for base class
	dim_type const
	dim() const;

	view_type const
	lock(
		lock_area const &,
		renderer::lock_mode::type
	);

	const_view_type const
	lock(
		lock_area const &
	) const;

	void
	unlock() const;
private:
	// helper functions
	void
	lock_me(
		lock_area const &,
		opengl::lock_method::type
	) const;

	view_type const
	view();

	const_view_type const
	view() const;

	dim_type const
	lock_dim() const;
protected:
	renderer::texture::filter::object const &
	filter() const;

	renderer::texture::capabilities_field const
	capabilities() const;

	using base_type::content;

	size_type
	stride() const;

	opengl::color_format const
	format() const;

	opengl::color_format_type const
	format_type() const;

	opengl::internal_color_format const
	internal_format() const;

	opengl::context::object &
	context() const;

	typedef typename Types::parameters parameters_type;

	basic(
		opengl::context::object &,
		opengl::texture::type,
		parameters_type const &
	);
public:
	~basic();

	renderer::resource_flags_field const
	flags() const;
private:
	virtual void
	set_area(
		opengl::texture::scoped_work_bind const &,
		lock_area const &,
		pointer dest
	) const = 0;

	void
	check_locked() const;

	void
	check_not_locked() const;

	opengl::context::object &context_;

	renderer::texture::filter::object const filter_;

	renderer::resource_flags_field const resource_flags_;

	renderer::texture::capabilities_field const capabilities_;

	dim_type const dim_;

	opengl::color_format const format_;

	opengl::color_format_type const format_type_;

	opengl::internal_color_format const internal_format_;

	sge::image::color::format::type const color_type_;

	size_type const stride_;

	typedef fcppt::scoped_ptr<
		opengl::texture::lock_base
	> scoped_lock_ptr;

	mutable scoped_lock_ptr lock_;

	typedef fcppt::optional<
		lock_area
	> optional_lock_area;

	mutable optional_lock_area lock_area_;

	typedef fcppt::optional<
		typename sge::image::traits::pitch<
			typename base_type::image_tag
		>::type
	> optional_pitch;
};

}
}
}

#endif
