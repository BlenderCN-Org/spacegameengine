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


#ifndef SGE_OPENGL_TARGET_HPP_INCLUDED
#define SGE_OPENGL_TARGET_HPP_INCLUDED

#include "common.hpp"
#include "pixel_pack_buffer.hpp"
#include <sge/shared_ptr.hpp>
#include <sge/renderer/target.hpp>
#include <boost/scoped_ptr.hpp>

namespace sge
{
namespace ogl
{

class target : public sge::renderer::target {
public:
	virtual void bind_me() const = 0;
private:
	void lock();
	void lock(renderer::lock_rect const &dest);
	void unlock();
	renderer::const_image_view const view() const;

	virtual size_type stride() const = 0;
	virtual GLenum format() const = 0;
	virtual GLenum format_type() const = 0;

	boost::scoped_ptr<
		pixel_pack_buffer> buffer;
};

typedef shared_ptr<target> target_ptr;

}
}

#endif
