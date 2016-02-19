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


#ifndef SGE_OPENGL_VERTEX_DECLARATION_HPP_INCLUDED
#define SGE_OPENGL_VERTEX_DECLARATION_HPP_INCLUDED

#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/vertex/declaration_fwd.hpp>
#include <sge/opengl/vf/part_fwd.hpp>
#include <sge/renderer/vertex/declaration.hpp>
#include <sge/renderer/vertex/declaration_parameters_fwd.hpp>
#include <sge/renderer/vf/dynamic/format.hpp>
#include <sge/renderer/vf/dynamic/part_fwd.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace vertex
{

class declaration
:
	public sge::renderer::vertex::declaration
{
	FCPPT_NONCOPYABLE(
		declaration
	);
public:
	declaration(
		sge::opengl::context::object &,
		sge::renderer::vertex::declaration_parameters const &
	);

	~declaration()
	override;

	sge::renderer::vf::dynamic::part const &
	format_part(
		sge::renderer::vf::dynamic::part_index
	) const;

	sge::opengl::vf::part const &
	gl_format_part(
		sge::renderer::vf::dynamic::part_index
	) const;
private:
	sge::renderer::vf::dynamic::format const format_;

	// Parts could be movable but lack a proper default state
	typedef
	fcppt::unique_ptr<
		sge::opengl::vf::part
	>
	part_unique_ptr;

	typedef
	std::vector<
		part_unique_ptr
	>
	part_container;

	part_container const parts_;
};

}
}
}

#endif
