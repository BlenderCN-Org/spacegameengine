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


#ifndef SGE_DEVIL_LOADER_HPP_INCLUDED
#define SGE_DEVIL_LOADER_HPP_INCLUDED

#include <sge/const_raw_range.hpp>
#include <sge/extension_set.hpp>
#include <sge/optional_extension.hpp>
#include <sge/devil/library.hpp>
#include <sge/image/capabilities_field.hpp>
#include <sge/image2d/file_ptr.hpp>
#include <sge/image2d/loader.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/filesystem/path.hpp>


namespace sge
{
namespace devil
{

class loader
:
	public sge::image2d::loader
{
	FCPPT_NONCOPYABLE(
		loader
	);
public:
	loader();

	~loader();

	image2d::file_ptr const
	load(
		fcppt::filesystem::path const &
	);

	image2d::file_ptr const
	load_raw(
		sge::const_raw_range const &,
		sge::optional_extension const &
	);

	image2d::file_ptr const
	create(
		image2d::view::const_object const &
	);

	image::capabilities_field const
	capabilities() const;

	sge::extension_set const
	extensions() const;
private:
	library lib_;
};

}
}

#endif
