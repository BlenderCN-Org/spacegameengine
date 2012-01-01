/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SRC_RENDERER_STATE_INSTANTIATE_EXTRACT_TRAMPOLINE_HPP_INCLUDED
#define SGE_SRC_RENDERER_STATE_INSTANTIATE_EXTRACT_TRAMPOLINE_HPP_INCLUDED

#include <sge/renderer/state/list_fwd.hpp>
#include <sge/renderer/state/trampoline_fwd.hpp>
#include <sge/src/renderer/state/extract_trampoline_impl.hpp>
#include <fcppt/export_symbol.hpp>


#define SGE_RENDERER_STATE_INSTANTIATE_EXTRACT_TRAMPOLINE(\
	_state\
)\
template FCPPT_EXPORT_SYMBOL \
sge::renderer::state::_state::base_type \
sge::renderer::state::extract_trampoline(\
	sge::renderer::state::list const &,\
	sge::renderer::state::trampoline<\
		_state::base_type,\
		_state::available_states::type\
	> const &\
);

#endif
