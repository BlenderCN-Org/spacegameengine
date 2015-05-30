/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_OPENGL_TEXTURE_BASIC_BOX_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_BASIC_BOX_HPP_INCLUDED

#include <sge/opengl/texture/basic.hpp>
#include <sge/opengl/texture/basic_box_fwd.hpp>
#include <sge/opengl/texture/basic_parameters_fwd.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <sge/renderer/texture/mipmap/level_count.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

template<
	typename Types
>
class basic_box
:
	public sge::opengl::texture::basic<
		Types
	>
{
	typedef sge::opengl::texture::basic<
		Types
	> base_type;

	FCPPT_NONCOPYABLE(
		basic_box
	);
public:
	typedef typename Types::parameters parameters_type;

	basic_box(
		sge::opengl::texture::basic_parameters const &,
		sge::opengl::texture::type,
		parameters_type const &
	);

	~basic_box()
	override;
private:
	typedef typename base_type::color_buffer color_buffer;

	typedef typename base_type::dim dim;

	// implementation for base class

	color_buffer &
	level(
		sge::renderer::texture::mipmap::level
	)
	override;

	color_buffer const &
	level(
		sge::renderer::texture::mipmap::level
	) const
	override;

	sge::renderer::texture::mipmap::level_count const
	levels() const
	override;

	typedef
	fcppt::unique_ptr<
		color_buffer
	>
	color_buffer_unique_ptr;

	typedef
	std::vector<
		color_buffer_unique_ptr
	>
	buffer_vector;

	buffer_vector levels_;
};

}
}
}

#endif
