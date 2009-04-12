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


#include <sge/parse/json/parse.hpp>
#include <sge/string.hpp>
#include <sge/text.hpp>
#include <sge/cerr.hpp>
#include <sge/cout.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <boost/foreach.hpp>
#include <cstdlib>

namespace
{

/*
template<
	typename Out
>
struct json_output
:
karma::grammar<
	Out,
	sge::parse::json::object
> {
	json_output()
	:
		json_output::base_type(
			object_
		)
	{
		member_ %=
			lit(at_c<0>(_r0))
			<< value_;

		object_ %=
			char_(SGE_TEXT('{'))
			<< (*member_)
			<< char_(SGE_TEXT('}'));
	}
private:
	boost::spirit::karma::rule<
		Out,
		sge::parse::json::object()
	> object_;
}
*/

template<
	typename T
>
void print(
	T const &t)
{
	sge::cout << t;
}

void print(
	sge::parse::json::null const &)
{
	sge::cout << SGE_TEXT("null");
}

void print(
	sge::parse::json::object const &obj);
void print(
	sge::parse::json::value const &obj);

void print(
	sge::parse::json::array const &a)
{
	sge::cout << SGE_TEXT('[');
	BOOST_FOREACH(
		sge::parse::json::array::element_vector::const_reference r,
		a.elements
	)
	{
		print(r);
		sge::cout << SGE_TEXT(',');
	}

	sge::cout << SGE_TEXT(']');
}

struct output_visitor : boost::static_visitor<> {
	template<
		typename T
	>
	void operator()(
		T const &t) const
	{
		print(t);
	}
};

void print(
	sge::parse::json::value const &val)
{
	boost::apply_visitor(
		output_visitor(),
		val
	);
}

void print(
	sge::parse::json::object const &obj)
{
	BOOST_FOREACH(
		sge::parse::json::object::member_vector::const_reference r,
		obj.members
	)
	{
		sge::cout
			<< SGE_TEXT('{')
			<< r.name
			<< SGE_TEXT(": ");
		
		print(r.value_);

		sge::cout
			<< SGE_TEXT('}');
	}
}

}

int main()
{
	sge::string const test(
		SGE_TEXT("{ \"foo\": 42, \"bar\" : { \"inner\" : 5.5 } }")
	);

	sge::string::const_iterator beg(
		test.begin()
	);

	sge::parse::json::object result;

	if(!sge::parse::json::parse(
		beg,
		test.end(),
		result
	))
	{
		sge::cerr << SGE_TEXT("failure\n");
		return EXIT_FAILURE;
	}

	print(
		result
	);

	sge::cout << SGE_TEXT('\n');
}
