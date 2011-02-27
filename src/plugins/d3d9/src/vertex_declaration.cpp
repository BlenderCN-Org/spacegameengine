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


#include "../vertex_declaration.hpp"
#include "../d3dinclude.hpp"
#include "../convert/vertex_role.hpp"
#include "../convert/vertex_type.hpp"
#include <sge/renderer/vf/dynamic/format.hpp>
#include <sge/renderer/vf/dynamic/ordered_element_list.hpp>
#include <sge/renderer/vf/dynamic/part_list.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/text.hpp>
#include <boost/foreach.hpp>
#include <map>

sge::d3d9::vertex_declaration::vertex_declaration(
	d3d9::d3d_device_ptr const _device,
	sge::renderer::vf::dynamic::format const &_format
)
:
	format_(_format),
	declaration_()
{
	typedef fcppt::container::raw_vector<
		D3DVERTEXELEMENT9
	> element_vector;
	
	element_vector vertex_elements;

	WORD stream(
		0
	);

	typedef std::map<
		D3DDECLUSAGE,
		unsigned
	> usage_count_map;

	BOOST_FOREACH(
		renderer::vf::dynamic::part_list::const_reference part,
		_format.parts()
	)
	{
		usage_count_map usage_counts;

		BOOST_FOREACH(
			renderer::vf::dynamic::ordered_element_list::const_reference element,
			part.elements()
		)
		{
			D3DDECLUSAGE const usage(
				convert::vertex_role(
					element.element()
				)
			);

			D3DVERTEXELEMENT9 const new_elem =
			{
				stream, // Stream
				static_cast<
					WORD
				>(
					element.offset()
				), // Offset
				convert::vertex_type(
					element.element()
				), // Type
				D3DDECLMETHOD_DEFAULT,
				usage,
				static_cast<
					BYTE
				>(
					usage_counts[
						usage
					]++
				)
			};

			vertex_elements.push_back(
				new_elem
			);
		}

		++stream;
	}

	D3DVERTEXELEMENT9 const end_token = D3DDECL_END();

	vertex_elements.push_back(
		end_token
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

	//if(D3DXFVFFromDeclarator(&vertex_elements.front(),&fvf) != D3D_OK)
	//	fvf = 0;
}

sge::d3d9::d3d_vertex_declaration_ptr const
sge::d3d9::vertex_declaration::get() const
{
	return declaration_;
}

sge::renderer::vf::dynamic::format const &
sge::d3d9::vertex_declaration::format() const
{
	return format_;
}

sge::renderer::size_type
sge::d3d9::vertex_declaration::stride(
	renderer::vf::dynamic::part_index const _part
) const
{
	return
		this->format().parts().at(
			_part.get()
		).stride();
}
