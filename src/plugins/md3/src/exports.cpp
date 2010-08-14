/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../loader.hpp"
#include <sge/plugin/info.hpp>
#include <fcppt/export_symbol.hpp>
#include <fcppt/text.hpp>

extern "C"
{

FCPPT_EXPORT_SYMBOL void
plugin_version_info(
	sge::plugin::info *
);

FCPPT_EXPORT_SYMBOL sge::model::loader *
create_model_loader();

FCPPT_EXPORT_SYMBOL void
plugin_version_info(
	sge::plugin::info *const i
)
{
	if(!i)
		return;
	i->name = FCPPT_TEXT("md3");
	i->description = FCPPT_TEXT("Provides loading of md3 model files.");
	i->type = sge::plugin::capabilities::model_loader;
	i->plugin_version = 0x1;
	i->min_core_version = 0x1;
}

FCPPT_EXPORT_SYMBOL sge::model::loader *
create_model_loader()
{
	return new sge::md3::loader();
}

}
