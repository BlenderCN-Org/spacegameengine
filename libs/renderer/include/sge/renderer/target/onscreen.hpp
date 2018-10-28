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


#ifndef SGE_RENDERER_TARGET_ONSCREEN_HPP_INCLUDED
#define SGE_RENDERER_TARGET_ONSCREEN_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/renderer/color_buffer/readable_surface_fwd.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/target/base.hpp>
#include <sge/renderer/target/onscreen_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{
namespace target
{

/**
\brief The target used to render on screen

Every device will have an onscreen target by default. It is used to render
anything on screen (instead of rendering to, for example, a texture).

\see sge::renderer::target_base
\see sge::renderer::device::onscreen_target
*/
class SGE_CORE_DETAIL_CLASS_SYMBOL onscreen
:
	public sge::renderer::target::base
{
	FCPPT_NONCOPYABLE(
		onscreen
	);
protected:
	SGE_RENDERER_DETAIL_SYMBOL
	onscreen();
public:
	/**
	\brief Returns the associated color surface
	*/
	virtual
	sge::renderer::color_buffer::readable_surface const &
	surface() const = 0;

	SGE_RENDERER_DETAIL_SYMBOL
	~onscreen()
	override;
};

}
}
}

#endif
