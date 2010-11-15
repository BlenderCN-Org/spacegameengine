#include <sge/shader/variable.hpp>
#include <fcppt/string.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/math/matrix/output.hpp>
#include <fcppt/lexical_cast.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/io/ostringstream.hpp>
#include <boost/format.hpp>
#include <utility>

namespace
{
// NOTE: This might be very unsafe, better use karma for this. The
// point of this function is that the std::streams output "10.f" as
// "10", which is _not_ implicitly converted by glsl, so there's a
// type error
template<typename Source>
sge::renderer::glsl::string const
lexical_cast(
	Source const &s)
{
	// NOTE: Strictly speaking, this has to be a stringstream with
	// char_type == glsl::string::value_type, which I assume to be
	// std::string and char, respectively.
	fcppt::io::ostringstream ss;
	ss << std::showpoint << s;
	return ss.str();
}

class type_value_generator
{
public:
	typedef 
	std::pair
	<
		sge::renderer::glsl::string,
		sge::renderer::glsl::string
	> 
	result_type;

	result_type
	operator()(
		sge::shader::scalar const &v) const
	{
		return result_type("float","("+lexical_cast(v)+")");
	}

	result_type
	operator()(
		int const v) const
	{
		return result_type(FCPPT_TEXT("int"),"("+lexical_cast(v)+")");
	}

	// Those could be made into a template taking vector::static_
	result_type
	operator()(
		sge::shader::vec2 const &v) const
	{
		return result_type("vec2",lexical_cast(v));
	}

	result_type
	operator()(
		sge::shader::vec3 const &v) const
	{
		return result_type("vec3",lexical_cast(v));
	}

	result_type
	operator()(
		sge::shader::vec4 const &v) const
	{
		return result_type("vec4",lexical_cast(v));
	}

	result_type
	operator()(
		sge::shader::mat4 const &v) const 
	{
		return result_type("mat4",lexical_cast(v));
	}
};

sge::renderer::glsl::string const
generate_declaration(
	sge::renderer::glsl::string const &name,
	sge::shader::variable_type::type const t,
	sge::shader::value_type const &v)
{
	sge::renderer::glsl::string s;

	switch (t)
	{
		case sge::shader::variable_type::uniform:
			s = "uniform ";
			break;
		case sge::shader::variable_type::const_:
			s = "const ";
			break;
	}

	std::pair
	<
		sge::renderer::glsl::string,
		sge::renderer::glsl::string
	> const type_value = 
		fcppt::variant::apply_unary(
			type_value_generator(),
			v);

	s += type_value.first + " " + name;

	switch (t)
	{
		case sge::shader::variable_type::uniform:
			s += ";";
			break;
		case sge::shader::variable_type::const_:
			s += 
				(boost::format(" = %s%s;")
					% type_value.first
					% type_value.second).str();
			break;
	}

	return s;
}
}

sge::shader::variable::variable(
	sge::renderer::glsl::string const &_name,
	variable_type::type const _type,
	value_type const &_initial_value)
:
	name_(
		_name),
	declaration_(
		generate_declaration(
			_name,
			_type,
			_initial_value)),
	type_(
		_type),
	initial_value_(
		_initial_value)
{
}

sge::renderer::glsl::string const
sge::shader::variable::declaration() const
{
	return declaration_;
}

sge::shader::variable_type::type
sge::shader::variable::type() const
{
	return type_;
}

sge::renderer::glsl::string const
sge::shader::variable::name() const
{
	return name_;
}

sge::shader::value_type const
sge::shader::variable::initial_value() const
{
	return initial_value_;
}