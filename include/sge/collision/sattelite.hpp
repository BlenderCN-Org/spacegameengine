#ifndef SGE_COLLISION_SATTELITE_HPP_INCLUDED
#define SGE_COLLISION_SATTELITE_HPP_INCLUDED

#include "sattelite_fwd.hpp"
#include "types.hpp"
#include "../export.hpp"
#include <boost/noncopyable.hpp>

namespace sge
{
namespace collision
{
class SGE_CLASS_SYMBOL sattelite : public boost::noncopyable
{
	public:
	virtual void position_change(point const &) = 0;
	SGE_SYMBOL virtual ~sattelite();
};
}
}

#endif
