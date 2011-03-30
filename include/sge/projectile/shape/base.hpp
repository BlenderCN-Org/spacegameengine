#ifndef SGE_PROJECTILE_SHAPE_BASE_HPP_INCLUDED
#define SGE_PROJECTILE_SHAPE_BASE_HPP_INCLUDED

#include <fcppt/noncopyable.hpp>

class btCollisionShape;

namespace sge
{
namespace projectile
{
namespace shape
{
class base
{
FCPPT_NONCOPYABLE(
	base);
public:
	virtual btCollisionShape &
	bullet_shape() = 0;

	virtual btCollisionShape const &
	bullet_shape() const = 0;

	virtual
	~base();
protected:
	explicit
	base();
};
}
}
}

#endif
