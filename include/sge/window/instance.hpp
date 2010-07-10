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


#ifndef SGE_WINDOW_INSTANCE_HPP_INCLUDED
#define SGE_WINDOW_INSTANCE_HPP_INCLUDED

#include <sge/window/dim_type.hpp>
#include <sge/mainloop/dispatchable.hpp>
#include <sge/symbol.hpp>
#include <sge/class_symbol.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace window
{

class SGE_CLASS_SYMBOL instance
:
	public mainloop::dispatchable
{
	FCPPT_NONCOPYABLE(instance)
protected:
	SGE_SYMBOL instance();
public:
	typedef window::dim_type dim_type;

	virtual dim_type const
	size() const = 0;

	virtual void
	show() = 0;

	SGE_SYMBOL virtual ~instance();
};

}
}

#endif
