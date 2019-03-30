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


#ifndef SGE_OPENGL_DRAW_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_DRAW_CONTEXT_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/fun_ref.hpp>
#include <sge/opengl/fun_ref_value_type.hpp>
#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/info/context_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional/reference.hpp>


namespace sge
{
namespace opengl
{

class draw_context
:
	public sge::opengl::context::base
{
	FCPPT_NONCOPYABLE(
		draw_context
	);
public:
	typedef
	sge::opengl::info::context const &
	parameter;

	explicit
	draw_context(
		sge::opengl::info::context const &
	);

	~draw_context()
	override;

	typedef
	sge::opengl::fun_ref<
		PFNGLDRAWRANGEELEMENTSPROC
	>
	gl_draw_range_elements;

	typedef
	fcppt::optional::reference<
		sge::opengl::fun_ref_value_type<
			gl_draw_range_elements
		>
	>
	optional_draw_range_elements;

	typedef
	optional_draw_range_elements::value_type
	draw_range_elements_ref;

	optional_draw_range_elements
	draw_range_elements() const;

	static sge::opengl::context::id const static_id;
private:
	optional_draw_range_elements const draw_range_elements_;
};

}
}

#endif
