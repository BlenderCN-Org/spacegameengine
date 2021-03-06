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


#ifndef SGE_RENDERER_VF_DYNAMIC_LOCKED_PART_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_LOCKED_PART_HPP_INCLUDED

#include <sge/renderer/lock_segment.hpp>
#include <sge/renderer/raw_pointer.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/lock_flags/method.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <sge/renderer/vf/dynamic/locked_part_fwd.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{
namespace dynamic
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

class locked_part
{
public:
	SGE_RENDERER_DETAIL_SYMBOL
	locked_part(
		sge::renderer::raw_pointer,
		sge::renderer::lock_segment const &,
		sge::renderer::lock_flags::method
	);

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::raw_pointer
	data() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::vertex::first
	pos() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::vertex::count
	count() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::lock_flags::method
	lock_flags() const;
private:
	sge::renderer::raw_pointer data_;

	sge::renderer::lock_segment segment_;

	sge::renderer::lock_flags::method lock_flags_;
};

FCPPT_PP_POP_WARNING

}
}
}
}

#endif
