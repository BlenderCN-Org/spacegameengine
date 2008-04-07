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


#include "../texture_animation.hpp"
#include "../object.hpp"
#include "../../math/rect_impl.hpp"
#include <boost/next_prior.hpp>

sge::sprite::texture_animation::texture_animation(
	const animation_series& series_,
	const loop_method::type action,
	object *spr)
: series(series_),
  action(action),
  cur_timer(0),
  s(0),
  pos(series.end())
{
	bind(spr);
}

void sge::sprite::texture_animation::bind(object *new_sprite)
{
	s = new_sprite;
	reset();
}

bool sge::sprite::texture_animation::process()
{
	if(!s || series.empty())
		return true;
	
	if(!cur_timer.expired())
		return false;

	const animation_series::const_iterator next(boost::next(pos));

	if(action == loop_method::repeat
	   && next == series.end())
	{
		reset();
		return true;
	}
		
	if(action == loop_method::stop_after_end
	   && next == series.end())
	{
		s->set_texture(no_texture);
		return true;
	}
	
	if(action == loop_method::stop_at_end
	   && next == series.end())
		return true;

	++pos;

	cur_timer.interval(pos->delay);
	s->set_texture(pos->tex);

	return false;
}

void sge::sprite::texture_animation::reset()
{
	if(!s || series.empty())
		return;
	s->set_texture(series[0].tex);
	pos = series.begin();
	cur_timer.interval(series[0].delay);
}

const sge::texture::dim_type
sge::sprite::texture_animation::dim() const
{
	return series.at(0).tex->area().size();
}

sge::sprite::texture_animation::entity::entity(
	const time_type delay,
	const virtual_texture_ptr tex)
: delay(delay),
  tex(tex)
{}
