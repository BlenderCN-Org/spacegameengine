/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SYSTEMS_WRAPPED_WINDOW_HPP_INCLUDED
#define SGE_SYSTEMS_WRAPPED_WINDOW_HPP_INCLUDED

#include <sge/systems/symbol.hpp>
#include <sge/systems/wrapped_window_fwd.hpp>
#include <awl/event/processor_fwd.hpp>
#include <awl/system/object_fwd.hpp>
#include <awl/system/event/processor_fwd.hpp>
#include <awl/window/object_fwd.hpp>
#include <awl/window/event/processor_fwd.hpp>
#include <fcppt/nonassignable.hpp>


namespace sge
{
namespace systems
{

class wrapped_window
{
	FCPPT_NONASSIGNABLE(
		wrapped_window
	);
public:
	SGE_SYSTEMS_SYMBOL
	wrapped_window(
		awl::system::object &,
		awl::system::event::processor &,
		awl::event::processor &,
		awl::window::object &,
		awl::window::event::processor &
	);

	awl::system::object &
	awl_system() const;

	awl::system::event::processor &
	awl_system_event_processor() const;

	awl::event::processor &
	awl_event_processor() const;

	awl::window::object &
	awl_window() const;

	awl::window::event::processor &
	awl_window_event_processor() const;
private:
	awl::system::object &awl_system_;

	awl::system::event::processor &awl_system_event_processor_;

	awl::event::processor &awl_event_processor_;

	awl::window::object &awl_window_;

	awl::window::event::processor &awl_window_event_processor_;
};

}
}

#endif
