#include <sge/gui/layout.hpp>
#include <sge/gui/widget.hpp>
#include <sge/gui/manager.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>

sge::gui::layout::layout()
:
	w(0)
{
}

void sge::gui::layout::invalidate(
	widget &)
{
	if (connected_widget().has_parent())
		connected_widget().parent_widget().invalidate(
			connected_widget());
	else
		connected_widget().parent_manager().invalidate(
			connected_widget());
}

sge::gui::widget &
sge::gui::layout::connected_widget()
{
	return *w;
}

sge::gui::widget const &
sge::gui::layout::connected_widget() const
{
	return *w;
}

sge::gui::layout::~layout()
{}

void sge::gui::layout::set_widget_size(
	widget &w,
	dim const &d)
{
	w.set_size_raw(d);
}

void sge::gui::layout::set_widget_pos(
	widget &w,
	point const &d)
{
	w.set_pos_raw(d);
}

void sge::gui::layout::compile_widget(widget &w)
{
	w.compile();
}

void sge::gui::layout::connected_widget(widget &_w)
{
	if (w)
		throw exception(SGE_TEXT("registered connected widget twice"));
	
	w = &_w;
}
