/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/renderer/arithmetic_convert.hpp>
#include <sge/export.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/apply_visitor.hpp>

namespace
{

template<
	typename Dest
>
struct visitor : boost::static_visitor<Dest> {
	template<
		typename T
	>
	Dest operator()(
		T const &) const;
};

}

template<
	typename Dest
>
Dest
sge::renderer::arithmetic_convert(
	any_arithmetic const &v)
{
	return boost::apply_visitor(
		visitor<Dest>(),
		v);
}

namespace
{

template<
	typename Dest
>
template<
	typename T
>
Dest
visitor<Dest>::operator()(
	T const &v) const
{
	return static_cast<Dest>(v);
}

}

#define SGE_INSTANTIATE_ARITHMETIC_CONVERT(dest)\
template SGE_SYMBOL \
dest \
sge::renderer::arithmetic_convert(\
	sge::renderer::any_arithmetic const &);

SGE_INSTANTIATE_ARITHMETIC_CONVERT(float)
SGE_INSTANTIATE_ARITHMETIC_CONVERT(double)

#undef SGE_INSTANTIATE_ARITMETIC_CONVERT
