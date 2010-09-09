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


#include "../body.hpp"
#include "../shapes/base.hpp"
#include "../world.hpp"
#include "../joint.hpp"
#include "../transformer_impl.hpp"
#include <fcppt/math/vector/basic_decl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <sge/collision/satellite.hpp>
#include <boost/foreach.hpp>

sge::ode::body::body(
	world &_world,
	transformer const &_transformer,
	dWorldID const _worldid,
	collision::satellite_ptr _satellite,
	collision::shapes::container const &_shapes,
	collision::point const &_position,
	collision::point const &_linear_velocity)
:
	world_(
		_world),
	transformer_(
		_transformer),
	body_(
		dBodyCreate(
			_worldid)),
	satellite_(
		move(
			_satellite
		)
	)
{
	BOOST_FOREACH(collision::shapes::container::const_reference r,_shapes)
		add(r);
	world_.body_count_++;
	dBodySetData(
		body_,
		this);
	dBodySetMovedCallback(
		body_,
		&body::moved);
	position(
		_position);
	linear_velocity(
		_linear_velocity);
	if (world_.plane_joint_)
		dJointAttach(
			world_.plane_joint_->value(), 
			body_, 
			0);
}

sge::collision::point const sge::ode::body::position() const
{
	dReal const * const p =
		dBodyGetPosition(
			body_);
	return
		transformer_.position_from_ode(
			point(
				p[0],
				p[1],
				p[2]));

}

void sge::ode::body::position(
	collision::point const &_p)
{
	point const p =
		transformer_.position_to_ode(
			_p);
	dBodySetPosition(
		body_,
		p.x(),
		p.y(),
		p.z());
}

sge::collision::point const sge::ode::body::linear_velocity() const
{
	dReal const * const p =
		dBodyGetLinearVel(
			body_);
	return
		transformer_.velocity_from_ode(
			point(
				p[0],
				p[1],
				p[2]));
}

void sge::ode::body::linear_velocity(
	collision::point const &_p)
{
	point const p =
		transformer_.velocity_to_ode(
			_p);
	dBodySetLinearVel(
		body_,
		p.x(),
		p.y(),
		p.z());
}

bool sge::ode::body::is_active()
{
	return
		dBodyIsEnabled(
			body_);
}

void sge::ode::body::is_active(
	bool const _b)
{
	if (_b)
		dBodyEnable(
			body_);
	else
		dBodyDisable(
			body_);
}

void sge::ode::body::add_to_group(
	group &_group)
{
	BOOST_FOREACH(shapes::container::const_reference r,shapes_)
		r->add_to_group(
			_group);
}

sge::ode::body::~body()
{
	world_.body_count_--;
	world_.destroy_body(
		body_);
	dBodyDestroy(
		body_);
}

void sge::ode::body::add(
	collision::shapes::base_ptr const _s)
{
	shapes_.push_back(
		fcppt::dynamic_pointer_cast<shapes::base,collision::shapes::base>(
			_s));
	dynamic_cast<ode::shapes::base &>(
		*_s).assign_body(body_);
}


void sge::ode::body::moved(
	dBodyID const _body)
{
	dReal const *const p =
		dBodyGetPosition(
			_body);
	body &b =
		*static_cast<body *>(
			dBodyGetData(
				_body));
	b.satellite_->position_change(
		b.transformer_.position_from_ode(
			point(
				p[0],
				p[1],
				p[2])));
}
