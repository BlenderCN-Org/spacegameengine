/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_WINDOW_HPP_INCLUDED
#define SGE_WINDOW_HPP_INCLUDED

#include "types.hpp"
#include "shared_ptr.hpp"
#include "math/dim.hpp"
#include "math/vector.hpp"
#include "string.hpp"

namespace sge
{

class window {
public:
	typedef int pos_type;
	typedef unsigned size_type;
	typedef math::basic_vector<pos_type,2> window_pos;
	typedef math::basic_dim<size_type,2> window_size;

	virtual void title(const string& title) = 0;
	virtual window_size size() const = 0;
	size_type width() const;
	size_type height() const;
	virtual void size(window_size newsize) = 0;
	virtual ~window(){}

	static void dispatch();
};

typedef shared_ptr<window> window_ptr;

//void dispatch_events();

}

#endif
