#ifndef SGE_ODE_BODY_HPP_INCLUDED
#define SGE_ODE_BODY_HPP_INCLUDED

#include "world_wrapper_fwd.hpp"
#include "point.hpp"
#include <sge/collision/sattelite_fwd.hpp>
#include <boost/noncopyable.hpp>
#include <ode/ode.h>

namespace sge
{
namespace ode
{
class body : boost::noncopyable
{
public:
	body(
		world_wrapper &,
		point const &center,
		point const &speed,
		collision::sattelite &);
	void pos(point const &);
	void speed(point const &);
	point const pos() const;
	point const speed() const;
	dBodyID &id();
	dBodyID const &id() const;
	~body();
private:
	dBodyID id_;

	static void moved(dBodyID);
};
}
}

#endif
