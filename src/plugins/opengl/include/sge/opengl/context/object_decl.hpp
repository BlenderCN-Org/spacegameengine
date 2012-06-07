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


#ifndef SGE_OPENGL_CONTEXT_OBJECT_DECL_HPP_INCLUDED
#define SGE_OPENGL_CONTEXT_OBJECT_DECL_HPP_INCLUDED

#include <sge/opengl/context/base_fwd.hpp>
#include <sge/opengl/context/base_unique_ptr.hpp>
#include <sge/opengl/context/container_decl.hpp>
#include <sge/opengl/context/id_fwd.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace context
{

template<
	typename Domain
>
class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	object();

	~object();

	typedef sge::opengl::context::base<
		Domain
	> base_type;

	typedef sge::opengl::context::id<
		Domain
	> id_type;

	base_type *
	get(
		id_type
	);

	typedef typename sge::opengl::context::base_unique_ptr<
		Domain
	>::type base_unique_ptr;

	base_type &
	insert(
		id_type,
		base_unique_ptr
	);
private:
	typedef sge::opengl::context::container<
		Domain
	> container;

	container elements_;
};

}
}
}

#endif