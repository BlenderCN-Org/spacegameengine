/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SRC_SYSTEMS_MODULES_CHARCONV_ORIGINAL_HPP_INCLUDED
#define SGE_SRC_SYSTEMS_MODULES_CHARCONV_ORIGINAL_HPP_INCLUDED

#include <sge/charconv/system_fwd.hpp>
#include <sge/charconv/system_scoped_ptr.hpp>
#include <sge/src/systems/modules/charconv/base.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace systems
{
namespace modules
{
namespace charconv
{

class original
:
	public sge::systems::modules::charconv::base
{
	FCPPT_NONCOPYABLE(
		original
	);
public:
	original();

	~original();

	sge::charconv::system &
	system() const;
private:
	sge::charconv::system_scoped_ptr const system_;
};

}
}
}
}

#endif
