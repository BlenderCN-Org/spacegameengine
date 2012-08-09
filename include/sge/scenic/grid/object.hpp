#ifndef SGE_SCENIC_GRID_OBJECT_HPP_INCLUDED
#define SGE_SCENIC_GRID_OBJECT_HPP_INCLUDED

#include <sge/camera/base_fwd.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/line_drawer/object.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/context/object_fwd.hpp>
#include <sge/scenic/symbol.hpp>
#include <sge/scenic/grid/depth_test.hpp>
#include <sge/scenic/grid/distance_to_origin.hpp>
#include <sge/scenic/grid/orientation.hpp>
#include <sge/scenic/grid/rect.hpp>
#include <sge/scenic/grid/spacing.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace scenic
{
namespace grid
{
class object
{
FCPPT_NONCOPYABLE(
	object);
public:
	SGE_SCENIC_SYMBOL
	object(
		sge::renderer::device &,
		sge::camera::base const &,
		sge::scenic::grid::orientation::type,
		sge::scenic::grid::rect const &,
		sge::scenic::grid::spacing const &,
		sge::scenic::grid::distance_to_origin const &,
		sge::image::color::any::object const &);

	SGE_SCENIC_SYMBOL
	void
	render(
		sge::renderer::context::object &,
		sge::scenic::grid::depth_test const &);

	SGE_SCENIC_SYMBOL
	~object();
private:
	sge::camera::base const &camera_;
	sge::line_drawer::object line_drawer_;
};
}
}
}

#endif
