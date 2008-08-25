#ifndef SGE_GUI_TYPES_HPP_INCLUDED
#define SGE_GUI_TYPES_HPP_INCLUDED

#include "../sprite/types.hpp"
#include "../sprite/fwd.hpp"
#include "../math/vector.hpp"
#include "../input/key_type.hpp"
#include "../renderer/texture.hpp"

namespace sge
{
namespace gui
{
typedef sprite::unit unit;
typedef sprite::point point;
typedef sprite::dim dim;
typedef sprite::rect rect;
typedef math::basic_vector<input::key_state,2u> mouse_point;

namespace direction
{
enum type { up,down,left,right };
}
}
}

#endif
