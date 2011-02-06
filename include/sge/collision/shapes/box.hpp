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


#ifndef SGE_COLLISION_SHAPES_BOX_HPP_INCLUDED
#define SGE_COLLISION_SHAPES_BOX_HPP_INCLUDED

#include <sge/collision/shapes/base.hpp>
#include <sge/collision/shapes/box_fwd.hpp>
#include <sge/collision/dim.hpp>
#include <sge/class_symbol.hpp>
#include <sge/symbol.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace collision
{
namespace shapes
{

class SGE_CLASS_SYMBOL box
:
	public virtual base
{
	FCPPT_NONCOPYABLE(
		box
	);
protected:
	SGE_SYMBOL
	box();
public:
	virtual collision::dim const 
	dim() const = 0;
	
	virtual void 
	dim(
		collision::dim const &
	) = 0;

	SGE_SYMBOL
	virtual ~box();
};

}
}
}

#endif
