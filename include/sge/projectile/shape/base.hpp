#ifndef SGE_PROJECTILE_SHAPE_BASE_HPP_INCLUDED
#define SGE_PROJECTILE_SHAPE_BASE_HPP_INCLUDED

#include <BulletCollision/CollisionShapes/btCollisionShape.h>
#include <sge/projectile/symbol.hpp>
#include <fcppt/noncopyable.hpp>

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

	SGE_PROJECTILE_SYMBOL
	virtual
	~base();
protected:
	SGE_PROJECTILE_SYMBOL
	explicit
	base();
};
}
}
}

#endif
