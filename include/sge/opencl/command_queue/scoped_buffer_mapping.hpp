/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_OPENCL_COMMAND_QUEUE_SCOPED_BUFFER_MAPPING_HPP_INCLUDED
#define SGE_OPENCL_COMMAND_QUEUE_SCOPED_BUFFER_MAPPING_HPP_INCLUDED

#include <sge/opencl/clinclude.hpp>
#include <sge/opencl/detail/symbol.hpp>
#include <sge/opencl/command_queue/map_flags_fwd.hpp>
#include <sge/opencl/command_queue/object_fwd.hpp>
#include <sge/opencl/event/sequence.hpp>
#include <sge/opencl/memory_object/buffer_fwd.hpp>
#include <sge/opencl/memory_object/byte_offset.hpp>
#include <sge/opencl/memory_object/byte_size.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opencl
{
namespace command_queue
{
class scoped_buffer_mapping
{
FCPPT_NONCOPYABLE(
	scoped_buffer_mapping);
public:
	SGE_OPENCL_DETAIL_SYMBOL
	scoped_buffer_mapping(
		sge::opencl::command_queue::object &,
		sge::opencl::memory_object::buffer &,
		sge::opencl::command_queue::map_flags,
		sge::opencl::memory_object::byte_offset const &,
		sge::opencl::memory_object::byte_size const &,
		sge::opencl::event::sequence const &);

	SGE_OPENCL_DETAIL_SYMBOL void*
	ptr() const;

	SGE_OPENCL_DETAIL_SYMBOL ~scoped_buffer_mapping();
private:
	sge::opencl::command_queue::object &queue_;
	cl_mem buffer_;
	void *ptr_;
};
}
}
}

#endif
