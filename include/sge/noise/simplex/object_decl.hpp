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


#ifndef SGE_NOISE_SIMPLEX_OBJECT_DECL_HPP_INCLUDED
#define SGE_NOISE_SIMPLEX_OBJECT_DECL_HPP_INCLUDED


#include <sge/noise/simplex/object_fwd.hpp>
#include <sge/noise/simplex/width.hpp>
#include <fcppt/static_assert_statement.hpp>
#include <fcppt/container/array.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/math/matrix/static.hpp>
#include <fcppt/math/vector/static.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <cstddef>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace noise
{
namespace simplex
{

template<
	typename Float,
	std::size_t N
>
class object
{
	FCPPT_STATIC_ASSERT_STATEMENT(
		boost::is_floating_point<
			Float
		>::value
	);
public:
	typedef
	typename
	fcppt::math::vector::static_<
		Float,
		N
	>::type
	vector_type;

	typedef
	Float
	value_type;

	explicit
	object(
		sge::noise::simplex::width const &);

	Float
	sample(
		vector_type const &);
private:
	typedef
	fcppt::math::size_type
	index_type;

	typedef
	std::vector<
		index_type
	> index_container;

	typedef
	typename
	fcppt::math::matrix::static_<
		Float,
		N,
		N
	>::type
	matrix;

	typedef
	fcppt::container::array<vector_type,2u*N>
	gradient_array;

	index_container perm_;
	gradient_array gradients_;

	std::size_t
	mod(
	long int const &a,
	std::size_t const &b);

	std::size_t
	index(
		vector_type const &vec);

	typedef fcppt::container::array<
		vector_type,
		N + 1
	> corner_array;

	corner_array
	corners(
		vector_type point);

	Float
	stretch_factor();

	Float
	inv_factor();

	matrix
	stretch_m();

	matrix
	inv_m();

	Float
	contrib(
		vector_type const &v,
		vector_type const &intv);
};

}
}
}

#endif
