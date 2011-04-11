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


#include "../part.hpp"
#include "../to_actor.hpp"
#include "../actor.hpp"
#include "../client_state_combiner.hpp"
#include "../../common.hpp"
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <boost/foreach.hpp>

sge::opengl::vf::part::part(
	sge::opengl::context::object &_context,
	renderer::vf::dynamic::part const &_part
)
:
	context_(
		_context
	),
	part_(
		_part
	)
{
	renderer::vf::dynamic::ordered_element_list const &elems(
		part_.elements()
	);

	BOOST_FOREACH(
		renderer::vf::dynamic::ordered_element_list::const_reference elem,
		elems
	)
		fcppt::container::ptr::push_back_unique_ptr(
			actors_,
			vf::to_actor(
				elem,
				part_.stride(),
				_context
			)
		);
}

sge::opengl::vf::part::~part()
{
}

sge::renderer::vf::dynamic::part const &
sge::opengl::vf::part::get() const
{
	return part_;
}

void
sge::opengl::vf::part::use_me(
	vf::pointer const _src
) const
{
	client_state_combiner states_(
		context_
	);

	BOOST_FOREACH(
		actor_array::reference actor,
		actors_
	)
		actor(
			states_,
			static_cast<
				unsigned char const *
			>(
				_src
			)
			+ actor.offset()
		);
}

void
sge::opengl::vf::part::unuse_me() const
{
	client_state_combiner states_(
		context_
	);

	BOOST_FOREACH(
		actor_array::reference current,
		actors_
	)
		current.unuse(
			states_
		);
}
