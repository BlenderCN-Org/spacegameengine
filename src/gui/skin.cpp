#include "utility/type_comparator.hpp"
#include "utility/blit.hpp"
#include <sge/gui/skin.hpp>
#include <sge/gui/unit.hpp>
#include <sge/gui/widgets/fwd.hpp>
#include <sge/gui/widgets/edit.hpp>
#include <sge/gui/widgets/label.hpp>
#include <sge/gui/widgets/graphics.hpp>
#include <sge/gui/widgets/backdrop.hpp>
#include <sge/gui/widgets/buttons/text.hpp>
#include <sge/gui/widgets/buttons/image.hpp>
#include <sge/gui/events/fwd.hpp>
#include <sge/gui/events/invalid_area.hpp>
#include <sge/gui/canvas.hpp>
#include <sge/gui/log.hpp>
#include <sge/math/dim/output.hpp>
#include <sge/renderer/make_const_image_view.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/bind.hpp>
#include <typeinfo>

namespace
{
sge::gui::logger mylogger(
	sge::gui::global_log(),
	SGE_TEXT("skin"),
	false);
}

namespace
{
class call_draw
{
	public:
	typedef void result_type;

	call_draw(
		sge::gui::skin &s,
		sge::gui::events::invalid_area const &e) 
		: s(s),
		  e(e) {}

	template<typename V>
	void operator()(V &v) { s.draw(v,e); }

	void value() const {}
	private:
	sge::gui::skin &s;
	sge::gui::events::invalid_area const &e;
};

class call_size_hint
{
	public:
	typedef sge::gui::dim result_type;

	call_size_hint(sge::gui::skin const &s) : s(s) {}

	template<typename V>
	void operator()(V const &v) 
	{ 
		sh = s.size_hint(v); 
	}

	sge::gui::dim const value() const { return sh; }
	private:
	sge::gui::skin const &s;
	sge::gui::dim sh;
};
}

SGE_GUI_SKIN_DRAW_RETURN(widget) sge::gui::skin::draw(
	SGE_GUI_SKIN_DRAW_PARAMS_NAMED(widget))
{
	if (typeid(w) == typeid(widget))
	{
		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("draw called for widget, falling back"));
		fallback(
			w,
			e);
		return;
	}

	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("draw called for some other widget"));

	utility::type_comparator<widgets::types>(
		w,
		call_draw(
			*this,
			e),
		boost::bind(
			&skin::default_handler,
			this,
			_1,
			boost::ref(e)));
}

SGE_GUI_SKIN_SIZE_RETURN(widget) sge::gui::skin::size_hint(
	SGE_GUI_SKIN_SIZE_PARAMS_NAMED(widget)) const
{
	if (typeid(w) == typeid(widget))
	{
		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("size_hint called for widget, returning null"));
		return dim::null();
	}

	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("size_hint called for widget ") 
		        << typeid(w).name());

	return utility::type_comparator<widgets::types>(
		w,
		call_size_hint(*this),
		boost::bind(&skin::default_hint_handler,this,_1));
}

SGE_GUI_SKIN_DRAW_RETURN(widget) sge::gui::skin::default_handler(
	SGE_GUI_SKIN_DRAW_PARAMS(widget))
{
	throw exception(SGE_TEXT("tried to draw a widget whose type is not drawable"));
}

SGE_GUI_SKIN_SIZE_RETURN(widget) sge::gui::skin::default_hint_handler(
	SGE_GUI_SKIN_SIZE_PARAMS(widget)) const
{
	throw exception(SGE_TEXT("tried to hint a widget whose type is not drawable"));
}
	
sge::gui::skin::~skin()
{}

void sge::gui::skin::resize_buffer(widget const &b)
{
	// resize internal buffer if neccessary
	if (b.buffer().width() != static_cast<image::coord_t>(b.size().w()) ||
	    b.buffer().height() != static_cast<image::coord_t>(b.size().h()))
	{
		SGE_LOG_DEBUG(
			mylogger,
			log::_1
				<< SGE_TEXT("resizing from ") 
				<< dim(
					static_cast<unit>(b.buffer().width()),
					static_cast<unit>(b.buffer().height()))
				<< SGE_TEXT(" to ")
				<< b.size());
		b.buffer() = image(
			static_cast<image::coord_t>(b.size().w()),
			static_cast<image::coord_t>(b.size().h()));
	}
}

void sge::gui::skin::blit_invalid(
	widget const &w,
	canvas::object &c,
	events::invalid_area const &e,
	bool const t)
{
	utility::blit_invalid(
		renderer::make_const_image_view(c.view()),
		rect(w.absolute_pos(),c.size()),
		e.texture(),
		e.area(),
		t);
}
