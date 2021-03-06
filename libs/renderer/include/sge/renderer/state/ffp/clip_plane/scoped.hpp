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


#ifndef SGE_RENDERER_STATE_FFP_CLIP_PLANE_SCOPED_HPP_INCLUDED
#define SGE_RENDERER_STATE_FFP_CLIP_PLANE_SCOPED_HPP_INCLUDED

#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/ffp/clip_plane/const_object_ref_vector.hpp>
#include <sge/renderer/state/ffp/clip_plane/scoped_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{
namespace state
{
namespace ffp
{
namespace clip_plane
{

class scoped
{
	FCPPT_NONCOPYABLE(
		scoped
	);
public:
	SGE_RENDERER_DETAIL_SYMBOL
	scoped(
		sge::renderer::context::ffp &context,
		sge::renderer::state::ffp::clip_plane::const_object_ref_vector const &
	);

	SGE_RENDERER_DETAIL_SYMBOL
	~scoped();
private:
	sge::renderer::context::ffp &context_;
};

}
}
}
}
}

#endif
