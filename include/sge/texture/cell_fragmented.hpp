/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef FCPPT_TEXTURE_CELL_FRAGMENTED_HPP_INCLUDED
#define FCPPT_TEXTURE_CELL_FRAGMENTED_HPP_INCLUDED

#include <sge/texture/fragmented.hpp>
#include <sge/texture/part_ptr.hpp>
#include <sge/renderer/filter/texture_fwd.hpp>
#include <sge/renderer/texture_ptr.hpp>
#include <sge/renderer/dim_type.hpp>
#include <sge/renderer/device_ptr.hpp>
#include <sge/image/color/format.hpp>
#include <sge/symbol.hpp>
#include <fcppt/container/raw_vector_decl.hpp>
#include <fcppt/container/field_decl.hpp>
#include <fcppt/math/dim/basic_decl.hpp>

namespace sge
{
namespace texture
{

class cell_fragmented
:
	public fragmented
{
public:
	SGE_SYMBOL cell_fragmented(
		renderer::device_ptr rend,
		image::color::format::type,
		renderer::filter::texture const &filter,
		renderer::dim_type const &cell_size
	);

	SGE_SYMBOL ~cell_fragmented();
private:
	SGE_SYMBOL part_ptr const
	consume_fragment(
		renderer::dim_type const &
	);

	SGE_SYMBOL void
	on_return_fragment(
		part const &
	);

	SGE_SYMBOL renderer::texture_ptr const
	texture() const;

	SGE_SYMBOL bool
	repeatable() const;

	SGE_SYMBOL free_type
	free_value() const;

	SGE_SYMBOL bool
	empty() const;

	typedef fcppt::container::field<
		bool,
		fcppt::container::raw_vector
	> field_type;

	renderer::device_ptr      const rend;
	renderer::dim_type        const cell_size;
	field_type                      cells;
	renderer::texture_ptr     const tex;
};

}
}

#endif
