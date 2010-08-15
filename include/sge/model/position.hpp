#ifndef SGE_MODEL_POSITION_HPP_INCLUDED
#define SGE_MODEL_POSITION_HPP_INCLUDED

#include <sge/model/scalar.hpp>
#include <fcppt/math/vector/static.hpp>

namespace sge
{
namespace model
{
typedef
fcppt::math::vector::static_
<
	scalar,
	3
>::type
position;
}
}

#endif