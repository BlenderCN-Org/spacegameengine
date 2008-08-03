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


#ifndef SGE_CON_ACTION_VAR_HPP_INCLUDED
#define SGE_CON_ACTION_VAR_HPP_INCLUDED

#include "action_var_base.hpp"
#include <boost/function.hpp>

namespace sge
{
namespace con
{

// this constructs an action_var with boost::function as functor
// which is an extremely convenient shortcut (you don't have to specify
// action_var< T,boost::function<T (const T &,const T &)> >
template<typename T>
struct action_var
{
	typedef boost::function<T (const T &,const T &)> fn;
	typedef action_var_base<T,fn> type;

	private:
	action_var() {}
	action_var(const action_var &) {}
};

}
}

#endif
