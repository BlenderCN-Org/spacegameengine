/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RENDERER_TEXTURE_DEPTH_STENCIL_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_DEPTH_STENCIL_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/renderer/depth_stencil_surface_unique_ptr.hpp>
#include <sge/renderer/dim2_fwd.hpp>
#include <sge/renderer/symbol.hpp>
#include <sge/renderer/texture/base.hpp>
#include <sge/renderer/texture/depth_stencil_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{
namespace texture
{

class SGE_CLASS_SYMBOL depth_stencil
:
	public renderer::texture::base
{
	FCPPT_NONCOPYABLE(
		depth_stencil
	);
protected:
	SGE_RENDERER_SYMBOL
	depth_stencil();
public:
	SGE_RENDERER_SYMBOL
	virtual ~depth_stencil() = 0;

	typedef sge::renderer::dim2 dim;

	virtual
	dim const
	size() const = 0;

	SGE_RENDERER_SYMBOL
	virtual
	sge::renderer::depth_stencil_surface_unique_ptr
	surface() const = 0;

	SGE_RENDERER_SYMBOL
	sge::renderer::texture::base::size_type
	content() const;
};

}
}
}

#endif
