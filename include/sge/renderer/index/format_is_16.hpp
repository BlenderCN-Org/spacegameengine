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


#ifndef SGE_RENDERER_INDEX_FORMAT_IS_16_HPP_INCLUDED
#define SGE_RENDERER_INDEX_FORMAT_IS_16_HPP_INCLUDED

#include <sge/renderer/index/format.hpp>
#include <sge/renderer/index/i16.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/type_traits/is_same.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace renderer
{
namespace index
{

template<
	typename Format
>
struct format_is_16
:
boost::is_same<
	typename Format::index_type,
	index::i16
>
{
};

}
}
}

#endif
