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


#ifndef SGE_RENDERER_TEXTURE_FILTER_NORMAL_OBJECT_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_FILTER_NORMAL_OBJECT_HPP_INCLUDED

#include <sge/renderer/texture/filter/normal/object_fwd.hpp>
#include <sge/renderer/texture/filter/normal/mag.hpp>
#include <sge/renderer/texture/filter/normal/min.hpp>
#include <sge/renderer/texture/filter/normal/mip.hpp>
#include <sge/renderer/symbol.hpp>

namespace sge
{
namespace renderer
{
namespace texture
{
namespace filter
{
namespace normal
{

class object
{
public:
	object(
		normal::mag::type,
		normal::min::type,
		normal::mip::type
	);

	SGE_RENDERER_SYMBOL
	normal::mag::type
	mag() const;

	SGE_RENDERER_SYMBOL
	normal::min::type
	min() const;

	SGE_RENDERER_SYMBOL
	normal::mip::type
	mip() const;
private:
	normal::mag::type mag_;

	normal::min::type min_;

	normal::mip::type mip_;
};

SGE_RENDERER_SYMBOL
bool
operator==(
	normal::object const &,
	normal::object const &
);

}
}
}
}
}

#endif
