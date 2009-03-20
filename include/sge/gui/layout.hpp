#ifndef SGE_GUI_LAYOUT_HPP_INCLUDED
#define SGE_GUI_LAYOUT_HPP_INCLUDED

#include <sge/gui/widget_fwd.hpp>
#include <sge/gui/layout_fwd.hpp>
#include <sge/gui/point.hpp>
#include <sge/gui/dim.hpp>
#include <sge/export.hpp>

namespace sge
{
namespace gui
{
class SGE_CLASS_SYMBOL layout
{
	public:
	SGE_SYMBOL layout(widget &);

	virtual void update() = 0;
	virtual void pos(point const &) = 0;
	virtual void size(dim const &) = 0;
	virtual dim const size_hint() const = 0;

	widget &connected_widget() { return w; }
	widget const &connected_widget() const { return w; }

	virtual ~layout() {}
	protected:
	void set_widget_size(widget &,dim const &);
	void set_widget_pos(widget &,point const &);
	void compile_widget(widget &);

	private:
	widget &w;
};

}
}

#endif
