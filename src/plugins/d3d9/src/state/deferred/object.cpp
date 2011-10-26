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


#include <sge/d3d9/state/deferred/apply.hpp>
#include <sge/d3d9/state/deferred/object.hpp>


sge::d3d9::state::deferred::object::object(
	IDirect3DDevice9 *const _device
)
:
	device_(_device),
	set_()
{
}

sge::d3d9::state::deferred::object::~object()
{
}

void
sge::d3d9::state::deferred::object::add(
	deferred::bundle::type const _bundle
)
{
	set_.insert(
		_bundle
	);
}

void
sge::d3d9::state::deferred::object::update(
	sge::renderer::state::list const &_states
)
{
	for(
		bundle_set::const_iterator it(
			set_.begin()
		);
		it != set_.end();
		++it
	)
		deferred::apply(
			device_,
			*it,
			_states
		);
}
