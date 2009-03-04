#include "../system.hpp"
#include "../objects/circle.hpp"
#include <sge/structure_cast.hpp>

sge::ode::system::system()
	: library_(),
	  world_(),
		space_()
{
	// this could be set to disable the auto disable feature
	//dWorldSetAutoDisableFlag(world_.id(),0);
	
	dSpaceCollide(space_.id(),this,&internal_static_callback);
}

void
sge::ode::system::test_callback(
	::sge::collision::test_callback const &_test_callback)
{
	test_callback_ = _test_callback;
}

signals::connection const 
sge::ode::system::register_callback(
	callback const &c)
{
	return callback_.connect(c);
}

sge::collision::objects::circle_ptr const
sge::ode::system::create_circle(
	sattelite_ptr _sattelite,
	collision::point const &center,
	collision::point const &speed,
	unit radius)
{
	return sge::collision::objects::circle_ptr(
		new objects::circle(
			_sattelite,
			space_,
			world_,
			structure_cast<point>(center),
			structure_cast<point>(speed),
			static_cast<dReal>(radius)));
}

void
sge::ode::system::update(
	time::funit delta)
{
	time::funit const step_size = static_cast<time::funit>(0.01);
	unsigned const iterations = static_cast<unsigned>(delta/step_size);

	for (unsigned i = 0; i < iterations; ++i)
		dWorldStep(
			world_.id(),
			static_cast<dReal>(
				step_size));

	//dWorldQuickStep(dWorldID, dReal stepsize);
}

void sge::ode::system::internal_static_collide(void *data,dGeomID g1,dGeomID g2)
{
	static_cast<system *>(data)->internal_collide(g1,g2);
}

void sge::ode::system::internal_collide(dGeomID g1,dGeomID g2)
{
	if (!test_callback_)
		return;
	
	sattelite &s1 = *static_cast<sattelite*>(dGeomGetData(g1));
	sattelite &s2 = *static_cast<sattelite*>(dGeomGetData(g2));

	if (test_callback_(s1,s2))
	{
		// manual states that the contact array has to contain at least 1 element,
		// so to be sure, allocate one dContactGeom here
		dContactGeom g;
		if (dCollide(g1,g2,1,&g,0))
			callback_(s1,s2);
	}
}
