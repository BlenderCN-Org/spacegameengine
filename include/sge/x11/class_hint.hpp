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


#ifndef SGE_X11_CLASS_HINT_HPP_INCLUDED
#define SGE_X11_CLASS_HINT_HPP_INCLUDED

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <sge/symbol.hpp>
#include <fcppt/string.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <string>

namespace sge
{
namespace x11
{

class class_hint
{
	FCPPT_NONCOPYABLE(class_hint)
public:
	SGE_SYMBOL class_hint(
		fcppt::string const &app_name,
		fcppt::string const &class_name
	);

	SGE_SYMBOL ~class_hint();

	SGE_SYMBOL XClassHint *
	get() const;
private:
	class impl;

	fcppt::scoped_ptr<impl> impl_;

	std::string const
		app_name,
		res_name;
};

}
}

#endif
