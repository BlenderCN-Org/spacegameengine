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


#ifndef SGE_SRC_CEGUI_IMAGE_CODEC_HPP_INCLUDED
#define SGE_SRC_CEGUI_IMAGE_CODEC_HPP_INCLUDED

#include <sge/image2d/system_fwd.hpp>
#include <sge/src/cegui/image_codec_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/ImageCodec.h>
#include <fcppt/config/external_end.hpp>


namespace CEGUI
{
class RawDataContainer;
class Texture;
}

namespace sge
{
namespace cegui
{

class image_codec
:
	public CEGUI::ImageCodec
{
	FCPPT_NONCOPYABLE(
		image_codec
	);
public:
	explicit
	image_codec(
		sge::image2d::system &
	);

	~image_codec()
	override;
private:
	CEGUI::Texture *
	load(
		CEGUI::RawDataContainer const &,
		CEGUI::Texture *
	)
	override;
public:
	sge::image2d::system &
	image_system() const;
private:
	sge::image2d::system &image_system_;
};

}
}

#endif