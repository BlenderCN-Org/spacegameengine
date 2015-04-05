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


#ifndef SGE_OPENGL_BUFFER_SOFTWARE_HPP_INCLUDED
#define SGE_OPENGL_BUFFER_SOFTWARE_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/buffer/base.hpp>
#include <sge/opengl/buffer/id.hpp>
#include <sge/opengl/buffer/optional_id.hpp>
#include <sge/opengl/buffer/type.hpp>
#include <sge/renderer/const_raw_pointer.hpp>
#include <sge/renderer/raw_pointer.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace buffer
{

class software
:
	public sge::opengl::buffer::base
{
	FCPPT_NONCOPYABLE(
		software
	);
public:
	software();

	~software()
	override;
private:
	sge::opengl::buffer::id const
	gen_buffer()
	override;

	void
	delete_buffer(
		sge::opengl::buffer::id
	)
	override;

	void
	bind_buffer(
		sge::opengl::buffer::type,
		sge::opengl::buffer::optional_id const &
	)
	override;

	GLvoid *
	map_buffer(
		sge::opengl::buffer::type,
		GLenum flags
	)
	override;

	GLvoid *
	map_buffer_range(
		sge::opengl::buffer::type,
		GLenum flags,
		GLsizei first,
		GLsizei size
	)
	override;

	bool
	map_buffer_range_supported() const
	override;

	void
	unmap_buffer(
		sge::opengl::buffer::type
	)
	override;

	void
	buffer_data(
		sge::opengl::buffer::type,
		GLsizei size,
		GLvoid const *data,
		GLenum flags
	)
	override;

	void
	buffer_sub_data(
		sge::opengl::buffer::type,
		GLsizei first,
		GLsizei size,
		GLvoid const *data
	)
	override;

	void *
	buffer_offset(
		sge::opengl::buffer::type,
		GLsizei offset
	) const
	override;

	bool
	hardware_supported() const
	override;

	typedef std::unordered_map<
		sge::opengl::buffer::id,
		sge::renderer::raw_pointer
	> buffer_map;

	sge::opengl::buffer::id const
	bound_buffer(
		sge::opengl::buffer::type
	) const;

	sge::renderer::raw_pointer &
	buffer_object(
		sge::opengl::buffer::id
	);

	sge::renderer::const_raw_pointer
	buffer_object(
		sge::opengl::buffer::id
	) const;

	typedef std::unordered_map<
		sge::opengl::buffer::type,
		sge::opengl::buffer::optional_id
	> bound_buffer_map;

	bound_buffer_map bound_buffers_;

	sge::opengl::buffer::id nextid_;

	buffer_map buffers_;
};

}
}
}

#endif
