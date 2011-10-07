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


#ifndef SGE_OPENCL_MEMORY_OBJECT_IMAGE_PLANAR_HPP_INCLUDED
#define SGE_OPENCL_MEMORY_OBJECT_IMAGE_PLANAR_HPP_INCLUDED

#include <sge/opencl/context/object_fwd.hpp>
#include <sge/opencl/symbol.hpp>
#include <sge/class_symbol.hpp>
#include <sge/opencl/memory_object/dim2.hpp>
#include <sge/opencl/memory_object/base.hpp>
#include <sge/opencl/memory_object/image/planar_pitch.hpp>
#include <sge/renderer/texture/planar_fwd.hpp>
#include <sge/opencl/memory_object/flags_field.hpp>
#include <sge/opencl/clinclude.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/math/dim/basic_impl.hpp>

namespace sge
{
namespace opencl
{
namespace memory_object
{
namespace image
{
class SGE_CLASS_SYMBOL planar
:
	public memory_object::base
{
FCPPT_NONCOPYABLE(
	planar);
public:
	SGE_OPENCL_SYMBOL explicit
	planar(
		context::object &,
		memory_object::flags_field const &,
		cl_image_format const &,
		memory_object::dim2 const &size,
		image::planar_pitch const &);

	SGE_OPENCL_SYMBOL explicit
	planar(
		context::object &,
		memory_object::flags_field const &,
		renderer::texture::planar &);

	SGE_OPENCL_SYMBOL cl_mem
	impl();

	SGE_OPENCL_SYMBOL cl_image_format const &
	image_format() const;

	SGE_OPENCL_SYMBOL memory_object::dim2 const &
	size() const;

	SGE_OPENCL_SYMBOL ~planar();
private:
	cl_mem impl_;
	cl_image_format image_format_;
	memory_object::dim2 size_;
};
}
}
}
}

#endif
