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


#ifndef SGE_SYSTEMS_RENDERER_HPP_INCLUDED
#define SGE_SYSTEMS_RENDERER_HPP_INCLUDED

#include <sge/plugin/name.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/systems/optional_name.hpp>
#include <sge/systems/renderer_fwd.hpp>
#include <sge/systems/symbol.hpp>
#include <sge/viewport/resize_function.hpp>
#include <fcppt/nonassignable.hpp>


namespace sge
{
namespace systems
{

class renderer
{
	FCPPT_NONASSIGNABLE(
		renderer
	);
public:
	SGE_SYSTEMS_SYMBOL
	renderer(
		sge::renderer::parameters const &,
		sge::viewport::resize_function const &
	);

	SGE_SYSTEMS_SYMBOL
	renderer &
	name(
		sge::plugin::name const &
	);

	sge::renderer::parameters const &
	parameters() const;

	sge::viewport::resize_function const &
	resize_function() const;

	sge::systems::optional_name const &
	name() const;
private:
	sge::renderer::parameters const parameters_;

	sge::viewport::resize_function const resize_function_;

	sge::systems::optional_name name_;
};

}
}

#endif
