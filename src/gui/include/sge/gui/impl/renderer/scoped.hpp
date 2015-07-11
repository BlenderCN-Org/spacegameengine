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


#ifndef SGE_GUI_IMPL_RENDERER_SCOPED_HPP_INCLUDED
#define SGE_GUI_IMPL_RENDERER_SCOPED_HPP_INCLUDED

#include <sge/gui/impl/renderer/stateless.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/sprite/state/all_choices.hpp>
#include <sge/sprite/state/object_decl.hpp>
#include <sge/sprite/state/scoped_decl.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace gui
{
namespace impl
{
namespace renderer
{

class scoped
:
	public sge::gui::impl::renderer::stateless
{
	FCPPT_NONCOPYABLE(
		scoped
	);
public:
	scoped(
		sge::renderer::device::ffp &,
		sge::renderer::context::ffp &
	);

	~scoped()
	override;
private:
	typedef
	sge::sprite::state::all_choices sprite_state_choices;

	typedef
	sge::sprite::state::object<
		sprite_state_choices
	>
	sprite_state;

	typedef
	sge::sprite::state::scoped<
		sprite_state_choices
	>
	sprite_scoped_state;

	sprite_state state_;

	sprite_scoped_state const scoped_state_;
};

}
}
}
}

#endif
