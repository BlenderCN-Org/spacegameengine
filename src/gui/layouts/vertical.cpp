#include <sge/gui/layouts/vertical.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/math/vector/basic_impl.hpp>

sge::gui::layouts::vertical::vertical()
	: row()
{
}

sge::gui::dim::reference sge::gui::layouts::vertical::master(
	dim &d) const
{
	return d.h();
}

sge::gui::dim::const_reference sge::gui::layouts::vertical::master(
	dim const &d) const
{
	return d.h();
}

sge::gui::point::reference sge::gui::layouts::vertical::master(
	point &d) const
{
	return d.y();
}

sge::gui::point::const_reference sge::gui::layouts::vertical::master(
	point const &d) const
{
	return d.y();
}
