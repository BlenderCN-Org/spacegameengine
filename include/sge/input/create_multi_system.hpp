/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_INPUT_CREATE_MULTI_SYSTEM_HPP_INCLUDED
#define SGE_INPUT_CREATE_MULTI_SYSTEM_HPP_INCLUDED

#include <sge/input/system_unique_ptr.hpp>
#include <sge/input/detail/symbol.hpp>
#include <sge/input/plugin/collection_fwd.hpp>
#include <sge/log/option_container.hpp>


namespace sge
{
namespace input
{

SGE_INPUT_DETAIL_SYMBOL
sge::input::system_unique_ptr
create_multi_system(
	sge::input::plugin::collection const &,
	sge::log::option_container const &
);

}
}

#endif
