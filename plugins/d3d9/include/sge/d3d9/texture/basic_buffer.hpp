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


#ifndef SGE_D3D9_TEXTURE_BASIC_BUFFER_HPP_INCLUDED
#define SGE_D3D9_TEXTURE_BASIC_BUFFER_HPP_INCLUDED

#include <sge/d3d9/texture/basic_buffer_fwd.hpp>
#include <sge/image/color/format.hpp>
#include <sge/renderer/basic_dim.hpp>
#include <sge/renderer/lock_mode_fwd.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/lock_flags/method_fwd.hpp>
#include <fcppt/com_deleter.hpp>
#include <fcppt/function_impl.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_decl.hpp>
#include <fcppt/optional/object_decl.hpp>


namespace sge
{
namespace d3d9
{
namespace texture
{

template<
	typename Types
>
class basic_buffer
:
	public Types::buffer_base
{
	FCPPT_NONCOPYABLE(
		basic_buffer
	);

	typedef
	typename
	Types::buffer_base
	base;
public:
	typedef
	typename
	Types::d3d_buffer
	d3d_buffer;

	typedef
	fcppt::unique_ptr<
		d3d_buffer,
		fcppt::com_deleter
	>
	d3d_buffer_unique_ptr;

	typedef
	fcppt::function<
		d3d_buffer_unique_ptr ()
	>
	d3d_buffer_create_function;

	basic_buffer(
		d3d_buffer_create_function const &,
		sge::image::color::format,
		sge::renderer::resource_flags_field const &
	);

	~basic_buffer()
	override;
private:
	typedef typename base::image_tag image_tag;

	typedef typename base::const_view const_view;

	typedef typename base::view view;

	typedef typename base::lock_area lock_area;

	typedef typename base::dim dim;

	const_view
	lock_c(
		lock_area const &
	) const
	override;

	view
	lock(
		lock_area const &,
		sge::renderer::lock_mode
	)
	override;

	void
	unlock() const
	override;

	dim
	size() const
	override;

	sge::image::color::format
	format() const
	override;

	template<
		typename View,
		typename MakeView
	>
	View
	lock_impl(
		MakeView const &,
		lock_area const &,
		sge::renderer::lock_flags::method
	) const;

	d3d_buffer_create_function const buffer_create_;

	sge::image::color::format const color_format_;

	sge::renderer::resource_flags_field const resource_flags_;

	dim const size_;

	typedef
	fcppt::optional::object<
		d3d_buffer_unique_ptr
	>
	optional_d3d_buffer_unique_ptr;

	mutable optional_d3d_buffer_unique_ptr buffer_;

	typedef
	typename
	Types::locked_dest
	locked_dest;

	mutable locked_dest locked_dest_;
};

}
}
}

#endif
