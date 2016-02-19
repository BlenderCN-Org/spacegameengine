/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_X11INPUT_DEVICE_MANAGER_OBJECT_HPP_INCLUDED
#define SGE_X11INPUT_DEVICE_MANAGER_OBJECT_HPP_INCLUDED

#include <sge/x11input/device/id.hpp>
#include <sge/x11input/device/use.hpp>
#include <sge/x11input/device/manager/config_map.hpp>
#include <awl/backends/x11/display_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <map>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace x11input
{
namespace device
{
namespace manager
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	object(
		awl::backends::x11::display &,
		sge::x11input::device::manager::config_map &&
	);

	~object();

	void
	initial(
		XIDeviceInfo const &
	);

	void
	change(
		XIHierarchyInfo const &
	);

	void
	dispatch_initial();
private:
	template<
		typename Function
	>
	bool
	update(
		x11input::device::use,
		Function const &
	);

	awl::backends::x11::display &display_;

	x11input::device::manager::config_map const config_;

	typedef std::map<
		sge::x11input::device::id,
		sge::x11input::device::use
	> use_map;

	use_map uses_;
};

}
}
}
}

#endif
