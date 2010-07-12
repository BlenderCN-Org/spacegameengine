/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../get.hpp"
#include "../type.hpp"
#include <sge/renderer/exception.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/text.hpp>

namespace
{

template<
	bool Native
>
struct get_uniform_iv;

template<>
struct get_uniform_iv<
	true
>
{
	static PFNGLGETUNIFORMIVPROC
	get();
};

template<>
struct get_uniform_iv<
	false
>
{
	static PFNGLGETUNIFORMIVPROC
	get();
};

template<
	bool Native
>
struct get_uniform_fv;

template<>
struct get_uniform_fv<
	true
>
{
	static PFNGLGETUNIFORMFVPROC
	get();
};

template<>
struct get_uniform_fv<
	false
>
{
	static PFNGLGETUNIFORMFVPROC
	get();
};

template<
	typename T
>
struct element_count;

template<>
struct element_count<
	sge::renderer::glsl::uniform::int_value_type::type
>
{
	static sge::renderer::size_type
	get(
		sge::opengl::glsl::uniform::element_type::type
	);
};

template<>
struct element_count<
	sge::renderer::glsl::uniform::float_value_type::type
>
{
	static sge::renderer::size_type
	get(
		sge::opengl::glsl::uniform::element_type::type
	);
};

template<
	typename T
>
struct to_type;

template<>
struct to_type<
	sge::renderer::glsl::uniform::int_value_type::type
>
{
	static sge::renderer::glsl::uniform::int_value_type::type
	get(
		sge::opengl::glsl::uniform::element_type::type
	);
};

template<>
struct to_type<
	sge::renderer::glsl::uniform::float_value_type::type
>
{
	static sge::renderer::glsl::uniform::float_value_type::type
	get(
		sge::opengl::glsl::uniform::element_type::type
	);
};

template<
	bool Native,
	typename ValueType,
	typename Function
>
sge::renderer::glsl::uniform::value const
get_impl(
	typename sge::opengl::glsl::traits<Native>::handle const program,
	GLint const location,
	sge::opengl::glsl::uniform::type const &t,
	Function const &function
)
{
	typedef typename ValueType::element_type element_type;

	sge::renderer::size_type const elements(
		element_count<
			element_type
		>::get(
			t.element_type()
		)
	);

	typename ValueType::data_type data(
		elements * t.elements()
	);

	for(
		sge::opengl::glsl::uniform::type::size_type i = 0;
		i < t.elements();
		++i
	)
		function(
			program,
			location,
			data.data() + i * elements
		);

	return sge::renderer::glsl::uniform::value(
		ValueType(
			data,
				elements,
			to_type<
				element_type
			>::get(
				t.element_type()
			)
		)
	);
}

}

template<
	bool Native
>
sge::renderer::glsl::uniform::value const
sge::opengl::glsl::uniform::get(
	typename traits<Native>::handle const program,
	GLint const location,
	type const &t
)
{
	switch(t.element_type())
	{
	case element_type::int1:
	case element_type::int2:
	case element_type::int3:
	case element_type::int4:
		return get_impl<
			Native,
			renderer::glsl::uniform::int_value
		>(
			program,
			location,
			t,
			get_uniform_iv<
				Native
			>::get()
		);
	case element_type::float1:
	case element_type::float2:
	case element_type::float3:
	case element_type::float4:
	case element_type::matrix2x2:
	case element_type::matrix3x3:
	case element_type::matrix4x4:
	case element_type::matrix2x3:
	case element_type::matrix3x2:
	case element_type::matrix2x4:
	case element_type::matrix4x2:
	case element_type::matrix3x4:
	case element_type::matrix4x3:
		return get_impl<
			Native,
			renderer::glsl::uniform::float_value
		>(
			program,
			location,
			t,
			get_uniform_fv<
				Native
			>::get()
		);
	case element_type::nothing:
		break;
	}

	throw renderer::exception(
		FCPPT_TEXT("Invalid variable type!")
	);
}

