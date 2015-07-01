#ifndef SGE_GUI_STYLE_BASE_HPP_INCLUDED
#define SGE_GUI_STYLE_BASE_HPP_INCLUDED

#include <sge/gui/fill_color_fwd.hpp>
#include <sge/gui/fill_level_fwd.hpp>
#include <sge/gui/detail/symbol.hpp>
#include <sge/gui/text_color_fwd.hpp>
#include <sge/gui/renderer/base_fwd.hpp>
#include <sge/gui/style/base_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/axis_fwd.hpp>
#include <sge/rucksack/dim_fwd.hpp>
#include <sge/rucksack/padding_fwd.hpp>
#include <sge/rucksack/rect_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace gui
{
namespace style
{

class base
{
	FCPPT_NONCOPYABLE(
		base
	);
protected:
	SGE_GUI_DETAIL_SYMBOL
	base();
public:
	SGE_GUI_DETAIL_SYMBOL
	virtual
	~base() = 0;

	virtual
	sge::rucksack::dim const
	button_spacing() const = 0;

	virtual
	void
	draw_button(
		sge::gui::renderer::base &,
		sge::renderer::context::ffp &,
		sge::rucksack::rect
	) const = 0;

	virtual
	void
	draw_bar(
		sge::gui::renderer::base &,
		sge::renderer::context::ffp &,
		sge::rucksack::rect,
		sge::rucksack::axis,
		sge::gui::fill_level,
		sge::gui::fill_color const &
	) const = 0;

	virtual
	sge::rucksack::padding const
	frame_padding() const = 0;

	virtual
	void
	draw_frame(
		sge::gui::renderer::base &,
		sge::renderer::context::ffp &,
		sge::rucksack::rect,
		sge::rucksack::padding
	) const = 0;

	virtual
	sge::rucksack::dim const
	edit_spacing() const = 0;

	virtual
	void
	draw_edit(
		sge::gui::renderer::base &,
		sge::renderer::context::ffp &,
		sge::rucksack::rect
	) const = 0;

	virtual
	sge::rucksack::dim const
	image_spacing() const = 0;

	virtual
	void
	draw_image(
		sge::gui::renderer::base &,
		sge::renderer::context::ffp &,
		sge::rucksack::rect
	) const = 0;

	virtual
	sge::rucksack::dim const
	text_spacing() const = 0;

	virtual
	void
	draw_text(
		sge::gui::renderer::base &,
		sge::renderer::context::ffp &,
		sge::rucksack::rect
	) const = 0;

	virtual
	sge::gui::text_color
	text_color() const = 0;
};

}
}
}

#endif
