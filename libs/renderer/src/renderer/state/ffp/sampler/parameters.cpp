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


#include <sge/renderer/state/ffp/sampler/alpha_op.hpp>
#include <sge/renderer/state/ffp/sampler/color_op.hpp>
#include <sge/renderer/state/ffp/sampler/parameters.hpp>


sge::renderer::state::ffp::sampler::parameters::parameters(
	sge::renderer::state::ffp::sampler::color_op const _color_op,
	sge::renderer::state::ffp::sampler::alpha_op const _alpha_op
)
:
	color_op_(
		_color_op
	),
	alpha_op_(
		_alpha_op
	)
{
}

sge::renderer::state::ffp::sampler::color_op
sge::renderer::state::ffp::sampler::parameters::color_op() const
{
	return
		color_op_;
}

sge::renderer::state::ffp::sampler::alpha_op
sge::renderer::state::ffp::sampler::parameters::alpha_op() const
{
	return
		alpha_op_;
}
