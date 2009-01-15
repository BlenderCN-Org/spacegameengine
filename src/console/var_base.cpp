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


#include <sge/console/var_base.hpp>
#include <sge/console/console.hpp>
#include <sge/console/detail/singleton.hpp>
#ifdef SGE_MSVC_VIRTUAL_BASE_REFERENCE_BUG
#include <sge/console/exception.hpp>
#include <sge/text.hpp>
#endif

sge::con::var_base::var_base(
	string const &name_)
:
	name_(name_)
{}

void sge::con::var_base::late_construct()
{
	instance().add(name_, *this);
}

sge::con::var_base::~var_base()
{
	instance().erase(name_);
}

sge::string const
sge::con::var_base::name() const
{
	return name_;
}

#ifdef SGE_MSVC_VIRTUAL_BASE_REFERENCE_BUG
void sge::con::var_base::set(
	string const &)
{
	throw exception(
		SGE_TEXT("var_base::set() is abstract (dumb VC++ hack)!"));
}

sge::string const sge::con::var_base::get() const
{
	throw exception(
		SGE_TEXT("var_base::get() is abstract (dumb VC++ hack)!"));
}
#endif
