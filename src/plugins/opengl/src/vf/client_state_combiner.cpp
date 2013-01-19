/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/opengl/disable_client_state.hpp>
#include <sge/opengl/enable_client_state.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/context/device/object_fwd.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/vf/attribute_context.hpp>
#include <sge/opengl/vf/client_state_combiner.hpp>
#include <sge/opengl/vf/context.hpp>
#include <sge/opengl/vf/disable_texcoords.hpp>
#include <sge/opengl/vf/disable_vertex_attrib_array.hpp>
#include <sge/opengl/vf/enable_texcoords.hpp>
#include <sge/opengl/vf/enable_vertex_attrib_array.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <functional>
#include <iterator>
#include <fcppt/config/external_end.hpp>


namespace
{

template<
	typename Set,
	typename EnableFun,
	typename DisableFun
>
void
apply_difference(
	Set const &old_states,
	Set const &new_states,
	EnableFun,
	DisableFun
);

}

sge::opengl::vf::client_state_combiner::client_state_combiner(
	sge::opengl::context::system::object &_system_context,
	sge::opengl::context::device::object &_device_context
)
:
	system_context_(
		_system_context
	),
	vf_context_(
		opengl::context::use<
			vf::context
		>(
			_device_context
		)
	),
	attribute_context_(
		opengl::context::use<
			vf::attribute_context
		>(
			_system_context
		)
	),
	old_states_(
		vf_context_.state()
	),
	new_states_(
		old_states_
	)
{
}

void
sge::opengl::vf::client_state_combiner::enable(
	GLenum const _enum
)
{
	new_states_.enable(
		_enum
	);
}

void
sge::opengl::vf::client_state_combiner::disable(
	GLenum const _enum
)
{
	new_states_.disable(
		_enum
	);
}

void
sge::opengl::vf::client_state_combiner::enable_texture(
	renderer::texture::stage const _texture
)
{
	new_states_.enable_texture(
		_texture
	);
}

void
sge::opengl::vf::client_state_combiner::disable_texture(
	renderer::texture::stage const _texture
)
{
	new_states_.disable_texture(
		_texture
	);
}

void
sge::opengl::vf::client_state_combiner::enable_attribute(
	GLuint const _attribute
)
{
	new_states_.enable_attribute(
		_attribute
	);
}

void
sge::opengl::vf::client_state_combiner::disable_attribute(
	GLuint const _attribute
)
{
	new_states_.disable_attribute(
		_attribute
	);
}

sge::opengl::vf::client_state_combiner::~client_state_combiner()
{
	apply_difference(
		old_states_.normal_states(),
		new_states_.normal_states(),
		opengl::enable_client_state,
		opengl::disable_client_state
	);

	apply_difference(
		old_states_.texture_states(),
		new_states_.texture_states(),
		std::bind(
			sge::opengl::vf::enable_texcoords,
			std::ref(
				system_context_
			),
			std::placeholders::_1
		),
		std::bind(
			sge::opengl::vf::disable_texcoords,
			std::ref(
				system_context_
			),
			std::placeholders::_1
		)
	);

	apply_difference(
		old_states_.attribute_states(),
		new_states_.attribute_states(),
		std::bind(
			sge::opengl::vf::enable_vertex_attrib_array,
			std::ref(
				attribute_context_
			),
			std::placeholders::_1
		),
		std::bind(
			sge::opengl::vf::disable_vertex_attrib_array,
			std::ref(
				attribute_context_
			),
			std::placeholders::_1
		)
	);

	vf_context_.state(
		new_states_
	);
}

namespace
{

template<
	typename Set,
	typename EnableFun,
	typename DisableFun
>
void
apply_difference(
	Set const &_old_states,
	Set const &_new_states,
	EnableFun _enable, // nonconst because of VC++12
	DisableFun _disable // nonconst because of VC++12
)
{
	Set diff;

	std::set_difference(
		_old_states.begin(),
		_old_states.end(),
		_new_states.begin(),
		_new_states.end(),
		std::inserter(
			diff,
			diff.begin()
		)
	);

	for(
		typename Set::const_iterator it(
			diff.begin()
		);
		it != diff.end();
		++it
	)
		_disable(
			*it
		);

	diff.clear();

	std::set_difference(
		_new_states.begin(),
		_new_states.end(),
		_old_states.begin(),
		_old_states.end(),
		std::inserter(
			diff,
			diff.begin()
		)
	);

	for(
		typename Set::const_iterator it(
			diff.begin()
		);
		it != diff.end();
		++it
	)
		_enable(
			*it
		);
}

}
