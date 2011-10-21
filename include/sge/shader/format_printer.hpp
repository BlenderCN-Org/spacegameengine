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


#ifndef SGE_SHADER_FORMAT_PRINTER_HPP_INCLUDED
#define SGE_SHADER_FORMAT_PRINTER_HPP_INCLUDED

#include <sge/renderer/glsl/from_fcppt_string.hpp>
#include <sge/renderer/glsl/string.hpp>
#include <sge/renderer/vf/unspecified.hpp>
#include <sge/renderer/vf/vector.hpp>
#include <sge/renderer/vf/vertex_size.hpp>
#include <sge/shader/vector_to_string.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/format.hpp>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace shader
{
// It used in a for_each to iterate over all components of a format
// and store the result in a string
class format_printer
{
	FCPPT_NONASSIGNABLE(
		format_printer
	);
public:
	explicit
	format_printer(
		renderer::glsl::string &_s)
	: s(_s)
	{}

	template
	<
		typename T,
		typename Tag,
		renderer::vf::vertex_size N
	>
	typename
	boost::enable_if_c
	<
		N != 1,
		void
	>::type
	operator()(
		renderer::vf::unspecified
		<
			renderer::vf::vector<T,N>,Tag>)
	{
		s +=
			boost::str(
				boost::format("in %s %s;\n")
				% shader::vector_to_string<T,N>()
				% renderer::glsl::from_fcppt_string(
					Tag::name()));
	}

	template
	<
		typename T,
		typename Tag,
		renderer::vf::vertex_size N
	>
	typename
	boost::enable_if_c
	<
		N == 1,
		void
	>::type
	operator()(
		renderer::vf::unspecified
		<
			renderer::vf::vector<T,N>,Tag>)
	{
		s +=
			boost::str(
				boost::format("in float %s;\n")
				% renderer::glsl::from_fcppt_string(
					Tag::name()));
	}

	template<typename T>
	void
	operator()(T const &) const
	{
		// shaders don't need declarations
		// for non unspecified types
	}
private:
	renderer::glsl::string &s;
};
}
}

#endif
