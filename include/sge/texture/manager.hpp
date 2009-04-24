/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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



#ifndef SGE_TEXTURE_MANAGER_HPP_INCLUDED
#define SGE_TEXTURE_MANAGER_HPP_INCLUDED

#include <sge/texture/part_fwd.hpp>
#include <sge/texture/fragmented_auto_ptr.hpp>
#include <sge/texture/detail/container_position.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/image_view.hpp>
#include <sge/noncopyable.hpp>
#include <sge/export.hpp>
#include <boost/function.hpp>

namespace sge
{
namespace texture
{

class fragmented;

class manager {
	SGE_NONCOPYABLE(manager)
public:
	typedef boost::function<
		fragmented_auto_ptr ()
	> onalloc_function;

	SGE_SYMBOL manager(
		sge::renderer::device_ptr rend,
		onalloc_function const &);
	SGE_SYMBOL ~manager();

	SGE_SYMBOL part_ptr const
	add(
		sge::renderer::const_image_view const &src);

	SGE_SYMBOL sge::renderer::device_ptr const
	renderer() const;

	SGE_SYMBOL void
	onalloc(
		onalloc_function const &);
private:
	friend class fragmented;

	void
	part_freed(
		detail::container_position const &,
		fragmented const &);
	
	sge::renderer::device_ptr const     rend;
	onalloc_function                    onalloc_;

	detail::fragmented_queue            free_textures;
	detail::fragmented_list             full_textures;
};

}
}

#endif
