/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SYSTEMS_CONFIG_HPP_INCLUDED
#define SGE_SYSTEMS_CONFIG_HPP_INCLUDED

#include <sge/systems/config_fwd.hpp>
#include <sge/systems/log_settings.hpp>
#include <sge/systems/optional_log_settings.hpp>
#include <sge/systems/optional_path.hpp>
#include <sge/systems/symbol.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace systems
{

class config
{
public:
	SGE_SYSTEMS_SYMBOL
	config();

	SGE_SYSTEMS_SYMBOL
	sge::systems::config &
	plugin_path(
		boost::filesystem::path const &
	);

	SGE_SYSTEMS_SYMBOL
	sge::systems::config &
	log_settings(
		sge::systems::log_settings const &
	);

	sge::systems::optional_path const &
	plugin_path() const;

	sge::systems::optional_log_settings const &
	log_settings() const;
private:
	sge::systems::optional_path plugin_path_;

	sge::systems::optional_log_settings log_settings_;
};

}
}

#endif
