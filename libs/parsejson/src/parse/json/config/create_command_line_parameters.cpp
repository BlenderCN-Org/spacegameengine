/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/parse/json/config/command_line_parameters.hpp>
#include <sge/parse/json/config/create_command_line_parameters.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <fcppt/config/external_end.hpp>


sge::parse::json::config::command_line_parameters
sge::parse::json::config::create_command_line_parameters(
	int argc,
	char *argv[])
{
	config::command_line_parameters result(
		static_cast<config::command_line_parameters::size_type>(
			argc));
	for(
		config::command_line_parameters::size_type i =
			0;
		i < static_cast<config::command_line_parameters::size_type>(argc);
		++i)
		result[i] =
			fcppt::from_std_string(
				argv[static_cast<std::size_t>(i)]);
	return result;
}
