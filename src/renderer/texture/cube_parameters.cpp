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


#include "basic_parameters_impl.hpp"
#include <sge/image/color/format.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/texture/address_mode2.hpp>
#include <sge/renderer/texture/cube_parameters.hpp>
#include <fcppt/export_symbol.hpp>
#include <fcppt/math/dim/basic_impl.hpp>


template FCPPT_EXPORT_SYMBOL class
sge::renderer::texture::basic_parameters<
	sge::renderer::size_type,
	sge::renderer::texture::address_mode2,
	sge::image::color::format::type
>;
