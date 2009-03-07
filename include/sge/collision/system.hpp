#ifndef SGE_COLLISION_SYSTEM_HPP_INCLUDED
#define SGE_COLLISION_SYSTEM_HPP_INCLUDED

#include <sge/collision/world_fwd.hpp>
#include <sge/collision/optional_rect.hpp>
#include <sge/export.hpp>
#include <sge/noncopyable.hpp>
#include <boost/optional.hpp>

namespace sge
{
namespace collision
{
class SGE_CLASS_SYMBOL system
{
	SGE_NONCOPYABLE(system)
protected:
	SGE_SYMBOL system();
public:
	virtual world_ptr const
	create_world(
		optional_rect const & = boost::none) = 0;
	
	virtual ~system();
};
}
}

#endif
