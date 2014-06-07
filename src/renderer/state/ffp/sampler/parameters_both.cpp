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


#include <sge/renderer/state/ffp/sampler/alpha_op.hpp>
#include <sge/renderer/state/ffp/sampler/color_op.hpp>
#include <sge/renderer/state/ffp/sampler/op.hpp>
#include <sge/renderer/state/ffp/sampler/parameters.hpp>
#include <sge/renderer/state/ffp/sampler/parameters_both.hpp>


sge::renderer::state::ffp::sampler::parameters const
sge::renderer::state::ffp::sampler::parameters_both(
	sge::renderer::state::ffp::sampler::op const &_op
)
{
	return
		sge::renderer::state::ffp::sampler::parameters(
			sge::renderer::state::ffp::sampler::color_op(
				_op
			),
			sge::renderer::state::ffp::sampler::alpha_op(
				_op
			)
		);
}
