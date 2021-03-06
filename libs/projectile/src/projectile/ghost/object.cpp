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


#include <sge/projectile/ghost/object.hpp>
#include <sge/projectile/ghost/parameters.hpp>
#include <sge/projectile/impl/bullet_to_vector2.hpp>
#include <sge/projectile/impl/object_extrusion_depth.hpp>
#include <sge/projectile/impl/vector2_to_bullet.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <BulletCollision/CollisionShapes/btBoxShape.h>
#include <fcppt/config/external_end.hpp>


sge::projectile::ghost::object::object(
	parameters const &p)
:
	log_{
		p.log()
	},
	body_enter_(),
	body_exit_(),
	box_shape_(
		fcppt::unique_ptr_to_base<
			btCollisionShape
		>(
			// The box shape gets _HALF EXTENTS_
			fcppt::make_unique_ptr<btBoxShape>(
				btVector3(
					p.size().get().w()/2,
					p.size().get().h()/2,
					sge::projectile::impl::object_extrusion_depth())))),
	ghost_object_(
		fcppt::make_unique_ptr<btPairCachingGhostObject>())
{
	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::out
			<< this
			<< FCPPT_TEXT(": Created a new ghost, position ")
			<< p.position().get()
			<< FCPPT_TEXT(", size ")
			<< p.size().get()
	)

	ghost_object_->setCollisionFlags(
		ghost_object_->getCollisionFlags() |
		btCollisionObject::CF_NO_CONTACT_RESPONSE);

	ghost_object_->setUserPointer(
		this);

	ghost_object_->setCollisionShape(
		box_shape_.get_pointer());

	position(
		p.position().get());
}

sge::projectile::vector2
sge::projectile::ghost::object::position() const
{
	return
		sge::projectile::impl::bullet_to_vector2(
			ghost_object_->getWorldTransform().getOrigin());
}

void
sge::projectile::ghost::object::position(
	vector2 const &p)
{
	ghost_object_->setWorldTransform(
		btTransform(
			btMatrix3x3::getIdentity(),
			sge::projectile::impl::vector2_to_bullet(
				p)));
}

fcppt::signal::auto_connection
sge::projectile::ghost::object::body_enter(
	sge::projectile::ghost::body_enter const &f)
{
	return
		body_enter_.connect(
			f);
}

fcppt::signal::auto_connection
sge::projectile::ghost::object::body_exit(
	sge::projectile::ghost::body_exit const &f)
{
	return
		body_exit_.connect(
			f);
}

sge::projectile::ghost::object::~object()
{
}

void
sge::projectile::ghost::object::enter_internal(
	body::object const &b)
{
	body_enter_(
		b);
}

void
sge::projectile::ghost::object::exit_internal(
	body::object const &b)
{
	body_exit_(
		b);
}
