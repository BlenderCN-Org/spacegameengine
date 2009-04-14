#ifndef SGE_GUI_CURSOR_HPP_INCLUDED
#define SGE_GUI_CURSOR_HPP_INCLUDED

#include <sge/gui/point.hpp>
#include <sge/gui/export.hpp>
#include <sge/sprite/object.hpp>
#include <sge/auto_ptr.hpp>

namespace sge
{
namespace gui
{
class SGE_CLASS_SYMBOL cursor
{
public:
	SGE_GUI_SYMBOL virtual void pos(point const &) = 0;
	SGE_GUI_SYMBOL virtual point const pos() const = 0;
	SGE_GUI_SYMBOL virtual sge::sprite::object const sprite() const = 0;
	SGE_GUI_SYMBOL virtual ~cursor();
};

typedef shared_ptr<cursor> cursor_ptr;
typedef shared_ptr<cursor const> const_cursor_ptr;
}
}

#endif
