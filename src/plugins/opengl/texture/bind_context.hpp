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


#ifndef SGE_OPENGL_TEXTURE_BIND_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_BIND_CONTEXT_HPP_INCLUDED

#include "bind_context_fwd.hpp"
#include "const_base_ptr.hpp"
#include "id.hpp"
#include "optional_type.hpp"
#include "type.hpp"
#include "../context/base.hpp"
#include "../context/id.hpp"
#include "../context/object_fwd.hpp"
#include <sge/renderer/stage_type.hpp>
#include <fcppt/container/index_map_decl.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_decl.hpp>
#include <fcppt/weak_ptr_decl.hpp>
#include <map>
#include <vector>

namespace sge
{
namespace opengl
{
namespace texture
{

class bind_context
:
	public context::base
{
	FCPPT_NONCOPYABLE(
		bind_context
	);
public:
	bind_context();

	~bind_context();

	void
	bind_for_rendering(
		opengl::context::object &,
		opengl::texture::const_base_ptr,
		renderer::stage_type
	);

	void
	unbind_for_rendering(
		opengl::context::object &,
		renderer::stage_type
	);

	void
	bind_for_work(
		opengl::context::object &,
		texture::type,
		texture::id,
		renderer::stage_type
	);

	void
	unbind_for_work(
		opengl::context::object &,
		renderer::stage_type
	);

	typedef void needs_before;

	static context::id const static_id;
private:
	void
	decrement_type_count(
		texture::type
	);

	typedef fcppt::weak_ptr<
		opengl::texture::base const
	> texture_weak_ptr;

	typedef fcppt::container::index_map<
		texture_weak_ptr
	> texture_vector;

	typedef fcppt::container::index_map<
		texture::optional_type
	> texture_type_vector;

	typedef std::map<
		texture::type,
		renderer::stage_type::value_type
	> texture_type_map;

	texture_vector
		render_textures_,
		temp_textures_;
	
	texture_type_vector last_types_;

	texture_type_map texture_type_counts_;
};

}
}
}

#endif
