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


#include <sge/exception.hpp>
#include <sge/log/global.hpp>
#include <sge/renderer/const_optional_vertex_declaration.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/glsl/const_optional_program.hpp>
#include <sge/renderer/glsl/pixel_shader.hpp>
#include <sge/renderer/glsl/program.hpp>
#include <sge/renderer/glsl/scoped_attachment.hpp>
#include <sge/renderer/glsl/scoped_program.hpp>
#include <sge/renderer/glsl/string.hpp>
#include <sge/renderer/glsl/to_cvv.hpp>
#include <sge/renderer/glsl/vertex_shader.hpp>
#include <sge/renderer/glsl/uniform/single_value.hpp>
#include <sge/renderer/glsl/uniform/variable_ptr.hpp>
#include <sge/renderer/texture/const_optional_base.hpp>
#include <sge/shader/object.hpp>
#include <sge/shader/object_parameters.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/range/numeric.hpp>
#include <boost/spirit/home/phoenix/bind/bind_member_function.hpp>
#include <boost/spirit/home/phoenix/core/argument.hpp>
#include <boost/spirit/home/phoenix/operator/arithmetic.hpp>
#include <streambuf>
#include <fcppt/config/external_end.hpp>


namespace
{
// TODO: Replace by some lambda?
struct uniform_setter
{
public:
	// apply_unary needs this
	typedef void result_type;

	sge::renderer::glsl::uniform::variable_ptr variable_;

	explicit
	uniform_setter(
		sge::renderer::glsl::uniform::variable_ptr const _variable)
	:
		variable_(_variable)
	{
	}

	template<typename T>
	result_type
	operator()(
		T const &_value) const
	{
		sge::renderer::glsl::uniform::single_value(
			*variable_,
			_value);
	}

	result_type
	operator()(
		bool const _value) const
	{
		sge::renderer::glsl::uniform::single_value(
			*variable_,
			static_cast<sge::renderer::glsl::int_type>(
				_value));
	}

	result_type
	operator()(
		sge::shader::matrix const &m) const
	{
		sge::renderer::matrix4 value =
			m.value();

		switch(m.flags())
		{
			case sge::shader::matrix_flags::none:
				break;
			case sge::shader::matrix_flags::size:
				break;
			case sge::shader::matrix_flags::projection:
				value =
					sge::renderer::glsl::to_cvv(
						value);
				break;
		}

		sge::renderer::glsl::uniform::single_value(
			*variable_,
			value);
	}
};
}

sge::shader::object::object(
	shader::object_parameters const &p)
