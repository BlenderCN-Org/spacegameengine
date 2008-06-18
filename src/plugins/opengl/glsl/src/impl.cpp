/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)
Copyright (C) 2007       Simon Stienen    (s.stienen@slashlife.org)

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


#include "../impl.hpp"
#include "../program.hpp"
#include "../init.hpp"
#include "../../common.hpp"

const sge::renderer::glsl::program_ptr
sge::ogl::glsl::create_program_impl(
	const std::string& vs_source,
	const std::string& ps_source)
{
	return is_native()
		? renderer::glsl::program_ptr(
			new program<true>(vs_source, ps_source))
		: renderer::glsl::program_ptr(
			new program<false>(vs_source, ps_source));
}

void sge::ogl::glsl::set_program_impl(
	const renderer::glsl::program_ptr prog)
{
	if(is_native())
		program<true>::use(prog);
	else
		program<false>::use(prog);
}
