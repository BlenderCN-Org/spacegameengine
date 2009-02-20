/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_IMAGE_LOADER_HPP_INCLUDED
#define SGE_IMAGE_LOADER_HPP_INCLUDED

#include <sge/image/object_fwd.hpp>
//#include <sge/image/format.hpp>
#include <sge/filesystem/path.hpp>
#include <sge/renderer/image_view.hpp>
#include <sge/export.hpp>
#include <sge/noncopyable.hpp>

namespace sge
{
namespace image
{

class SGE_CLASS_SYMBOL loader {
	SGE_NONCOPYABLE(loader)
protected:
	SGE_SYMBOL loader();
public:
	virtual const object_ptr
	load(
		filesystem::path const &) = 0;

	/*virtual object_ptr const
	load(
		format::type type,
		object::const_pointer format_data,
		object::size_type size) = 0;*/

	virtual object_ptr const
	create(
		renderer::const_image_view const &) = 0;

	SGE_SYMBOL virtual ~loader();
};

}
}

#endif
