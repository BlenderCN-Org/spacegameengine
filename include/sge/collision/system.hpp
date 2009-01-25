#ifndef SGE_COLLISION_SYSTEM_HPP_INCLUDED
#define SGE_COLLISION_SYSTEM_HPP_INCLUDED

#include "system_fwd.hpp"
#include "unit.hpp"
#include "callbacks.hpp"
#include "sattelite_fwd.hpp"
#include "objects/fwd.hpp"
#include "../export.hpp"
#include <sge/time/types.hpp>
#include <sge/signals/connection.hpp>
#include <boost/noncopyable.hpp>

namespace sge
{
namespace collision
{
class SGE_CLASS_SYMBOL system : public boost::noncopyable
{
	public:
	virtual void test_callback(::sge::collision::test_callback const &) = 0;
	virtual signals::connection const 
		register_callback(callback const &) = 0;
	virtual objects::circle_ptr const create_circle(sattelite_ptr,unit radius) = 0;
	virtual void update(time::funit delta) = 0;
	SGE_SYMBOL virtual ~system();
};
}
}

#endif
