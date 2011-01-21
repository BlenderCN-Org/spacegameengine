/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_DINPUT_DEVICE_HPP_INCLUDED
#define SGE_DINPUT_DEVICE_HPP_INCLUDED

#include "device_fwd.hpp"
#include "device_parameters_fwd.hpp"
#include "di.hpp"
#include "dinput_device_ptr.hpp"
#include <fcppt/container/array.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/string.hpp>
#include <cstddef>

namespace sge
{
namespace dinput
{

class device
{
	FCPPT_NONCOPYABLE(
		device
	)
public:
	virtual void
	dispatch() = 0;

	virtual ~device();

	static std::size_t const buffer_size = 1024;

	bool
	acquire();

	void
	unacquire();
protected:
	explicit device(
		dinput::device_parameters const &
	);

	void
	poll();
	
	void
	set_data_format(
		LPCDIDATAFORMAT
	);

	void
	set_property(
		REFGUID,
		LPCDIPROPHEADER
	);

	typedef fcppt::container::array<
		DIDEVICEOBJECTDATA,
		buffer_size
	> input_buffer;

	bool
	get_input(
		input_buffer &,
		DWORD &elements
	);

	void
	enum_objects(
		LPDIENUMDEVICEOBJECTSCALLBACK
	);

	fcppt::string const &
	name() const;
private:
	void
	set_cooperative_level(
		HWND,
		DWORD flags
	);

	fcppt::string const name_;

	dinput::dinput_device_ptr device_;
};

}
}

#endif
