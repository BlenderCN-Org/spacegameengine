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


#ifndef SGE_D3D9_VF_CONVERT_INDEX_VISITOR_HPP_INCLUDED
#define SGE_D3D9_VF_CONVERT_INDEX_VISITOR_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/vf/texture_coordinate_count.hpp>
#include <sge/renderer/vf/dynamic/color_fwd.hpp>
#include <sge/renderer/vf/dynamic/extra_fwd.hpp>
#include <sge/renderer/vf/dynamic/normal_fwd.hpp>
#include <sge/renderer/vf/dynamic/pos_fwd.hpp>
#include <sge/renderer/vf/dynamic/texpos_fwd.hpp>


namespace sge
{
namespace d3d9
{
namespace vf
{
namespace convert
{

class index_visitor
{
public:
	explicit
	index_visitor(
		sge::d3d9::vf::texture_coordinate_count
	);

	typedef BYTE result_type;

	result_type
	operator()(
		sge::renderer::vf::dynamic::pos const &
	) const;

	result_type
	operator()(
		sge::renderer::vf::dynamic::normal const &
	) const;

	result_type
	operator()(
		sge::renderer::vf::dynamic::color const &
	) const;

	result_type
	operator()(
		sge::renderer::vf::dynamic::texpos const &
	) const;

	result_type
	operator()(
		sge::renderer::vf::dynamic::extra const &
	) const;
private:
	sge::d3d9::vf::texture_coordinate_count texture_coordinates_;
};

}
}
}
}

#endif
