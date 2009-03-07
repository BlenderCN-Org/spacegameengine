#ifndef SGE_ODE_WORLD_WRAPPER_HPP_INCLUDED
#define SGE_ODE_WORLD_WRAPPER_HPP_INCLUDED

#include <sge/noncopyable.hpp>
#include <ode/ode.h>

namespace sge
{
namespace ode
{
class world_wrapper
{
	SGE_NONCOPYABLE(world_wrapper)
public:
	world_wrapper();
	dWorldID &id();
	dWorldID const &id() const;
	~world_wrapper();
private:
	dWorldID id_;
};
}
}

#endif
