/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SPRITE_BUFFERS_WITH_DECLARATION_DECL_HPP_INCLUDED
#define SGE_SPRITE_BUFFERS_WITH_DECLARATION_DECL_HPP_INCLUDED

#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/vertex/declaration_scoped_ptr.hpp>
#include <sge/sprite/count.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/buffers/parameters_fwd.hpp>
#include <sge/sprite/buffers/with_declaration_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace sprite
{
namespace buffers
{

template<
	typename Buffers
>
class with_declaration
{
	FCPPT_NONCOPYABLE(
		with_declaration
	);
public:
	with_declaration(
		sge::renderer::device::core &,
		sge::sprite::buffers::option
	);

	~with_declaration();

	typedef Buffers buffers_type;

	typedef typename buffers_type::choices choices;

	typedef typename Buffers::slice_type slice_type;

	slice_type &
	allocate(
		sge::sprite::count
	);

	sge::sprite::buffers::parameters const &
	parameters() const;

	buffers_type &
	impl();

	buffers_type const &
	impl() const;
private:
	sge::renderer::vertex::declaration_scoped_ptr const vertex_declaration_;

	buffers_type buffers_;
};

}
}
}

#endif
