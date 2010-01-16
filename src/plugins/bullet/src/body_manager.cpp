#include "../body_manager.hpp"
#include "../log.hpp"
#include "../world.hpp"
#include "../shapes/base.hpp"
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/assert.hpp>
#include <fcppt/text.hpp>
#include <utility>
#include <BulletCollision/NarrowPhaseCollision/btManifoldPoint.h>

namespace
{
fcppt::log::object 
mylogger(
	fcppt::log::parameters::inherited(
		sge::bullet::log(),
		FCPPT_TEXT("body manager")));
}


sge::bullet::body_manager::body_manager(
	world &_world)
:
	world_(
		_world)
{
}

sge::bullet::collision_proxy const &
sge::bullet::body_manager::begin(
	btManifoldPoint &cp,
	shapes::base &s0,
	shapes::base &s1)
{
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ 
			<< FCPPT_TEXT("There was a collision between shapes ")
			<< &s0
			<< FCPPT_TEXT(" and ")
			<< &s1);
			
	std::pair<pair_map::iterator,bool> const r = 
		pairs_.insert(
			std::make_pair(
				collision_proxy(
					s0,
					s1,
					world_),
				static_cast<size_type>(
					1)));
	
	if (r.second)
	{
		FCPPT_LOG_DEBUG(
			mylogger,
			fcppt::log::_ 
				<< FCPPT_TEXT("The collision is new!"));
				
		if (s0.is_solid() && s1.is_solid())
		{
			FCPPT_LOG_DEBUG(
				mylogger,
				fcppt::log::_ 
					<< FCPPT_TEXT("Both items are solid, sending solid callback"));
			solid_callback_(
				std::tr1::ref(
					s0.satellite()),
				std::tr1::ref(
					s1.satellite()));
			world_.solid_collision(
				s0,
				s1);
			return 
				r.first->first;
		}
		
		FCPPT_LOG_DEBUG(
			mylogger,
			fcppt::log::_ 
				<< FCPPT_TEXT("Sending begin callback"));
				
		begin_callback_(
			std::tr1::ref(
				s0.satellite()),
			std::tr1::ref(
				s1.satellite()));
	}
	else
	{
				
		if (cp.m_lifeTime)
		{
			FCPPT_LOG_DEBUG(
				mylogger,
				fcppt::log::_ 
					<< FCPPT_TEXT("Contact point's lifetime wasn't zero, so it isn't new, not doing anything."));
		}
		else
		{
			FCPPT_LOG_DEBUG(
				mylogger,
				fcppt::log::_ 
					<< FCPPT_TEXT("The collision is old, increasing refcount"));
			r.first->second++;
		}
	}
	return 
		r.first->first;
}

void
sge::bullet::body_manager::end(
	shapes::base &s0,
	shapes::base &s1)
{
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ 
			<< FCPPT_TEXT("Collision end between ")
			<< &s0
			<< FCPPT_TEXT(" and ")
			<< &s1);
			
	pair_map::iterator const i = 
		pairs_.find(
			collision_proxy(
				s0,
				s1,
				world_));
	
	FCPPT_ASSERT(
		i != pairs_.end());
	
	FCPPT_ASSERT(
		i->second != static_cast<size_type>(0));
	
	if (--i->second != static_cast<size_type>(0))
	{
		/*
		FCPPT_LOG_DEBUG(
			mylogger,
			fcppt::log::_ 
				<< FCPPT_TEXT("Decreased refcount is ")
				<< i->second
				<< FCPPT_TEXT(" so just returning"));
				*/
		return;
	}
	
	/*
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ 
			<< FCPPT_TEXT("Decreased refcount is zero."));
			*/
	
	pairs_.erase(
		i);
	
	if (!s0.is_solid() || !s1.is_solid())
	{
		FCPPT_LOG_DEBUG(
			mylogger,
			fcppt::log::_ 
				<< FCPPT_TEXT("One of the items isn't solid, so sending end callback"));
				
		end_callback_(
			std::tr1::ref(
				s0.satellite()),
			std::tr1::ref(
				s1.satellite()));
	}
}

fcppt::signal::auto_connection
sge::bullet::body_manager::register_begin(
	collision::shape_callback const &f)
{
	return
		begin_callback_.connect(
			f);
}
	
fcppt::signal::auto_connection
sge::bullet::body_manager::register_end(
	collision::shape_callback const &f)
{
	return
		end_callback_.connect(
			f);
}
	
fcppt::signal::auto_connection
sge::bullet::body_manager::register_solid(
	collision::shape_callback const &f)
{
	return
		solid_callback_.connect(
			f);
}
