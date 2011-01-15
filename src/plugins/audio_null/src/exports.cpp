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


#include "../player.hpp"
#include <sge/plugin/info.hpp>
#include <fcppt/export_symbol.hpp>
#include <fcppt/text.hpp>

extern "C"
{

FCPPT_EXPORT_SYMBOL void
plugin_version_info(
	sge::plugin::info *
);

FCPPT_EXPORT_SYMBOL sge::audio::player *
create_audio_player();

FCPPT_EXPORT_SYMBOL void
plugin_version_info(
	sge::plugin::info *const p
)
{
	if(!p)
		return;
	p->name = FCPPT_TEXT("audionull");
	p->description = FCPPT_TEXT("audio plugin that does not do anything");
	p->plugin_version = 0x1;
	p->min_core_version = 0x1;
	p->type = sge::plugin::capabilities::audio_player;
}

FCPPT_EXPORT_SYMBOL sge::audio::player *
create_audio_player()
{
	return new sge::audio_null::player();
}

}
