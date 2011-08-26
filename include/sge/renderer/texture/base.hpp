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


#ifndef SGE_RENDERER_TEXTURE_BASE_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_BASE_HPP_INCLUDED

#include <sge/renderer/texture/base_fwd.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/texture/mipmap/object_fwd.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/symbol.hpp>
#include <sge/class_symbol.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace renderer
{
namespace texture
{

class SGE_CLASS_SYMBOL base
{
	FCPPT_NONCOPYABLE(
		base
	);
protected:
	SGE_RENDERER_SYMBOL
	base();
public:
	typedef renderer::size_type size_type;

	SGE_RENDERER_SYMBOL
	virtual ~base() = 0;

	virtual size_type
	content() const = 0;

	virtual renderer::resource_flags_field const
	resource_flags() const = 0;

	virtual renderer::texture::capabilities_field const
	capabilities() const = 0;

	virtual renderer::texture::mipmap::object const
	mipmap() const = 0;
};

}
}
}

#endif
