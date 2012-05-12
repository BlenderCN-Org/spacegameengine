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


#ifndef SGE_OPENGL_TEXTURE_FILTER_VISITOR_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_FILTER_VISITOR_HPP_INCLUDED

#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/renderer/texture/filter/anisotropic/object_fwd.hpp>
#include <sge/renderer/texture/filter/normal/object_fwd.hpp>
#include <fcppt/nonassignable.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{
namespace filter
{

class visitor
{
	FCPPT_NONASSIGNABLE(
		visitor
	);
public:
	visitor(
		sge::opengl::context::system::object &,
		sge::opengl::texture::binding const &,
		sge::opengl::texture::type
	);

	typedef void result_type;

	result_type
	operator()(
		sge::renderer::texture::filter::anisotropic::object const &
	) const;

	result_type
	operator()(
		sge::renderer::texture::filter::normal::object const &
	) const;
private:
	sge::opengl::context::system::object &system_context_;

	sge::opengl::texture::binding const &binding_;

	sge::opengl::texture::type const type_;
};

}
}
}
}

#endif
