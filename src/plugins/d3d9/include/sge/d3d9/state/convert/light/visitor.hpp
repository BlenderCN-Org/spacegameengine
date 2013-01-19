/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_D3D9_STATE_CONVERT_LIGHT_VISITOR_HPP_INCLUDED
#define SGE_D3D9_STATE_CONVERT_LIGHT_VISITOR_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/renderer/state/ffp/lighting/light/directional_fwd.hpp>
#include <sge/renderer/state/ffp/lighting/light/point_fwd.hpp>
#include <sge/renderer/state/ffp/lighting/light/spot_fwd.hpp>
#include <fcppt/nonassignable.hpp>


namespace sge
{
namespace d3d9
{
namespace state
{
namespace convert
{
namespace light
{

class visitor
{
	FCPPT_NONASSIGNABLE(
		visitor
	);
public:
	explicit
	visitor(
		D3DLIGHT9 &
	);

	typedef void result_type;

	result_type const
	operator()(
		sge::renderer::state::ffp::lighting::light::directional const &
	) const;

	result_type const
	operator()(
		sge::renderer::state::ffp::lighting::light::point const &
	) const;

	result_type const
	operator()(
		sge::renderer::state::ffp::lighting::light::spot const &
	) const;
private:
	D3DLIGHT9 &object_;
};

}
}
}
}
}

#endif
