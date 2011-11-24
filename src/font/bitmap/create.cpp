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


#include <sge/font/metrics_ptr.hpp>
#include <sge/font/bitmap/create.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/src/font/bitmap/metrics.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/filesystem/path.hpp>


sge::font::metrics_ptr const
sge::font::bitmap::create(
	fcppt::filesystem::path const &_path,
	sge::image2d::system &_system
)
{
	return
		fcppt::make_shared_ptr<
			font::bitmap::metrics
		>(
			_path,
			fcppt::ref(
				_system
			)
		);
}