:
	renderer_(
		p.renderer()),
	vertex_declaration_(
		p.vertex_declaration()),
	program_(
		renderer_.create_glsl_program()),
	uniforms_(),
	uniform_matrices_(),
	samplers_()
{
	program_->vertex_declaration(
		vertex_declaration_);

	renderer::glsl::string const header =
		p.vertex_format_string().get() +
		boost::accumulate(
			p.variables(),
			sge::renderer::glsl::string(),
			boost::phoenix::arg_names::arg1 +
				boost::phoenix::bind(
					&variable::declaration,
					boost::phoenix::arg_names::arg2)) +
		boost::accumulate(
			p.samplers(),
			sge::renderer::glsl::string(),
			boost::phoenix::arg_names::arg1 +
				boost::phoenix::bind(
					&sampler::declaration,
					boost::phoenix::arg_names::arg2));


	sge::renderer::glsl::shader *current_shader =
		0;

	try
	{
		for(
			shader::object_parameters::shader_sequence::const_iterator it =
				p.vertex_shaders().begin();
			it != p.vertex_shaders().end();
			++it)
		{
			vertex_shaders_.push_back(
				renderer_.create_glsl_vertex_shader(
					boost::algorithm::replace_first_copy(
						*it,
						std::string("$$$HEADER$$$"),
						header)));

			current_shader =
				vertex_shaders_.back().get();

			vertex_shaders_.back()->compile();

			fcppt::container::ptr::push_back_unique_ptr(
				attachments_,
				fcppt::make_unique_ptr<renderer::glsl::scoped_attachment>(
					fcppt::ref(
						*program_),
					fcppt::cref(
						*vertex_shaders_.back())));
		}

		for(
			shader::object_parameters::shader_sequence::const_iterator it =
				p.fragment_shaders().begin();
			it != p.fragment_shaders().end();
			++it)
		{
			pixel_shaders_.push_back(
				renderer_.create_glsl_pixel_shader(
					boost::algorithm::replace_first_copy(
						*it,
						std::string("$$$HEADER$$$"),
						header)));

			current_shader =
				pixel_shaders_.back().get();

			vertex_shaders_.back()->compile();

			fcppt::container::ptr::push_back_unique_ptr(
				attachments_,
				fcppt::make_unique_ptr<renderer::glsl::scoped_attachment>(
					fcppt::ref(
						*program_),
					fcppt::cref(
						*pixel_shaders_.back())));
		}

		program_->link();
	}
	catch(sge::exception const &e)
	{
		throw
			sge::exception(
				FCPPT_TEXT("Shader error for shader \"")+
				p.name()+
				FCPPT_TEXT("\": \n")+
				e.string()+
				FCPPT_TEXT("\nShader source:\n")+
				fcppt::from_std_string(
					current_shader->source()));
	}

	sge::renderer::glsl::scoped_program scoped_shader_(
		renderer_,
		*program_);

	for(
		variable_sequence::const_iterator it(
			p.variables().begin()
		);
		it != p.variables().end();
		++it
	)
	{
		switch(it->type())
		{
			case shader::variable_type::constant:
				break;
			case shader::variable_type::uniform:
				uniforms_.insert(
					uniform_map::value_type(
						it->name(),
						program_->uniform(
							it->name())));

				update_uniform(
					it->name(),
					it->initial_value());
				break;
		}
	}

	sampler::texture_unit_type current_tu =
		static_cast<sampler::texture_unit_type>(0);

	for(
		sampler_sequence::const_iterator it(
			p.samplers().begin()
		);
		it != p.samplers().end();
		++it
	)
	{
		samplers_.push_back(
			*it);

		sge::renderer::glsl::uniform::single_value(
			*uniforms_.insert(
				uniform_map::value_type(
					it->name(),
					program_->uniform(it->name()))).first->second,
			current_tu);

		samplers_.back().texture_unit(
			current_tu);

		++current_tu;
	}

	if (!program_->info_log().empty())
	{
		FCPPT_LOG_INFO(
			log::global(),
			fcppt::log::_
				<< FCPPT_TEXT("Shader program error log: ")
				<< program_->info_log()
				<< FCPPT_TEXT("\n"));
	}
}

void
sge::shader::object::update_uniform(
	sge::renderer::glsl::string const &name,
	shader::value_variant const &v)
{
	uniform_map::iterator const i =
		uniforms_.find(name);

	if (i == uniforms_.end())
		throw exception(
			FCPPT_TEXT("Error in update_uniform: The uniform variable \"")+
			fcppt::from_std_string(
				name)+
			FCPPT_TEXT("\" was not found"));

	fcppt::variant::apply_unary(
		uniform_setter(
			i->second),
		v);
}

void
sge::shader::object::update_texture(
	sge::renderer::glsl::string const &name,
	texture_variant const &newtex)
{
	for(
		sampler_sequence::iterator it(
			samplers_.begin()
		);
		it != samplers_.end();
		++it
	)
	{
		if (it->name() == name)
		{
			it->texture(
				newtex);
			return;
		}
	}

	throw
		sge::exception(
			FCPPT_TEXT("The texture \"")+
			fcppt::from_std_string(name)+
			FCPPT_TEXT("\" you tried to update in a shader doesn't exist!"));
}

void
sge::shader::object::activate(
	shader::activation_method_field const &t)
{
	renderer_.glsl_program(
		sge::renderer::glsl::const_optional_program(
			*program_));

	if(t & shader::activation_method::textures)
	{
		for(
			sampler_sequence::const_iterator it(
				samplers_.begin()
			);
			it != samplers_.end();
			++it
		)
			renderer_.texture(
				sge::renderer::texture::const_optional_base(
					*it->texture()),
				sge::renderer::stage(
					it->texture_unit()));
	}

	if(t & shader::activation_method::vertex_declaration)
	{
		renderer_.vertex_declaration(
			sge::renderer::const_optional_vertex_declaration(
				vertex_declaration_));
	}
}

void
sge::shader::object::deactivate(
	shader::activation_method_field const &t)
{
	renderer_.glsl_program(
		sge::renderer::glsl::const_optional_program());

	if(t & shader::activation_method::textures)
	{
		for(
			sampler_sequence::const_iterator it(
				samplers_.begin()
			);
			it != samplers_.end();
			++it
		)
			renderer_.texture(
				sge::renderer::texture::const_optional_base(),
				sge::renderer::stage(
					it->texture_unit()));
	}

	if(t & shader::activation_method::vertex_declaration)
		renderer_.vertex_declaration(
			renderer::const_optional_vertex_declaration());
}

sge::shader::object::~object()
{
}
