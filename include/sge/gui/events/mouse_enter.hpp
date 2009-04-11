#ifndef SGE_GUI_EVENTS_MOUSE_ENTER_HPP_INCLUDED
#define SGE_GUI_EVENTS_MOUSE_ENTER_HPP_INCLUDED

#include <sge/gui/point.hpp>
#include <sge/gui/export.hpp>
#include <sge/math/vector/basic_impl.hpp>

namespace sge
{
namespace gui
{
namespace events
{
class mouse_enter
{
	public:
	SGE_GUI_SYMBOL mouse_enter(point const &);
	point const &pos() const { return pos_; }
	private:
	point const pos_;
};
}
}
}

#endif