namespace
{

PFNGLGETUNIFORMIVPROC
get_uniform_iv<true>::get()
{
	return glGetUniformiv;
}

PFNGLGETUNIFORMIVPROC
get_uniform_iv<false>::get()
{
	return glGetUniformivARB;
}

PFNGLGETUNIFORMFVPROC
get_uniform_fv<true>::get()
{
	return glGetUniformfv;
}

PFNGLGETUNIFORMFVPROC
get_uniform_fv<false>::get()
{
	return glGetUniformfvARB;
}

sge::renderer::size_type
element_count<
	sge::renderer::glsl::uniform::int_value_type::type
>::get(
	sge::opengl::glsl::uniform::element_type::type const _type
)
{
	namespace et = sge::opengl::glsl::uniform::element_type;

	switch(_type)
	{
	case et::int1:
		return 1;
	case et::int2:
		return 2;
	case et::int3:
		return 3;
	case et::int4:
		return 4;
	case et::nothing:
	case et::float1:
	case et::float2:
	case et::float3:
	case et::float4:
	case et::matrix2x2:
	case et::matrix3x3:
	case et::matrix4x4:
	case et::matrix2x3:
	case et::matrix3x2:
	case et::matrix2x4:
	case et::matrix4x2:
	case et::matrix3x4:
	case et::matrix4x3:
		break;
	}

	throw sge::renderer::exception(
		FCPPT_TEXT("Invalid int type!")
	);
}

sge::renderer::size_type
element_count<
	sge::renderer::glsl::uniform::float_value_type::type
>::get(
	sge::opengl::glsl::uniform::element_type::type const _type
)
{
	namespace et = sge::opengl::glsl::uniform::element_type;

	switch(_type)
	{
	case et::float1:
		return 1;
	case et::float2:
		return 2;
	case et::float3:
		return 3;
	case et::float4:
		return 4;
	case et::matrix2x2:
		return 4;
	case et::matrix3x3:
		return 9;
	case et::matrix4x4:
		return 16;
	case et::matrix2x3:
	case et::matrix3x2:
		return 6;
	case et::matrix2x4:
	case et::matrix4x2:
		return 8;
	case et::matrix3x4:
	case et::matrix4x3:
		return 12;
	case et::nothing:
	case et::int1:
	case et::int2:
	case et::int3:
	case et::int4:
		break;
	}

	throw sge::renderer::exception(
		FCPPT_TEXT("Invalid float type!")
	);
}

sge::renderer::glsl::uniform::int_value_type::type
to_type<
	sge::renderer::glsl::uniform::int_value_type::type
>::get(
	sge::opengl::glsl::uniform::element_type::type const _type
)
{
	namespace et = sge::opengl::glsl::uniform::element_type;
	namespace ivt = sge::renderer::glsl::uniform::int_value_type;

	switch(_type)
	{
	case et::int1:
		return ivt::int1;
	case et::int2:
		return ivt::int2;
	case et::int3:
		return ivt::int3;
	case et::int4:
		return ivt::int4;
	case et::nothing:
	case et::float1:
	case et::float2:
	case et::float3:
	case et::float4:
	case et::matrix2x2:
	case et::matrix3x3:
	case et::matrix4x4:
	case et::matrix2x3:
	case et::matrix3x2:
	case et::matrix2x4:
	case et::matrix4x2:
	case et::matrix3x4:
	case et::matrix4x3:
		break;
	}

	throw sge::renderer::exception(
		FCPPT_TEXT("Invalid int element!")
	);
}

sge::renderer::glsl::uniform::float_value_type::type
to_type<
	sge::renderer::glsl::uniform::float_value_type::type
>::get(
	sge::opengl::glsl::uniform::element_type::type const _type
)
{
	namespace et = sge::opengl::glsl::uniform::element_type;
	namespace fvt = sge::renderer::glsl::uniform::float_value_type;

	switch(_type)
	{
	case et::float1:
		return fvt::float1;
	case et::float2:
		return fvt::float2;
	case et::float3:
		return fvt::float3;
	case et::float4:
		return fvt::float4;
	case et::matrix2x2:
		return fvt::matrix2x2;
	case et::matrix3x3:
		return fvt::matrix3x3;
	case et::matrix4x4:
		return fvt::matrix4x4;
	case et::matrix2x3:
		return fvt::matrix2x3;
	case et::matrix3x2:
		return fvt::matrix3x2;
	case et::matrix2x4:
		return fvt::matrix2x4;
	case et::matrix4x2:
		return fvt::matrix4x2;
	case et::matrix3x4:
		return fvt::matrix3x4;
	case et::matrix4x3:
		return fvt::matrix4x3;
	case et::nothing:
	case et::int1:
	case et::int2:
	case et::int3:
	case et::int4:
		break;
	}

	throw sge::renderer::exception(
		FCPPT_TEXT("Invalid float type!")
	);
}

}

#define SGE_OPENGL_INSTANTIATE_GLSL_GET(x)\
template sge::renderer::glsl::uniform::value const \
sge::opengl::glsl::uniform::get<x>(\
	sge::opengl::glsl::traits<x>::handle,\
	GLint,\
	sge::opengl::glsl::uniform::type const &\
);

SGE_OPENGL_INSTANTIATE_GLSL_GET(true)
SGE_OPENGL_INSTANTIATE_GLSL_GET(false)

#undef SGE_OPENGL_INSTANTIATE_GLSL_GET
