/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/renderer/device.hpp>
#include <sge/renderer/copy_and_convert_pixels.hpp>
#include <sge/renderer/image_view_format.hpp>
#include <sge/renderer/image_view_dim.hpp>
#include <sge/renderer/image_view_impl.hpp>
#include <sge/renderer/index_view_operations.hpp>
#include <sge/renderer/scoped_texture_lock.hpp>
#include <sge/renderer/scoped_index_lock.hpp>
#include <sge/renderer/scoped_vertex_lock.hpp>
#include <sge/renderer/texture.hpp>
#include <sge/renderer/index_buffer.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/vf/dynamic_format.hpp>
#include <sge/algorithm/copy_n.hpp>
#include <boost/variant/apply_visitor.hpp>

sge::renderer::texture_ptr const sge::renderer::device::no_texture;
sge::renderer::texture_ptr const sge::renderer::device::default_render_target;
sge::renderer::glsl::program_ptr const sge::renderer::device::no_program;


sge::renderer::texture_ptr const
sge::renderer::device::create_texture(
	const_image_view const &v,
	filter_args const &filter,
	resource_flag_t const flags)
{
	texture_ptr const tex(
		create_texture(
			dim_type(
				image_view_dim(v)),
			image_view_format(v),
			filter,
			flags));
	
	scoped_texture_lock const lock(
		make_scoped_lock(
			tex,
			lock_flags::writeonly));

	copy_and_convert_pixels(
		v,
		lock.value());

	return tex;
}

sge::renderer::vertex_buffer_ptr const
sge::renderer::device::create_vertex_buffer(
	vf::const_dynamic_view const &view,
	resource_flag_t const flags)
{
	vertex_buffer_ptr const vb(
		create_vertex_buffer(
			view.format(),
			view.size(),
			flags));
	
	scoped_vertex_lock const lock(
		make_scoped_lock(
			vb,
			lock_flags::writeonly));
	
	copy_n(
		view.data(),
		view.format().stride() * view.size(),
		lock.value().data());

	return vb;
}

sge::renderer::index_buffer_ptr const
sge::renderer::device::create_index_buffer(
	const_dynamic_index_view const &view,
	resource_flag_t const flags)
{
	size_type const sz(
		boost::apply_visitor(
			index_view_size(),
			view));

	index_buffer_ptr const ib(
		create_index_buffer(
			boost::apply_visitor(
				index_view_format(),
				view),
			sz,
			flags));
	
	scoped_index_lock const lock(
		make_scoped_lock(
			ib,
			lock_flags::writeonly));
	
	copy_n(
		boost::apply_visitor(
			index_view_data_const(),
			view),
		sz * boost::apply_visitor(
			index_view_stride(),
			view),
		boost::apply_visitor(
			index_view_data(),
			lock.value()));
	
	return ib;
}

sge::space_unit
sge::renderer::device::aspect() const
{
	return static_cast<space_unit>(screen_size().w())
	     / static_cast<space_unit>(screen_size().h());
}

sge::renderer::device::~device()
{}
