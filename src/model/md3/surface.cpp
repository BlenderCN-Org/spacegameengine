/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/model/md3/exception.hpp>
#include <sge/model/md3/load_flags.hpp>
#include <sge/model/md3/string.hpp>
#include <sge/src/model/md3/max_qpath.hpp>
#include <sge/src/model/md3/read_and_check_id3p.hpp>
#include <sge/src/model/md3/read_s32.hpp>
#include <sge/src/model/md3/read_string.hpp>
#include <sge/src/model/md3/s32.hpp>
#include <sge/src/model/md3/shader.hpp>
#include <sge/src/model/md3/shader_vector.hpp>
#include <sge/src/model/md3/surface.hpp>
#include <sge/src/model/md3/texpos.hpp>
#include <sge/src/model/md3/texpos_vector.hpp>
#include <sge/src/model/md3/transformed_vertex.hpp>
#include <sge/src/model/md3/transformed_vertex_vector.hpp>
#include <sge/src/model/md3/triangle.hpp>
#include <sge/src/model/md3/triangle_vector.hpp>
#include <sge/src/model/md3/vertex.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <istream>
#include <fcppt/config/external_end.hpp>


sge::model::md3::surface::surface(
	std::istream &_stream,
	md3::load_flags::type const _flags,
	md3::s32 const _num_frames_head
)
:
	name_(),
	shaders_(),
	triangles_(),
	texpos_(),
	transformed_vertices_()
{
	std::istream::off_type const start(
		_stream.tellg()
	);

	if(
		!md3::read_and_check_id3p(
			_stream
		)
	)
		throw sge::model::md3::exception(
			FCPPT_TEXT("Invalid md3 surface!")
		);

	name_ =
		md3::read_string<
			md3::max_qpath::value
		>(
			_stream
		);

	// flags
	sge::model::md3::read_s32(
		_stream
	);

	md3::s32 const num_frames(
		sge::model::md3::read_s32(
			_stream
		)
	);

	if(
		num_frames != _num_frames_head
	)
		throw sge::model::md3::exception(
			FCPPT_TEXT("num_frames mismatch in md3::surface!")
		);

	md3::s32 const
		num_shaders(
			sge::model::md3::read_s32(
				_stream
			)
		),
		num_verts(
			sge::model::md3::read_s32(
				_stream
			)
		),
		num_triangles(
			sge::model::md3::read_s32(
				_stream
			)
		),
		ofs_triangles(
			sge::model::md3::read_s32(
				_stream
			)
		),
		ofs_shaders(
			sge::model::md3::read_s32(
				_stream
			)
		),
		ofs_st(
			sge::model::md3::read_s32(
				_stream
			)
		),
		ofs_xyznormal(
			sge::model::md3::read_s32(
				_stream
			)
		),
		ofs_end(
			sge::model::md3::read_s32(
				_stream
			)
		);

	_stream.seekg(
		start
		+
		ofs_triangles
		,
		std::ios_base::beg
	);

	for(
		s32 i = 0;
		i < num_triangles;
		++i
	)
		triangles_.push_back(
			md3::triangle(
				_stream
			)
		);

	_stream.seekg(
		start
		+
		ofs_shaders
		,
		std::ios_base::beg
	);

	for(
		s32 i = 0;
		i < num_shaders;
		++i
	)
		shaders_.push_back(
			md3::shader(
				_stream
			)
		);

	_stream.seekg(
		start
		+
		ofs_st
		,
		std::ios_base::beg
	);

	for(
		s32 i = 0;
		i < num_verts;
		++i
	)
		texpos_.push_back(
			md3::texpos(
				_stream
			)
		);

	_stream.seekg(
		start
		+
		ofs_xyznormal
		,
		std::ios_base::beg
	);

	for(
		s32 i = 0;
		i < num_verts;
		++i
	)
		transformed_vertices_.push_back(
			md3::transformed_vertex(
				md3::vertex(
					_stream,
					_flags
				)
			)
		);

	_stream.seekg(
		start
		+
		ofs_end
		,
		std::ios_base::beg
	);
}

sge::model::md3::string const &
sge::model::md3::surface::name() const
{
	return name_;
}

sge::model::md3::shader_vector const &
sge::model::md3::surface::shaders() const
{
	return shaders_;
}

sge::model::md3::triangle_vector const &
sge::model::md3::surface::triangles() const
{
	return triangles_;
}

sge::model::md3::texpos_vector const &
sge::model::md3::surface::texpos() const
{
	return texpos_;
}

sge::model::md3::transformed_vertex_vector const &
sge::model::md3::surface::transformed_vertices() const
{
	return transformed_vertices_;
}
