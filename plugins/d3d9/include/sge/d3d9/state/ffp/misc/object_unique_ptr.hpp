/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_D3D9_STATE_FFP_MISC_OBJECT_UNIQUE_PTR_HPP_INCLUDED
#define SGE_D3D9_STATE_FFP_MISC_OBJECT_UNIQUE_PTR_HPP_INCLUDED

#include <sge/d3d9/state/ffp/misc/object_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sge
{
namespace d3d9
{
namespace state
{
namespace ffp
{
namespace misc
{

typedef
fcppt::unique_ptr<
	sge::d3d9::state::ffp::misc::object
>
object_unique_ptr;

}
}
}
}
}

#endif
