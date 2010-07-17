/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENGL_GLSL_ARB_PROGRAM_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_GLSL_ARB_PROGRAM_CONTEXT_HPP_INCLUDED

#include "program_context_fwd.hpp"
#include "handle.hpp"
#include "../../common.hpp"
#include "../../context/base.hpp"
#include "../../context/id.hpp"
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace opengl
{
namespace glsl
{
namespace arb
{

class program_context
:
	public opengl::context::base
{
	FCPPT_NONCOPYABLE(program_context)
public:
	program_context();

	~program_context();

	typedef arb::handle handle;

	typedef handle (*gl_create_program)();

	typedef void (*gl_delete_program)(handle);

	typedef void (*gl_attach_shader)(handle, handle);

	typedef void (*gl_detach_shader)(handle, handle);

	typedef void (*gl_link_program)(handle);

	typedef void (*gl_program_integer)(handle, GLenum, GLint *);

	typedef void (*gl_use_program)(handle);

	typedef void (*gl_program_info_log)(handle, GLint, GLint *, char *);

	gl_create_program
	create_program() const;
	
	gl_delete_program
	delete_program() const;

	gl_attach_shader
	attach_shader() const;

	gl_detach_shader
	detach_shader() const;

	gl_link_program
	link_program() const;

	gl_program_integer
	program_integer() const;

	gl_use_program
	use_program() const;

	gl_program_info_log
	program_info_log() const;

	GLenum
	link_status_type() const;

	GLenum
	info_log_length_type() const;

	typedef void needs_before;

	static opengl::context::id const static_id;
private:
	gl_create_program const create_program_;

	gl_delete_program const delete_program_;

	gl_attach_shader const attach_shader_;

	gl_detach_shader const detach_shader_;

	gl_link_program const link_program_;

	gl_program_integer const program_integer_;

	gl_use_program const use_program_;

	gl_program_info_log const program_info_log_;

	GLenum const
		link_status_type_,
		info_log_length_type_;
};

}
}
}
}

#endif
