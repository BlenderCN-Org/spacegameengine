/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_LIBPNG_FILE_HPP_INCLUDED
#define SGE_LIBPNG_FILE_HPP_INCLUDED

#include "byte_vector.hpp"
#include <sge/image/color/format.hpp>
#include <sge/image/file.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/math/dim/basic_decl.hpp>

namespace sge
{
namespace libpng
{
class file
:
	public image::file
{
public:
	explicit file(
		fcppt::filesystem::path const &
	);

	explicit file(
		image::view::const_object const &
	);

	void data(
		image::view::const_object const &);
	image::view::const_object const view() const;
	image::dim_type const dim() const;
	void save(
		fcppt::filesystem::path const &);
private:
	image::dim_type dim_;
	byte_vector bytes_;
	image::color::format::type format_;
};
}
}

#endif
