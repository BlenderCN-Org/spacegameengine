/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_D3D9_SYSTEM_HPP_INCLUDED
#define SGE_D3D9_SYSTEM_HPP_INCLUDED

#include <sge/d3d9/d3d_unique_ptr.hpp>
#include <sge/d3d9/d3dinclude.hpp>
#include <sge/renderer/system.hpp>
#include <sge/renderer/caps/device_count.hpp>
#include <sge/renderer/caps/device_fwd.hpp>
#include <sge/renderer/device/core_unique_ptr.hpp>
#include <sge/renderer/device/ffp_unique_ptr.hpp>
#include <sge/renderer/device/index.hpp>
#include <sge/renderer/device/parameters_fwd.hpp>
#include <sge/renderer/display_mode/container.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <fcppt/int_range_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace d3d9
{

class system
:
	public sge::renderer::system
{
	FCPPT_NONCOPYABLE(
		system
	);
public:
	system();

	~system()
	override;
private:
	sge::renderer::device::core_unique_ptr
	create_core_renderer(
		sge::renderer::device::parameters const &
	)
	override;

	sge::renderer::device::ffp_unique_ptr
	create_ffp_renderer(
		sge::renderer::device::parameters const &
	)
	override;

	awl::visual::object_unique_ptr
	create_visual(
		sge::renderer::pixel_format::object const &
	)
	override;

	sge::renderer::caps::device_count
	device_count() const
	override;

	sge::renderer::caps::device const &
	device_caps(
		sge::renderer::device::index
	) const
	override;

	sge::renderer::display_mode::container
	display_modes(
		sge::renderer::device::index
	) const
	override;

	typedef
	fcppt::int_range<
		UINT
	>
	device_index_range;

	device_index_range
	adapter_range() const;

	sge::d3d9::d3d_unique_ptr const system_;

	typedef
	std::vector<
		sge::renderer::caps::device
	>
	caps_vector;

	caps_vector const caps_;

	typedef
	std::vector<
		sge::renderer::display_mode::container
	>
	display_mode_container_vector;

	display_mode_container_vector const display_modes_;
};

}
}

#endif
