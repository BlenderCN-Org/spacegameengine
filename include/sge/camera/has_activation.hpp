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


#ifndef SGE_CAMERA_HAS_ACTIVATION_HPP_INCLUDED
#define SGE_CAMERA_HAS_ACTIVATION_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/camera/symbol.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace camera
{
class SGE_CLASS_SYMBOL has_activation
{
FCPPT_NONCOPYABLE(
	has_activation);
protected:
	SGE_CAMERA_SYMBOL
	explicit
	has_activation();
public:
	virtual bool
	is_active() const = 0;

	virtual void
	is_active(
		bool) = 0;

	void
	toggle_is_active();

	SGE_CAMERA_SYMBOL
	virtual ~has_activation() = 0;
};
}
}

#endif

