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


#include <boost/cast.hpp>
#include "../../../exception.hpp"
#include "../../../plugin.hpp"
#include "../../../x_window.hpp"
#include "../input_system.hpp"

extern "C"
{

void plugin_version_info(sge::plugin_info* const i)
{
	if(!i)
		return;
	i->name = SGE_TEXT("X input plugin");
	i->description = SGE_TEXT("");
	i->type = sge::plugin_type::input;
	i->plugin_version = 0x1;
	i->min_core_version = 0x1;
}

sge::input_system* create_input_system(const sge::window_ptr w)
{
	if(!w)
		throw sge::exception(SGE_TEXT("xinput plugin's window parameter may not be 0!"));
	boost::polymorphic_cast<sge::x_window*>(w.get());
	return new sge::xinput::input_system(sge::dynamic_pointer_cast<sge::x_window_ptr::value_type>(w));
}

}
