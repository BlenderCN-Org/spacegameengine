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


#ifndef SGE_D3D9_STATE_CONVERT_SAMPLER_ARG_TYPE_HPP_INCLUDED
#define SGE_D3D9_STATE_CONVERT_SAMPLER_ARG_TYPE_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/renderer/state/ffp/sampler/alpha_op_fwd.hpp>
#include <sge/renderer/state/ffp/sampler/color_op_fwd.hpp>


namespace sge
{
namespace d3d9
{
namespace state
{
namespace convert
{

template<
	typename OpType,
	typename Arg
>
struct sampler_arg_type;

template<
	typename Arg
>
struct sampler_arg_type<
	sge::renderer::state::ffp::sampler::alpha_op,
	Arg
>
{
	static
	D3DTEXTURESTAGESTATETYPE
	get();
};

template<
	typename Arg
>
struct sampler_arg_type<
	sge::renderer::state::ffp::sampler::color_op,
	Arg
>
{
	static
	D3DTEXTURESTAGESTATETYPE
	get();
};

}
}
}
}

#endif
