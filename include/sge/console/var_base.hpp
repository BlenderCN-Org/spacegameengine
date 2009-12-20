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


#ifndef SGE_CONSOLE_VAR_BASE_HPP_INCLUDED
#define SGE_CONSOLE_VAR_BASE_HPP_INCLUDED

#include <sge/console/object_fwd.hpp>
#include <sge/symbol.hpp>
#include <sge/class_symbol.hpp>
#include <fcppt/string.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace console
{

class SGE_CLASS_SYMBOL var_base
{
	FCPPT_NONCOPYABLE(var_base)
public:
	SGE_SYMBOL var_base(
		object &,
		fcppt::string const &
	);

	virtual void
	string(
		fcppt::string const &
	) = 0;

	virtual fcppt::string const
	string() const = 0;

	SGE_SYMBOL fcppt::string const
	name() const;

	virtual ~var_base();
private:
	object &object_;
	fcppt::string name_;
};

}
}

#endif
