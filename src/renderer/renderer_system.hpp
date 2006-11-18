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


#ifndef SGE_RENDER_ERSYSTEM_HPP_INCLUDED
#define SGE_RENDER_ERSYSTEM_HPP_INCLUDED

#include <vector>
#include "../shared_ptr.hpp"
#include "../types.hpp"
#include "./types.hpp"
#include "./renderer.hpp"

namespace sge
{

typedef std::vector<renderer_caps> renderer_caps_array;

class renderer_system {
public:
	enum { use_best_renderer = -1 };
	virtual renderer_ptr create_renderer(const renderer_parameters& param,
	                                     int adapter = use_best_renderer) = 0;
	virtual void get_renderer_caps(renderer_caps_array& v) const = 0;
	virtual ~renderer_system(){}
};

typedef shared_ptr<renderer_system> renderer_system_ptr;

}

#endif
