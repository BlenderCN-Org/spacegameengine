/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_RENDERER_RESOURCE_FLAGS_HPP_INCLUDED
#define SGE_RENDERER_RESOURCE_FLAGS_HPP_INCLUDED

#include <sge/renderer/resource_flags_fwd.hpp>


namespace sge
{
namespace renderer
{

/**
\brief Flags used when creating resources

\ingroup sge_renderer
*/
enum class resource_flags
{
	/**
	\brief Makes the resource dynamic

	A driver shall try to make a compromise so that dynamic resources are
	faster to lock/unlock but may be also slower to render. A dynamic
	resource must be completely updated for every render block, otherwise
	its contents will be undefined. This is to ensure that sge doesn't have
	to make a copy of the internal data. Dynamic resources are most useful
	if the contents change every frame anyway, e.g. in a sprite system.
	*/
	dynamic,
	/**
	\brief Makes a resource readable

	By default, a resource is not readable which means it cannot be locked
	so that data can be read from it. A readable resource might be slower
	to render, slower to lock or unlock or might require more memory.
	*/
	readable,
	fcppt_maximum = readable
};

}
}

#endif
