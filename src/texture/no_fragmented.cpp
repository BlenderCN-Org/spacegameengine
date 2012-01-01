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


#include <sge/log/global.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/texture/planar_parameters.hpp>
#include <sge/texture/guaranteed_free.hpp>
#include <sge/texture/no_fragmented.hpp>
#include <sge/texture/part_fragmented.hpp>
#include <sge/texture/atlasing/bounds.hpp>
#include <sge/texture/atlasing/need.hpp>
#include <sge/texture/atlasing/size.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/dim/comparison.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ostream>
#include <fcppt/config/external_end.hpp>


sge::texture::no_fragmented::no_fragmented(
	renderer::device &_rend,
	image::color::format::type const _format,
	renderer::texture::mipmap::object const &_mipmap
)
:
 	rend_(_rend),
	format_(_format),
 	mipmap_(_mipmap),
	tex_()
{
}

sge::texture::no_fragmented::~no_fragmented()
{
}

sge::texture::part_ptr const
sge::texture::no_fragmented::consume_fragment(
	renderer::dim2 const &_dim
)
{
	if(
		tex_
	)
		return texture::part_ptr();

	renderer::dim2 const real_dim(
		atlasing::bounds(
			_dim
		)
	);

	tex_ =
		rend_.create_planar_texture(
			renderer::texture::planar_parameters(
				real_dim,
				format_,
				mipmap_,
				renderer::resource_flags::none,
				renderer::texture::capabilities_field::null()
			)
		);

	if(
		real_dim != _dim
	)
		FCPPT_LOG_WARNING(
			log::global(),
			fcppt::log::_
				<< FCPPT_TEXT("You used a texture::no_fragmented whose dimensions are not a power of 2.")\
				FCPPT_TEXT(" This is slower to load and requires more texture memory because it needs atlasing and thus is not intuitive.")\
				FCPPT_TEXT(" The texture's size was ")
				<< _dim
				<< FCPPT_TEXT('.')
		);

	return
		texture::part_ptr(
			fcppt::make_shared_ptr<
				texture::part_fragmented
			>(
				renderer::lock_rect(
					renderer::lock_rect::vector::null(),
					atlasing::size(
						_dim
					)
				),
				fcppt::ref(
					*this
				),
				atlasing::need(
					_dim.w()
				),
				atlasing::need(
					_dim.h()
				)
			)
		);
}

void
sge::texture::no_fragmented::on_return_fragment(
	part const &
)
{
	tex_.reset();
}

sge::renderer::texture::planar_ptr const
sge::texture::no_fragmented::texture()
{
	return tex_;
}

sge::renderer::texture::const_planar_ptr const
sge::texture::no_fragmented::texture() const
{
	return tex_;
}

bool
sge::texture::no_fragmented::repeatable() const
{
	return true;
}

sge::texture::free_type
sge::texture::no_fragmented::free_value() const
{
	return
		this->empty()
		?
			0
		:
			texture::guaranteed_free();
}

bool
sge::texture::no_fragmented::empty() const
{
	return !tex_;
}
