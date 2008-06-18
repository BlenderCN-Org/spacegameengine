/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/image/util.hpp>

const sge::renderer::texture_ptr
sge::image::create_texture(
	const renderer::device_ptr r,
	const image_ptr p,
	const renderer::filter_args& filter,
	const renderer::resource_flag_t flags)
{
	// FIXME
	//return r->create_texture(p->data(), p->dim(), filter, flags);
}

const sge::renderer::texture_ptr
sge::image::create_texture(
	const path& file,
	const renderer::device_ptr r,
	const loader_ptr p,
	const renderer::filter_args& filter,
	const renderer::resource_flag_t flags)
{
	// FIXME
	//return create_texture(r, p->load_image(file), filter, flags);
}

