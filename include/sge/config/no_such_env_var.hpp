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


#ifndef SGE_CONFIG_NO_SUCH_ENV_VAR_HPP_INCLUDED
#define SGE_CONFIG_NO_SUCH_ENV_VAR_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/config/exception.hpp>
#include <sge/config/detail/symbol.hpp>
#include <fcppt/string.hpp>


namespace sge
{
namespace config
{

class SGE_CORE_DETAIL_CLASS_SYMBOL no_such_env_var
:
	public sge::config::exception
{
public:
	SGE_CONFIG_DETAIL_SYMBOL
	explicit
	no_such_env_var(
		fcppt::string const &env_var
	);
};

}
}

#endif
