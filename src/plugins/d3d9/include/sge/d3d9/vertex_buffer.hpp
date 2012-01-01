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


#ifndef SGE_D3D9_VERTEX_BUFFER_HPP_INCLUDED
#define SGE_D3D9_VERTEX_BUFFER_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/resource.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/raw_pointer.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/lock_flags/method.hpp>
#include <sge/renderer/vf/dynamic/converter.hpp>
#include <sge/renderer/vf/dynamic/part.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <fcppt/com_deleter.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr_impl.hpp>
#include <fcppt/container/bitfield/basic_decl.hpp>


namespace sge
{
namespace d3d9
{

class vertex_buffer
:
	public sge::renderer::vertex_buffer,
	public d3d9::resource
{
	FCPPT_NONCOPYABLE(
		vertex_buffer
	);
public:
	vertex_buffer(
		IDirect3DDevice9 *,
		renderer::vf::dynamic::part const &,
		renderer::vf::dynamic::part_index,
		count_type,
		renderer::resource_flags_field const &
	);

	~vertex_buffer();

	view_type const
	lock(
		renderer::lock_mode::type,
		first_type,
		count_type
	);

	const_view_type const
	lock(
		first_type,
		count_type
	) const;

	void
	unlock() const;

	count_type const
	size() const;

	renderer::resource_flags_field const
	resource_flags() const;

	renderer::vf::dynamic::part const
	format_part() const;

	renderer::vf::dynamic::part_index const
	format_part_index() const;

	IDirect3DVertexBuffer9 *
	get() const;
private:
	void
	init();

	void
	on_loss();

	void
	on_reset();

	template<
		typename View
	>
	View const
	do_lock(
		first_type,
		count_type,
		renderer::lock_flags::method::type
	) const;

	size_type
	stride() const;

	IDirect3DDevice9 *const device_;

	renderer::vf::dynamic::part const format_part_;

	renderer::vf::dynamic::part_index const format_part_index_;

	count_type const size_;

	renderer::resource_flags_field const resource_flags_;

	mutable renderer::vf::dynamic::converter converter_;

	typedef fcppt::scoped_ptr<
		IDirect3DVertexBuffer9,
		fcppt::com_deleter
	> d3d_scoped_vertex_buffer_ptr;

	d3d_scoped_vertex_buffer_ptr buffer_;

	mutable renderer::raw_pointer lock_dest_;
};

}
}

#endif
