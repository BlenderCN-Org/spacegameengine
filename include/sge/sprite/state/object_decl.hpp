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


#ifndef SGE_SPRITE_STATE_OBJECT_DECL_HPP_INCLUDED
#define SGE_SPRITE_STATE_OBJECT_DECL_HPP_INCLUDED

#include <sge/sprite/state/object_fwd.hpp>
#include <sge/sprite/state/parameters_fwd.hpp>
#include <sge/sprite/state/render_device.hpp>
#include <sge/sprite/state/detail/object_class.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace sprite
{
namespace state
{

template<
	typename StateChoices
>
class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	typedef StateChoices state_choices;

	typedef typename sge::sprite::state::detail::object_class<
		StateChoices
	>::type elements_type;

	typedef sge::sprite::state::parameters<
		state_choices
	> parameters_type;

	typedef typename sge::sprite::state::render_device<
		StateChoices
	>::type render_device;

	object(
		render_device &,
		parameters_type const &
	);

	~object();

	elements_type const &
	elements() const;
private:
	elements_type const elements_;
};

}
}
}

#endif
