/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENGL_VF_FORMAT_HPP_INCLUDED
#define SGE_OPENGL_VF_FORMAT_HPP_INCLUDED

#include "actor_fwd.hpp"
#include "pointer.hpp"
#include "../context/object_fwd.hpp"
#include <sge/renderer/vf/dynamic/format.hpp>
#include <fcppt/noncopyable.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

namespace sge
{
namespace opengl
{
namespace vf
{

class format
{
	FCPPT_NONCOPYABLE(format)
public:
	explicit format(
		sge::opengl::context::object &,
		renderer::vf::dynamic::format const &
	);

	~format();

	renderer::vf::dynamic::format const &
	get() const;

	void
	use_me(
		vf::pointer
	) const;

	void
	unuse_me() const;
private:
	opengl::context::object &context_;

	renderer::vf::dynamic::format const fmt;

	typedef boost::ptr_vector<
		actor
	> actor_array;

	mutable actor_array actors;
};

}
}
}

#endif
