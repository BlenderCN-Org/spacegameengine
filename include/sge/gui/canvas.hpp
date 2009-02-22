#ifndef SGE_GUI_CANVAS_HPP_INCLUDED
#define SGE_GUI_CANVAS_HPP_INCLUDED

#include <sge/gui/types.hpp>
#include <sge/gui/widget.hpp>
#include <sge/gui/canvas/rect_type.hpp>
#include <sge/gui/canvas/line_type.hpp>
#include <sge/gui/canvas/strip_type.hpp>
#include <sge/export.hpp>
#include <sge/font/metrics_fwd.hpp>
#include <sge/font/align_h.hpp>
#include <sge/font/align_v.hpp>
#include <sge/font/flags.hpp>
#include <sge/renderer/image_view.hpp>

#include <boost/optional.hpp>

#include <vector>

namespace sge
{
namespace gui
{
namespace canvas
{
class SGE_CLASS_SYMBOL object
{
	public:
	SGE_SYMBOL explicit object(image &);
	SGE_SYMBOL ~object();

	SGE_SYMBOL dim const size() const;
	SGE_SYMBOL rect const area() const;
	SGE_SYMBOL image_view &view();
	SGE_SYMBOL const_image_view const view() const;

	SGE_SYMBOL void draw_rect(
		rect const &,
		color,
		rect_type::type);

	SGE_SYMBOL void draw_text(
		font::metrics_ptr,
		color,
		string const &,
		point const &,
		dim const &max_size,
		font::align_h::type,
		font::align_v::type,
		font::flag_t = font::flags::default_,
		boost::optional<string::size_type> character_pos = boost::none,
		point * = 0);

	SGE_SYMBOL void draw_line(
		point const &,
		point const &,
		color,
		line_type::type type = line_type::solid);

	typedef std::vector<point> point_container;

	SGE_SYMBOL void draw_line_strip(
		point_container const &,
		color,
		line_type::type = line_type::solid,
		strip_type::type = strip_type::open);

	SGE_SYMBOL void draw_pixel(point const &,color);
	private:
	image &texture_;
	image_view view_;
	font::metrics_ptr metrics;
};
}
}
}

#endif
