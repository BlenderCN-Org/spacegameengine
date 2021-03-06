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


#ifndef SGE_SYSTEMS_IMPL_INPUT_OBJECT_HPP_INCLUDED
#define SGE_SYSTEMS_IMPL_INPUT_OBJECT_HPP_INCLUDED

#include <sge/input/processor_fwd.hpp>
#include <sge/input/processor_unique_ptr.hpp>
#include <sge/input/system_fwd.hpp>
#include <sge/input/system_unique_ptr.hpp>
#include <sge/input/plugin/collection_fwd.hpp>
#include <sge/systems/input_fwd.hpp>
#include <sge/systems/impl/input/cursor_modifier_fwd.hpp>
#include <sge/systems/impl/input/object_fwd.hpp>
#include <sge/systems/impl/window/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/optional/object_decl.hpp>


namespace sge
{
namespace systems
{
namespace impl
{
namespace input
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	object(
		fcppt::log::context &,
		fcppt::log::object &,
		sge::input::plugin::collection const &,
		sge::systems::input const &,
		sge::systems::impl::window::object const &
	);

	~object();

	sge::input::system &
	system() const;

	sge::input::processor &
	processor() const;
private:
	sge::input::system_unique_ptr const input_system_;

	sge::input::processor_unique_ptr const input_processor_;

	typedef
	fcppt::unique_ptr<
		sge::systems::impl::input::cursor_modifier
	>
	cursor_modifier_unique_ptr;

	typedef
	fcppt::optional::object<
		cursor_modifier_unique_ptr
	>
	optional_cursor_modifier_unique_ptr;

	optional_cursor_modifier_unique_ptr const cursor_modifier_;
};

}
}
}
}

#endif
