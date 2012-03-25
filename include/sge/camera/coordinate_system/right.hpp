#ifndef SGE_CAMERA_COORDINATE_SYSTEM_RIGHT_HPP_INCLUDED
#define SGE_CAMERA_COORDINATE_SYSTEM_RIGHT_HPP_INCLUDED

#include <sge/renderer/vector3.hpp>
#include <fcppt/strong_typedef.hpp>

namespace sge
{
namespace camera
{
namespace coordinate_system
{
/**
\brief The right axis of a coordinate system
\ingroup sgecamera
*/
FCPPT_MAKE_STRONG_TYPEDEF(
	sge::renderer::vector3,
	right);
}
}
}

#endif

