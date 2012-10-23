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


#include <sge/window/default_class_name.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/parameters.hpp>
#include <sge/window/size_hints.hpp>
#include <sge/window/title.hpp>
#include <awl/cursor/const_optional_object_ref.hpp>
#include <awl/cursor/object_fwd.hpp>
#include <fcppt/string.hpp>


sge::window::parameters::parameters(
	sge::window::title const &_title,
	sge::window::dim const &_dim
)
:
	title_(
		_title
	),
	dim_(
		_dim
	),
	class_name_(
		sge::window::default_class_name()
	),
	size_hints_(),
	cursor_()
{
}

sge::window::parameters &
sge::window::parameters::class_name(
	fcppt::string const &_class_name
)
{
	class_name_ = _class_name;

	return *this;
}

sge::window::parameters &
sge::window::parameters::size_hints(
	sge::window::size_hints const &_size_hints
)
{
	size_hints_ = _size_hints;

	return *this;
}

sge::window::parameters &
sge::window::parameters::cursor(
	awl::cursor::object const &_cursor
)
{
	cursor_ =
		awl::cursor::const_optional_object_ref(
			_cursor
		);

	return *this;
}

sge::window::title const &
sge::window::parameters::title() const
{
	return title_;
}

sge::window::dim const &
sge::window::parameters::dim() const
{
	return dim_;
}

fcppt::string const &
sge::window::parameters::class_name() const
{
	return class_name_;
}

sge::window::size_hints const &
sge::window::parameters::size_hints() const
{
	return size_hints_;
}

awl::cursor::const_optional_object_ref const &
sge::window::parameters::cursor() const
{
	return cursor_;
}
