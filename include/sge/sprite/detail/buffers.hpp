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


#ifndef SGE_SPRITE_DETAIL_BUFFERS_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_BUFFERS_HPP_INCLUDED

#include <sge/sprite/detail/roles/vertex_buffer.hpp>
#include <sge/sprite/detail/roles/index_buffer.hpp>
#include <sge/sprite/with_dim.hpp>
#include <sge/renderer/index_buffer_ptr.hpp>
#include <sge/renderer/vertex_buffer_ptr.hpp>
#include <majutsu/memory/fusion.hpp>
#include <majutsu/class.hpp>
#include <majutsu/composite.hpp>
#include <majutsu/fundamental.hpp>
#include <majutsu/role.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/if.hpp>

namespace sge
{
namespace sprite
{
namespace detail
{

template<
	typename Choices
>
struct buffers
{
private:
	typedef majutsu::role<
		majutsu::fundamental<
			sge::renderer::vertex_buffer_ptr
		>,
		detail::roles::vertex_buffer
	> vertex_buffer_role;

	typedef majutsu::role<
		majutsu::fundamental<
			sge::renderer::index_buffer_ptr
		>,
		detail::roles::index_buffer
	> index_buffer_role;
public:
	typedef majutsu::class_<
		majutsu::composite<
			boost::mpl::if_<
				boost::mpl::contains<
					typename Choices::elements,
					sprite::with_dim
				>,
				boost::mpl::vector2<
					vertex_buffer_role,
					index_buffer_role
				>,
				boost::mpl::vector1<
					vertex_buffer_role
				>
			>
		>,
		majutsu::memory::fusion
	> type;
};

}
}
}

#endif
