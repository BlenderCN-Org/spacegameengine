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


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/vertex_declaration.hpp>
#include <sge/d3d9/vf/create.hpp>
#include <sge/d3d9/vf/element_vector.hpp>
#include <sge/d3d9/vf/texture_coordinates.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/vf/dynamic/format.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <sge/renderer/vf/dynamic/stride.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/raw_vector_impl.hpp>


sge::d3d9::vertex_declaration::vertex_declaration(
	IDirect3DDevice9 *const _device,
	sge::renderer::vf::dynamic::format const &_format
)
:
	format_(
		_format
	),
	texture_coordinates_(
		sge::d3d9::vf::texture_coordinates(
			_format
		)
	),
	declaration_()
{

	sge::d3d9::vf::element_vector const vertex_elements(
		sge::d3d9::vf::create(
			_format,
			texture_coordinates_
		)
	);

	IDirect3DVertexDeclaration9 *decl;

	if(
		_device->CreateVertexDeclaration(
			vertex_elements.data(),
			&decl
		)
		!= D3D_OK
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("CreateVertexDeclaration() failed!")
		);

	declaration_.reset(
		decl
	);
}

sge::d3d9::vertex_declaration::~vertex_declaration()
{
}

IDirect3DVertexDeclaration9 *
sge::d3d9::vertex_declaration::get() const
{
	return
		declaration_.get();
}

sge::renderer::vf::dynamic::format const &
sge::d3d9::vertex_declaration::format() const
{
	return
		format_;
}

sge::renderer::vf::dynamic::stride const
sge::d3d9::vertex_declaration::stride(
	sge::renderer::vf::dynamic::part_index const _part
) const
{
	return
		this->format().parts().at(
			_part.get()
		).stride();
}
