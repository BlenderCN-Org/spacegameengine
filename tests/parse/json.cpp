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
#include <sge/parse/json/array_or_object.hpp>
#include <sge/parse/json/element_vector.hpp>
#include <sge/parse/json/float_type.hpp>
#include <sge/parse/json/int_type.hpp>
#include <sge/parse/json/make_value.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/parse_string.hpp>
#include <sge/parse/json/start.hpp>
#include <fcppt/make_recursive.hpp>
#include <fcppt/strong_typedef_comparison.hpp>
#include <fcppt/catch/convert.hpp>
#include <fcppt/catch/either.hpp>
#include <fcppt/catch/optional.hpp>
#include <fcppt/catch/recursive.hpp>
#include <fcppt/catch/strong_typedef.hpp>
#include <fcppt/catch/variant.hpp>
#include <fcppt/either/comparison.hpp>
#include <fcppt/parse/make_success.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>


namespace Catch
{

template<>
struct StringMaker<
	sge::parse::json::start
>
{
	static
	std::string
	convert(
		sge::parse::json::start const &_value
	)
	{
		return
			fcppt::catch_::convert(
				_value.variant
			);
	}
};

template<>
struct StringMaker<
	sge::parse::json::array
>
{
	static
	std::string
	convert(
		sge::parse::json::array const &_value
	)
	{
		return
			fcppt::catch_::convert(
				_value.elements
			);
	}
};

template<>
struct StringMaker<
	sge::parse::json::object
>
{
	static
	std::string
	convert(
		sge::parse::json::object const &_value
	)
	{
		return
			fcppt::catch_::convert(
				_value.members
			);
	}
};

template<>
struct StringMaker<
	sge::parse::json::value
>
{
	static
	std::string
	convert(
		sge::parse::json::value const &_value
	)
	{
		return
			fcppt::catch_::convert(
				_value.get()
			);
	}
};

}

TEST_CASE(
	"parse_json object",
	"[sge]"
)
{
	CHECK(
		sge::parse::json::parse_string(
			std::string{
				"{"
					"\"foo\": 42,"
					"\"bar\" :"
					"{"
						"\"inner\" : 5.5,"
						"\"booltest\" : true"
					"}"
				"}"
			}
		)
		==
		fcppt::parse::make_success<
			char
		>(
			sge::parse::json::start{
				sge::parse::json::array_or_object{
					sge::parse::json::object{
						sge::parse::json::member_map{
							sge::parse::json::member{
								std::string{
									"foo"
								},
								fcppt::make_recursive(
									sge::parse::json::make_value(
										sge::parse::json::int_type{
											42
										}
									)
								)
							},
							sge::parse::json::member{
								std::string{
									"bar"
								},
								fcppt::make_recursive(
									sge::parse::json::make_value(
										sge::parse::json::object{
											sge::parse::json::member_map{
												sge::parse::json::member{
													std::string{
														"inner"
													},
													fcppt::make_recursive(
														sge::parse::json::make_value(
															sge::parse::json::float_type{
																5.5
															}
														)
													)
												},
												sge::parse::json::member{
													std::string{
														"booltest"
													},
													fcppt::make_recursive(
														sge::parse::json::make_value(
															true
														)
													)
												}
											}
										}
									)
								)
							}
						}
					}
				}
			}
		)
	);
}

TEST_CASE(
	"parse_json array",
	"[sge]"
)
{
	CHECK(
		sge::parse::json::parse_string(
			std::string{
				"["
					"42,"
					"100"
				"]"
			}
		)
		==
		fcppt::parse::make_success<
			char
		>(
			sge::parse::json::start{
				sge::parse::json::array_or_object{
					sge::parse::json::array{
						sge::parse::json::element_vector{
							fcppt::make_recursive(
								sge::parse::json::make_value(
									sge::parse::json::int_type{
										42
									}
								)
							),
							fcppt::make_recursive(
								sge::parse::json::make_value(
									sge::parse::json::int_type{
										100
									}
								)
							)
						}
					}
				}
			}
		)
	);
}

TEST_CASE(
	"parse_json error",
	"[sge]"
)
{
	CHECK(
		sge::parse::json::parse_string(
			std::string{
				"{"
					"\"foo\": 42,"
					"\"bar\" :"
					"{"
						"\"inner\" : 5.5,"
						"\"booltest\" : true"
					"}"
				""
			}
		).has_failure()
	);
}
