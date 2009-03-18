#include "../../utility/ptr_find.hpp"
#include <sge/gui/detail/managers/keyboard.hpp>
#include <sge/gui/events/key.hpp>
#include <sge/gui/events/keyboard_enter.hpp>
#include <sge/gui/events/keyboard_leave.hpp>
#include <sge/gui/widget.hpp>
#include <sge/gui/log.hpp>
#include <sge/assert.hpp>
#include <sge/exception.hpp>
#include <sge/input/system.hpp>
#include <sge/input/key_type.hpp>
#include <sge/input/classification.hpp>
#include <sge/input/key_pair.hpp>
#include <boost/next_prior.hpp>
#include <boost/bind.hpp>
#include <algorithm>

namespace
{
sge::gui::logger mylogger(
	sge::gui::global_log(),
	SGE_TEXT("managers: keyboard"),
	false);

bool active(sge::gui::widget const &w)
{
	switch (w.activation())
	{
		case sge::gui::activation_state::active:
			if (!w.has_parent())
				return true;
			return active(w.parent_widget());
		case sge::gui::activation_state::inactive:
			return false;
	}
	throw sge::exception(SGE_TEXT("missed an activation state"));
}
}

sge::gui::detail::managers::keyboard::keyboard(sge::input::system_ptr const is)
	: input_filter(is),
	  ic(
	     input_filter.register_callback(
			   boost::bind(&keyboard::input_callback,this,_1,_2,false))),
	  irc(
	     input_filter.register_repeat_callback(
			   boost::bind(&keyboard::repeat_callback,this,_1,_2)))
{
}

// Here, we could add a keyboard_enter event to the first added widget, but the function
// below is called from a base class constructor, so widget::process(keyboard_enter)
// is called instead of most_derived::process(keyboard_enter), so the policy is: No 
// widget initially has the focus.
void sge::gui::detail::managers::keyboard::add(widget &w)
{
	/* TODO: think about this
	BOOST_FOREACH(widget &v,w.children())
		add(v);
		*/

	if (w.keyboard_focus() == keyboard_focus::ignore)
		return; 

	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("adding widget"));
	
	SGE_ASSERT(
		utility::ptr_find(widgets.begin(),widgets.end(),&w) 
			== widgets.end());

	widgets.push_back(&w);
}

void sge::gui::detail::managers::keyboard::activation(
	widget &w,
	activation_state::type const a)
{
	if (!focus)
		return;

	if (!w.has_child(**focus) && &(**focus) != &w)
		return;

	if (a == activation_state::active)
		return;
	
	(*focus)->process(events::keyboard_leave());
	focus.reset();
}

void sge::gui::detail::managers::keyboard::request_focus(widget &w)
{
	widget_container::iterator wi = utility::ptr_find(
			widgets.begin(),
			widgets.end(),&w);
	
	SGE_ASSERT_MESSAGE(
		wi != widgets.end(),
		SGE_TEXT("a widget requested the keyboard focus which cannot receive keys"));
	
	// Widget already has the focus?
	if (focus && *focus == wi)
		return;
	
	switch_focus(wi);
}

void sge::gui::detail::managers::keyboard::remove(widget &w)
{
	if (w.keyboard_focus() == keyboard_focus::ignore)
		return;
	
	widget_container::iterator wi = utility::ptr_find(
			widgets.begin(),
			widgets.end(),&w);
	
	SGE_ASSERT(wi != widgets.end());
	
	// the widget to delete has the focus? then reset focus
	if (focus && *focus == wi)
		focus.reset();
/* old (alternative) behaviour was to take the next possible widget
		switch_focus(
			boost::next(*focus) == widgets.end() 
				? widgets.begin()
				: boost::next(*focus));
				*/
	
	widgets.erase(wi);
}

void sge::gui::detail::managers::keyboard::cycle_focus()
{
	if (widgets.empty())
		return;
	
	// If no widget currently has the focus, take the first (active) one on the
	// list
	if (!focus)
	{
		for (widget_container::iterator i = widgets.begin(); 
		     i != widgets.end(); 
				 ++i) 
		{
			if (active(*i))
			{
				switch_focus(i);
				break;
			}
		}
		return;
	}

	SGE_ASSERT((*focus)->activation() == activation_state::active);

	widget_container::iterator next = boost::next(*focus);
	if (next == widgets.end())
		next = widgets.begin();

	while (!active(*next))
	{
		++next;
		if (next == widgets.end())
			next = widgets.begin();
	}

	switch_focus(next);
}


// This is called by manager whenever a widget changes its behaviour towards the
// keyboard focus. If a widget decides not to accept the focus anymore, we have to
// delete it and possibly nominate a new focused widget
void sge::gui::detail::managers::keyboard::keyboard_focus(
	widget &w,
	keyboard_focus::type const n)
{
	switch (n)
	{
		case keyboard_focus::ignore:
		{
			widget_container::iterator wi = utility::ptr_find(
					widgets.begin(),
					widgets.end(),&w);
			
			// The widget ignores keyboard focus and it never accepted it?
			// then we can return
			if (wi == widgets.end())
				return;
			
			// The widget to delete has the focus? then take the next one
			if (focus && *focus == wi)
			{
				// ...if there is a next one
				if (widgets.size() != 1)
				{
					switch_focus(
						boost::next(*focus) == widgets.end() 
							? widgets.begin()
							: boost::next(*focus));
				}
			}
			
			widgets.erase(wi);
		}
		break;
		case keyboard_focus::receive:
		{
			SGE_LOG_DEBUG(
				mylogger,
				log::_1 << SGE_TEXT("adding widget after focus change"));
			widget_container::iterator wi = utility::ptr_find(
					widgets.begin(),
					widgets.end(),&w);

			// The widget has the focus and has had it before? Then 
			// there's nothing to do
			if (wi != widgets.end())
				return;

			add(w);
		}
		break;
	}
}

void sge::gui::detail::managers::keyboard::repeat_callback(
	input::key_type const &k,
	input::modifier::states const &s)
{
	input_callback(
		input::key_pair(
			k,
			static_cast<input::key_state>(1)),
		s,
		true);
}

void sge::gui::detail::managers::keyboard::input_callback(
	input::key_pair const &k,
	input::modifier::states const &s,
	bool const repeated)
{
	if (widgets.empty())
		return;
	
	if (input::is_mouse_axis(k.key().code()) || input::is_mouse_button(k.key().code()))
		return;
	
	if (focus)
	{
		if ((*focus)->process(events::key(k,s,repeated)) == key_handling::ignore)
			return;
	}

	if (k.key().code() == sge::input::kc::key_tab)
	{
		if (!sge::math::almost_zero(k.value()))
			cycle_focus();
		return;
	}
}

void sge::gui::detail::managers::keyboard::switch_focus(widget_container::iterator n)
{
	SGE_LOG_DEBUG(mylogger,log::_1 << SGE_TEXT("switching focus"));
	if (focus)
		(*focus)->process(events::keyboard_leave());
	focus.reset(n);
	(*focus)->process(events::keyboard_enter());
}
