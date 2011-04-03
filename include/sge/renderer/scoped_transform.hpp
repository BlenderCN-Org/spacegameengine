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


#ifndef SGE_RENDERER_SCOPED_TRANSFORM_HPP_INCLUDED
#define SGE_RENDERER_SCOPED_TRANSFORM_HPP_INCLUDED

#include <sge/renderer/device_ptr.hpp>
#include <sge/renderer/matrix_mode.hpp>
#include <sge/renderer/matrix4.hpp>
#include <sge/symbol.hpp>
#include <fcppt/math/matrix/basic_impl.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace renderer
{

class scoped_transform
{
	FCPPT_NONCOPYABLE(
		scoped_transform
	);
public:
	SGE_SYMBOL
	scoped_transform(
		renderer::device_ptr,
		renderer::matrix_mode::type,
		renderer::matrix4 const &
	);

	SGE_SYMBOL
	~scoped_transform();
private:
	renderer::device_ptr const device_;

	renderer::matrix_mode::type const mode_;

	renderer::matrix4 const old_matrix_;
};

}
}

#endif