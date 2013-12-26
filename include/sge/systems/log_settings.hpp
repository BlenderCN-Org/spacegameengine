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


#ifndef SGE_SYSTEMS_LOG_SETTINGS_HPP_INCLUDED
#define SGE_SYSTEMS_LOG_SETTINGS_HPP_INCLUDED

#include <sge/systems/log_settings_fwd.hpp>
#include <sge/systems/optional_path.hpp>
#include <sge/systems/symbol.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace systems
{

class log_settings
{
public:
	SGE_SYSTEMS_SYMBOL
	log_settings(
		fcppt::log::location const &,
		fcppt::log::level
	);

	// TODO: Add location container

	SGE_SYSTEMS_SYMBOL
	sge::systems::log_settings &
	redirect(
		boost::filesystem::path const &
	);

	fcppt::log::location const &
	location() const;

	fcppt::log::level
	level() const;

	sge::systems::optional_path const &
	redirect() const;
private:
	fcppt::log::location location_;

	fcppt::log::level level_;

	sge::systems::optional_path redirect_;
};

}
}

#endif
