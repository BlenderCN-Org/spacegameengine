/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_WINDOW_OBJECT_HPP_INCLUDED
#define SGE_WINDOW_OBJECT_HPP_INCLUDED

#include <sge/window/dim_fwd.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/window/detail/symbol.hpp>
#include <awl/event/processor_fwd.hpp>
#include <awl/event/scoped_window_processor.hpp>
#include <awl/window/object_fwd.hpp>
#include <awl/window/event/processor_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace window
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	SGE_WINDOW_DETAIL_SYMBOL
	object(
		awl::window::object &,
		awl::window::event::processor &,
		awl::event::processor &
	);

	SGE_WINDOW_DETAIL_SYMBOL
	~object();

	SGE_WINDOW_DETAIL_SYMBOL
	sge::window::dim const
	size() const;

	SGE_WINDOW_DETAIL_SYMBOL
	void
	show();

	SGE_WINDOW_DETAIL_SYMBOL
	awl::window::object &
	awl_object() const;

	SGE_WINDOW_DETAIL_SYMBOL
	awl::window::event::processor &
	awl_window_event_processor() const;
private:
	awl::window::object &awl_object_;

	awl::window::event::processor &awl_window_processor_;

	awl::event::scoped_window_processor const attachment_;
};

}
}

#endif
