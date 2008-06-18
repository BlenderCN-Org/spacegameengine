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

#include "../string.hpp"
#include "../shared_ptr.hpp"
#include "../plugin_traits.hpp"
#include "../path.hpp"
#include "../export.hpp"
#include "../renderer/image_view.hpp"
#include "object.hpp"
#include "format.hpp"

namespace sge
{
namespace image
{

class loader {
public:
	virtual const object_ptr
	load_image(
		const path&) = 0;

	virtual const object_ptr
	load_image(
		format::type type,
		object::const_pointer format_data,
		object::size_type size) = 0;

	virtual const object_ptr
	create_image(
		renderer::const_image_view const &) = 0;

	SGE_SYMBOL virtual ~loader();
};

typedef shared_ptr<loader> loader_ptr;

}

namespace detail
{

template<> struct plugin_traits<image::loader> {
	SGE_SYMBOL static address_name plugin_loader_name();
	SGE_SYMBOL static plugin_type::type get_plugin_type();
	typedef image::loader* (*loader_fun)();
};

}

}

#endif
