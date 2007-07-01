/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_TEXTURE_MANAGER_HPP_INCLUDED
#define SGE_TEXTURE_MANAGER_HPP_INCLUDED

#include <stdexcept>
#include <boost/ptr_container/ptr_list.hpp>
#include <boost/scoped_ptr.hpp>
#include "../renderer/renderer.hpp"
#include "../renderer/texture.hpp"
#include "../image/image.hpp"
#include "fragmented_texture.hpp"

namespace sge
{

class texture_manager {
public:
	texture_manager(renderer_ptr rend, const fragmented_texture* proto);
	virtual_texture_ptr add_texture(texture::const_pointer src, texture::size_type w, texture::size_type h);
	virtual_texture_ptr add_texture(image_ptr im);
	virtual_texture_ptr add_texture(texture_ptr tex);
	renderer_ptr get_renderer() const;
	void prototype(fragmented_texture*);

	class image_too_big : public std::runtime_error {
	public:
		image_too_big() : std::runtime_error("texture_manager::add_texture() image too big!") {}
	};
private:
	typedef boost::ptr_list<fragmented_texture> fragmented_texture_list;
	fragmented_texture_list fragmented_textures;
	renderer_ptr rend;
	boost::scoped_ptr<const fragmented_texture> _prototype;
};

}

#endif
