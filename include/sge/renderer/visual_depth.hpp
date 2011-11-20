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


#ifndef SGE_RENDERER_VISUAL_DEPTH_HPP_INCLUDED
#define SGE_RENDERER_VISUAL_DEPTH_HPP_INCLUDED

namespace sge
{
namespace renderer
{

/**
\brief The namespace for the \link sge::renderer::visual_depth::type visual_depth \endlink enum
*/
namespace visual_depth
{
/**
\brief The enum type for visual depths
*/
enum type
{
	/**
	\brief A visual depth of 16 bits
	*/
	depth16 = 16,
	/**
	\brief A visual depth of 32 bits
	*/
	depth32 = 32
};

}

}
}

#endif
