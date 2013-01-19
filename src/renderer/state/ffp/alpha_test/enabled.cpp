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


#include <sge/renderer/state/ffp/alpha_test/enabled.hpp>
#include <sge/renderer/state/ffp/alpha_test/func.hpp>
#include <sge/renderer/state/ffp/alpha_test/ref.hpp>


sge::renderer::state::ffp::alpha_test::enabled::enabled(
	sge::renderer::state::ffp::alpha_test::func const _func,
	sge::renderer::state::ffp::alpha_test::ref const _ref
)
:
	func_(
		_func
	),
	ref_(
		_ref
	)
{
}

sge::renderer::state::ffp::alpha_test::func
sge::renderer::state::ffp::alpha_test::enabled::func() const
{
	return func_;
}

sge::renderer::state::ffp::alpha_test::ref const
sge::renderer::state::ffp::alpha_test::enabled::ref() const
{
	return ref_;
}
