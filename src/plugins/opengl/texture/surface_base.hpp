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


#ifndef SGE_OPENGL_TEXTURE_SURFACE_BASE_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_SURFACE_BASE_HPP_INCLUDED

#include "surface_base_fwd.hpp"
#include "id.hpp"
#include "type.hpp"
#include <sge/renderer/stage.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

class surface_base
{
	FCPPT_NONCOPYABLE(
		surface_base
	);
protected:
	surface_base(
		texture::type,
		texture::id,
		sge::renderer::stage
	);
public:
	virtual ~surface_base();

	texture::type const
	type() const;

	texture::id const
	id() const;

	sge::renderer::stage const
	stage() const;
private:
	texture::type const type_;

	texture::id const id_;

	sge::renderer::stage const stage_;
};

}
}
}

#endif
