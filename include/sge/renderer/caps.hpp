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


#ifndef SGE_RENDERER_CAPS_HPP_INCLUDED
#define SGE_RENDERER_CAPS_HPP_INCLUDED

#include "adapter.hpp"
#include "anisotropy_type.hpp"
#include "size_type.hpp"
#include "../export.hpp"
#include "../string.hpp"

namespace sge
{
namespace renderer
{

struct caps {
	SGE_SYMBOL caps(
		adapter_type adapter_,
		string const &driver_name,
		string const &description,
		size_type max_texure_edge_size,
		anisotropy_type max_anisotropy_);
		
	SGE_SYMBOL adapter_type adapter() const;
	SGE_SYMBOL string const &driver_name() const;
	SGE_SYMBOL string const &description() const;
	SGE_SYMBOL size_type max_texture_edge_size() const;
	SGE_SYMBOL anisotropy_type max_anisotropy() const; 
private:
	adapter_type       adapter_;
	string             driver_name_;
	string             description_;
	size_type          max_texture_edge_size_;
	anisotropy_type    max_anisotropy_;
};

}
}

#endif
