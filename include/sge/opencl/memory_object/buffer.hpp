/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_OPENCL_MEMORY_OBJECT_BUFFER_HPP_INCLUDED
#define SGE_OPENCL_MEMORY_OBJECT_BUFFER_HPP_INCLUDED

#include <sge/opencl/clinclude.hpp>
#include <sge/opencl/symbol.hpp>
#include <sge/opencl/context/object_fwd.hpp>
#include <sge/opencl/memory_object/base.hpp>
#include <sge/opencl/memory_object/byte_size.hpp>
#include <sge/opencl/memory_object/flags_field.hpp>
#include <sge/opencl/memory_object/renderer_buffer_lock_mode_fwd.hpp>
#include <sge/renderer/vertex/buffer_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opencl
{
namespace memory_object
{
class buffer
:
	public memory_object::base
{
FCPPT_NONCOPYABLE(
	buffer);
public:
	SGE_OPENCL_SYMBOL explicit
	buffer(
		opencl::context::object &,
		memory_object::flags_field const &,
		memory_object::byte_size const &);

	SGE_OPENCL_SYMBOL explicit
	buffer(
		opencl::context::object &,
		sge::renderer::vertex::buffer &,
		memory_object::renderer_buffer_lock_mode);

	SGE_OPENCL_SYMBOL cl_mem
	impl();

	SGE_OPENCL_SYMBOL memory_object::byte_size const
	byte_size() const;

	SGE_OPENCL_SYMBOL ~buffer();
private:
	cl_mem impl_;
	memory_object::byte_size const byte_size_;
};
}
}
}

#endif
