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

#ifndef SGE_GUI_LAYOUTS_NULL_HPP_INCLUDED
#define SGE_GUI_LAYOUTS_NULL_HPP_INCLUDED

#include <sge/gui/layouts/base.hpp>
#include <sge/gui/export.hpp>

namespace sge
{
namespace gui
{
namespace layouts
{
class null : public base
{
	public:
	SGE_GUI_SYMBOL null();

	SGE_GUI_SYMBOL void compile(invalidation::type const &);
	SGE_GUI_SYMBOL void compile_static();
	SGE_GUI_SYMBOL void pos(point const &);
	SGE_GUI_SYMBOL void size(dim const &);
	SGE_GUI_SYMBOL dim const optimal_size() const;
};
}
}
}

#endif
