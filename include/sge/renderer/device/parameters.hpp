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


#ifndef SGE_RENDERER_DEVICE_PARAMETERS_HPP_INCLUDED
#define SGE_RENDERER_DEVICE_PARAMETERS_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/device/parameters_fwd.hpp>
#include <sge/renderer/display_mode/parameters.hpp>
#include <awl/window/object_fwd.hpp>
#include <fcppt/nonassignable.hpp>


namespace sge
{
namespace renderer
{
namespace device
{

class parameters
{
	FCPPT_NONASSIGNABLE(
		parameters
	);
public:
	SGE_RENDERER_DETAIL_SYMBOL
	parameters(
		sge::renderer::display_mode::parameters const &,
		awl::window::object &
	);

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::display_mode::parameters const &
	display_mode() const;

	SGE_RENDERER_DETAIL_SYMBOL
	awl::window::object &
	window() const;
private:
	sge::renderer::display_mode::parameters const display_mode_;

	awl::window::object &window_;
};

}
}
}

#endif
