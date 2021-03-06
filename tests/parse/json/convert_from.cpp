/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/parse/json/array.hpp>
#include <sge/parse/json/convert_from.hpp>
#include <sge/parse/json/element_vector.hpp>
#include <sge/parse/json/int_type.hpp>
#include <sge/parse/json/make_value.hpp>
#include <sge/parse/json/value.hpp>
#include <fcppt/make_recursive.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/math/matrix/comparison.hpp>
#include <fcppt/math/matrix/output.hpp>
#include <fcppt/math/matrix/row.hpp>
#include <fcppt/math/matrix/static.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


TEST_CASE(
	"parse::json::convert_from",
	"[sge]"
)
{
	auto const make_row(
		[](
			std::vector<
				int
			> const &_values
		)
		->
		sge::parse::json::value
		{
			return
				sge::parse::json::make_value(
					sge::parse::json::array(
						fcppt::algorithm::map<
							sge::parse::json::element_vector
						>(
							_values,
							[](
								int const _value
							)
							{
								return
									fcppt::make_recursive(
										sge::parse::json::make_value(
											fcppt::cast::size<
												sge::parse::json::int_type
											>(
												_value
											)
										)
									);
							}
						)
					)
				);
		}
	);

	auto const make_matrix(
		[
			&make_row
		](
			std::vector<
				std::vector<
					int
				>
			> const &_values
		)
		->
		sge::parse::json::value
		{
			return
				sge::parse::json::make_value(
					sge::parse::json::array(
						fcppt::algorithm::map<
							sge::parse::json::element_vector
						>(
							_values,
							[
								&make_row
							](
								std::vector<
									int
								> const &_inner
							)
							{
								return
									fcppt::make_recursive(
										make_row(
											_inner
										)
									);
							}
						)
					)
				);
		}
	);

	sge::parse::json::value const value(
		make_matrix(
			{
				{
					1,
					2
				},
				{
					3,
					4
				},
				{
					5,
					6
				}
			}
		)
	);

	typedef
	fcppt::math::matrix::static_<
		int,
		3,
		2
	>
	int_3_2_matrix;

	int_3_2_matrix const result(
		sge::parse::json::convert_from<
			int_3_2_matrix
		>(
			value
		)
	);

	CHECK(
		result
		==
		int_3_2_matrix(
			fcppt::math::matrix::row(
				1,
				2
			),
			fcppt::math::matrix::row(
				3,
				4
			),
			fcppt::math::matrix::row(
				5,
				6
			)
		)
	);
}
