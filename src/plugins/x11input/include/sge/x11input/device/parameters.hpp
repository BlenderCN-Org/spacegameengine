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


#ifndef SGE_X11INPUT_DEVICE_PARAMETERS_HPP_INCLUDED
#define SGE_X11INPUT_DEVICE_PARAMETERS_HPP_INCLUDED

#include <sge/x11input/create_parameters_fwd.hpp>
#include <sge/x11input/device/id.hpp>
#include <sge/x11input/device/parameters_fwd.hpp>
#include <sge/x11input/device/raw_demuxer_fwd.hpp>
#include <sge/x11input/device/window_demuxer_fwd.hpp>
#include <awl/backends/x11/system/event/opcode.hpp>
#include <awl/backends/x11/window/instance_fwd.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace x11input
{
namespace device
{

class parameters
{
	FCPPT_NONASSIGNABLE(
		parameters
	);
public:
	parameters(
		x11input::create_parameters const &,
		awl::backends::x11::system::event::opcode,
		awl::backends::x11::window::instance const &,
		x11input::device::window_demuxer &,
		x11input::device::raw_demuxer &
	);

	x11input::device::id const
	id() const;

	XIDeviceInfo const &
	info() const;

	awl::backends::x11::system::event::opcode const
	opcode() const;

	awl::backends::x11::window::instance const &
	window() const;

	x11input::device::window_demuxer &
	window_demuxer() const;

	x11input::device::raw_demuxer &
	raw_demuxer() const;
private:
	x11input::device::id const id_;

	XIDeviceInfo const &info_;

	awl::backends::x11::system::event::opcode const opcode_;

	awl::backends::x11::window::instance const &window_;

	x11input::device::window_demuxer &window_demuxer_;

	x11input::device::raw_demuxer &raw_demuxer_;
};

}
}
}

#endif
