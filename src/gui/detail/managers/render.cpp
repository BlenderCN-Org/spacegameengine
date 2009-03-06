#include <sge/gui/detail/managers/render.hpp>
#include <sge/gui/detail/managers/mouse.hpp>
#include <sge/gui/events/invalid_area.hpp>
#include <sge/gui/canvas.hpp>
#include <sge/gui/log.hpp>
#include <sge/gui/widget.hpp>
#include <sge/math/rect_util.hpp>
#include <sge/math/power.hpp>
#include <sge/math/dim/output.hpp>
#include <sge/math/vector/output.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/filter/linear.hpp>
#include <sge/renderer/texture_software.hpp>
#include <sge/renderer/texture_rw.hpp>
#include <sge/renderer/scoped_texture_lock.hpp>
#include <sge/renderer/texture.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/text.hpp>
#include <sge/assert.hpp>
#include <sge/structure_cast.hpp>
#include <boost/foreach.hpp>
#include <algorithm>

namespace
{
sge::gui::logger mylogger(
	sge::gui::global_log(),
	SGE_TEXT("render manager"),
	false);
}

sge::gui::detail::managers::render::dirt::dirt(
	widget &_widget,
	rect const &_rect)
	: widget_(&_widget),
	  rect_(_rect)
{
}

sge::gui::detail::managers::render::render(
	renderer::device_ptr const _rend,
	managers::mouse &_mouse)
	: rend(_rend),
	  ss(rend),
		mouse_(_mouse)
{
}

void sge::gui::detail::managers::render::add(widget &w)
{
	if (!w.parent_widget())
		widgets[&w] = widget_data();
}

void sge::gui::detail::managers::render::activation(
	widget &w,
	activation_state::type const t)
{
	if (w.parent_widget())
		return;
	
	SGE_ASSERT(widgets.find(&w) != widgets.end());

	switch (t)
	{
		case activation_state::active:
			widgets[&w].sprite.visible(true);
		break;
		case activation_state::inactive:
			widgets[&w].sprite.visible(false);
		break;
	}
}

void sge::gui::detail::managers::render::draw()
{
	if (!dirt_.empty())
		clean();

	sprite::container sprites;
	BOOST_FOREACH(widget_container::value_type const &w,widgets)
		sprites.push_back(w.second.sprite);
	sprites.push_back(mouse_.cursor());
	ss.render(sprites.begin(),sprites.end());
}

void sge::gui::detail::managers::render::remove(widget &w)
{
	if (w.parent_widget())
		return;
	
	widget_container::iterator wi = widgets.find(&w);
	SGE_ASSERT(wi != widgets.end());
	widgets.erase(wi);
}

void sge::gui::detail::managers::render::resize(widget &w,dim const &d)
{
	widget_container::iterator wi = widgets.find(&w);
	
	// widget is not a top level widget, so we don't care
	if (wi == widgets.end())
		return;
	
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("resizing widget from ") << w.size() 
		        << SGE_TEXT(" to ") << d);

	widget_data &wd = wi->second;
	
	// check if the current texture is large enough to hold the new widget
	dim const new_dim = 
		dim(
			math::next_pow_2(d.w()),
			math::next_pow_2(d.h()));

	if (!wd.texture || structure_cast<dim>(wd.texture->dim()) == new_dim)
	{
		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("new resolution is ")
			        << new_dim);

		renderer::texture_ptr const software_texture(
			new renderer::texture_software(
				structure_cast<renderer::texture::dim_type>(new_dim),
				renderer::color_format::rgba8));

		renderer::texture_ptr hardware_texture = rend->create_texture(
			structure_cast<renderer::texture::dim_type>(new_dim),
			renderer::color_format::rgba8,
			renderer::filter::linear,
			renderer::resource_flags::dynamic);
		
		// NOTE: the sprite::object has to get a texture convertible to
		// sge::ogl::texture, so we give it hardware_texture below. the sprite_texture
		// serves as a canvas for the widgets and we pass it here
		wd.texture.reset(
			new renderer::texture_rw(
				software_texture,
				hardware_texture));
								
		wd.sprite = sprite::object(
			sprite::point(structure_cast<sprite::point>(w.pos())),
			texture::const_part_ptr(new texture::part_raw(hardware_texture)),
			sprite::dim(structure_cast<sprite::dim>(new_dim)),
			sprite::defaults::color_,
			static_cast<sprite::depth_type>(1));
		
		switch (w.activation())
		{
			case activation_state::active:
				wd.sprite.visible(true);
			break;
			case activation_state::inactive:
				wd.sprite.visible(false);
			break;
		}
	}
	else
	{
		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("resolution suffices, doing nothing"));
	}

	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("adding dirty region ") 
		        << rect(w.pos(),d));
		
	invalidate(
		w,
		rect(
			w.pos(),
			new_dim));
}

void sge::gui::detail::managers::render::reposition(
	widget &w,
	point const &d)
{
	widget_container::iterator wi = widgets.find(&w);
	// widget is not a top level widget
	if (wi == widgets.end())
		return;

	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("repositioning sprite to ") << d);
	// just reset sprite position
	wi->second.sprite.pos() = structure_cast<sprite::point>(d);
}

void sge::gui::detail::managers::render::invalidate(
	widget &w,
	rect const &r)
{
	dirt_.push_back(dirt(w,r));
}

void sge::gui::detail::managers::render::clean()
{
	std::vector<rect> rects;
	BOOST_FOREACH(dirt_container::const_reference d,dirt_)
		rects.push_back(d.rect_);
	// calculate bounding rect of all dirt rects
	rect const bound = math::bounding<unit>(
		rects.begin(),
		rects.end());

	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("bounding rect of all dirty regions is ") << bound);
	dirt_.clear();
	
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("invalidate called for rect ") << bound 
		        << SGE_TEXT(", checking intersections"));

	// if rects intersect, pass event on to top level widgets
	BOOST_FOREACH(widget_container::value_type &p,widgets)
	{
		widget &w = *p.first;
		widget_data &wd = p.second;

		if (!math::intersects(w.absolute_area(),bound))
			continue;

		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("got an intersection with area ") 
							<< w.absolute_area());

		// if it intersects, lock the whole intersection
		rect const widget_area  = w.absolute_area();
		rect const is = math::intersection(widget_area,bound);

		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("intersection is ") << is);

		// we have to convert the global intersection rect to a local one so we
		// can lock the texture
		rect const is_local(
			is.left()-widget_area.left(),
			is.top()-widget_area.top(),
			is.right()-widget_area.left(),
			is.bottom()-widget_area.top());

		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("locking (local) ") << is_local 
							<< SGE_TEXT(" and sending invalid_area event with ")
							<< is
							<< SGE_TEXT(" (global)"));

		renderer::scoped_texture_lock const lock_(
			wd.texture,
			math::structure_cast<renderer::lock_rect>(is_local),
			renderer::lock_flags::readwrite);

		w.process(
			events::invalid_area(
				lock_.value(),
				is));

		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("invalid_area sent, now unlocking"));
	}
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("checking intersections completed"));
}
