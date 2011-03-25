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


#ifndef SGE_CEGUI_DETAIL_IMAGE_CODEC_HPP_INCLUDED
#define SGE_CEGUI_DETAIL_IMAGE_CODEC_HPP_INCLUDED

#include <sge/image2d/multi_loader_fwd.hpp>
#include <CEGUI/CEGUIImageCodec.h>

namespace CEGUI
{
class RawDataContainer;
class Texture;
}

namespace sge
{
namespace cegui
{
namespace detail
{
class image_codec
:
	public CEGUI::ImageCodec
{
public:
	explicit	
	image_codec(
		sge::image2d::multi_loader &);

	CEGUI::Texture *
	load(
		CEGUI::RawDataContainer const &,
		CEGUI::Texture *);

	sge::image2d::multi_loader &
	loader() const;
private:
	sge::image2d::multi_loader &image_loader_;
};
}
}
}

#endif
