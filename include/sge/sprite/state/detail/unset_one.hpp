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


#ifndef SGE_SPRITE_STATE_DETAIL_UNSET_ONE_HPP_INCLUDED
#define SGE_SPRITE_STATE_DETAIL_UNSET_ONE_HPP_INCLUDED

#include <sge/sprite/state/render_context.hpp>
#include <sge/sprite/state/detail/options_class.hpp>
#include <majutsu/get.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/tag.hpp>


namespace sge
{
namespace sprite
{
namespace state
{
namespace detail
{

template<
	typename StateChoices
>
class unset_one
{
	FCPPT_NONASSIGNABLE(
		unset_one
	);
public:
	typedef
	sge::sprite::state::detail::options_class<
		StateChoices
	>
	options_class;

	typedef
	sge::sprite::state::render_context<
		StateChoices
	>
	render_context;

	unset_one(
		render_context &_render_context,
		options_class const &_options
	)
	:
		render_context_(
			_render_context
		),
		options_(
			_options
		)
	{
	}

	typedef void result_type;

	template<
		typename Type
	>
	result_type
	operator()(
		fcppt::tag<
			Type
		>
	) const
	{
		if(
			majutsu::get<
				typename Type::role
			>(
				options_
			)
		)
			Type::unset(
				render_context_
			);
	}
private:
	render_context &render_context_;

	options_class const &options_;
};

}
}
}
}

#endif
