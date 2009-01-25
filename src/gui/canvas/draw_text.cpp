#include "log.hpp"
#include <sge/gui/canvas.hpp>
#include <sge/gui/canvas/font_drawer.hpp>
#include <sge/font/font.hpp>
#include <sge/font/text_size_t.hpp>
#include <sge/assert.hpp>
#include <sge/text.hpp>
#include <algorithm>

void sge::gui::canvas::object::draw_text(
	font::metrics_ptr const metrics,
	color const c,
	string const &text,
	point const &pos,
	dim const &max_size,
	font::align_h::type const h,
	font::align_v::type const v,
	font::flag_t const f,
	boost::optional<string::size_type> cp,
	point *const p)
{
	SGE_ASSERT(!cp || *cp < text.length());

	// determine which invisible characters have to be filtered
	if (cp)
	{
		string::size_type const filter = 
			std::count(
				text.begin(),
				text.begin()+(*cp)+1,
				SGE_TEXT('\n'));
		
		cp = (*cp) - filter;
	}

	font::font(
		metrics,
		font::drawer_ptr(
			new font_drawer(view_,c,cp,p))
	).draw_text(
		text,
		pos,
		max_size,
		h,
		v,
		f);
}
