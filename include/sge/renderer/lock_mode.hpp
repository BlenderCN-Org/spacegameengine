/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_RENDERER_LOCK_MODE_HPP_INCLUDED
#define SGE_RENDERER_LOCK_MODE_HPP_INCLUDED

#include <sge/renderer/lock_mode_fwd.hpp>


namespace sge
{
namespace renderer
{

enum class lock_mode
{
	/**
	\brief Locks a resource for writing only

	This is always safe to use and is the most efficient way to update a
	resource.
	*/
	writeonly,
	/**
	\brief Locks a resource for reading and writing

	The contents of the resource can be read and written at the same time.
	This can only be used if the resource has been created with
	sge::renderer::resource_flags::readable. Reading a resource can slow
	locking and unlocking down a lot.
	*/
	readwrite
};

}
}

#endif
