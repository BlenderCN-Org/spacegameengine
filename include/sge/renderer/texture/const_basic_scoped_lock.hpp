/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_RENDERER_TEXTURE_CONST_BASIC_SCOPED_LOCK_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_CONST_BASIC_SCOPED_LOCK_HPP_INCLUDED

#include <sge/renderer/symbol.hpp>
#include <sge/renderer/color_buffer/basic.hpp>
#include <sge/renderer/color_buffer/const_basic_scoped_lock.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{
namespace texture
{

template<
	typename Texture
>
class const_basic_scoped_lock
{
	FCPPT_NONCOPYABLE(
		const_basic_scoped_lock
	);
public:
	typedef typename Texture::rect lock_area;

	typedef typename Texture::color_buffer color_buffer;

	typedef typename color_buffer::const_view const_view;

	SGE_RENDERER_SYMBOL
	explicit
	const_basic_scoped_lock(
		Texture const &
	);

	SGE_RENDERER_SYMBOL
	const_basic_scoped_lock(
		Texture const &,
		lock_area const &
	);

	SGE_RENDERER_SYMBOL
	const_view const
	value() const;

	SGE_RENDERER_SYMBOL
	~const_basic_scoped_lock();
private:
	typedef sge::renderer::color_buffer::const_basic_scoped_lock<
		color_buffer
	> buffer_lock;

	buffer_lock const lock_;
};

}
}
}

#endif
