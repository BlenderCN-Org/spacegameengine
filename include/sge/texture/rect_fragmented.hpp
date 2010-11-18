/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_TEXTURE_RECT_FRAGMENTED_HPP_INCLUDED
#define SGE_TEXTURE_RECT_FRAGMENTED_HPP_INCLUDED

#include <sge/texture/fragmented.hpp>
#include <sge/texture/part_fwd.hpp>
#include <sge/texture/part_ptr.hpp>
#include <sge/texture/symbol.hpp>
#include <sge/renderer/filter/texture_fwd.hpp>
#include <sge/renderer/device_ptr.hpp>
#include <sge/renderer/texture_ptr.hpp>
#include <sge/renderer/dim_type.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/image/color/format.hpp>
#include <sge/class_symbol.hpp>

namespace sge
{
namespace texture
{

class SGE_CLASS_SYMBOL rect_fragmented
:
	public fragmented
{
public:
	SGE_TEXTURE_SYMBOL rect_fragmented(
		renderer::device_ptr,
		image::color::format::type,
		renderer::filter::texture const &,
		renderer::dim_type const &initial_size
	);
private:
	SGE_TEXTURE_SYMBOL part_ptr const
	consume_fragment(
		renderer::dim_type const &
	);

	SGE_TEXTURE_SYMBOL void
	on_return_fragment(
		part const &
	);

	SGE_TEXTURE_SYMBOL renderer::texture_ptr const
	texture() const;

	SGE_TEXTURE_SYMBOL bool repeatable() const;

	SGE_TEXTURE_SYMBOL free_type
	free_value() const;

	SGE_TEXTURE_SYMBOL bool
	empty() const;

	renderer::device_ptr const rend_;

	renderer::size_type
		cur_x_,
		cur_y_,
		cur_height_;

	renderer::texture_ptr const tex_;

	renderer::size_type texture_count_;
};

}
}

#endif
