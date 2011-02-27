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


#ifndef SGE_D3D9_INDEX_BUFFER_HPP_INCLUDED
#define SGE_D3D9_INDEX_BUFFER_HPP_INCLUDED

#include "d3d_device_ptr.hpp"
#include "d3d_index_buffer_ptr.hpp"
#include "d3dinclude.hpp"
#include "lock_flags.hpp"
#include "resource.hpp"
#include <sge/renderer/index_buffer.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/raw_pointer.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/index/dynamic/format.hpp>
#include <fcppt/container/bitfield/basic_decl.hpp>

namespace sge
{
namespace d3d9
{

class index_buffer
:
	public sge::renderer::index_buffer,
	public resource
{
	FCPPT_NONCOPYABLE(
		index_buffer
	);
public:
	index_buffer(
		d3d9::d3d_device_ptr,
		renderer::index::dynamic::format::type,
		size_type size,
		renderer::resource_flags_field const &
	);

	~index_buffer();

	view_type const
	lock(
		renderer::lock_mode::type,
		size_type offset,
		size_type range
	);

	const_view_type const
	lock(
		size_type offse,
		size_type range
	) const;

	void
	unlock() const;

	size_type
	size() const;

	renderer::resource_flags_field const
	resource_flags() const;

	renderer::index::dynamic::format::type
	format() const;
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
		size_type first,
		size_type count,
		d3d9::lock_flags
	) const;

	d3d9::d3d_device_ptr const device_;

	d3d9::d3d_index_buffer_ptr buffer_;

	renderer::resource_flags_field const resource_flags_;

	renderer::index::dynamic::format::type const format_;

	size_type const
		size_,
		stride_;

	mutable renderer::raw_pointer lock_dest_;
};

}
}

#endif
