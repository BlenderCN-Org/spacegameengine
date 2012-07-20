#ifndef SGE_SHADER_PARAMETER_MATRIX_DECL_HPP_INCLUDED
#define SGE_SHADER_PARAMETER_MATRIX_DECL_HPP_INCLUDED

#include <sge/cg/parameter/named.hpp>
#include <sge/cg/program/object_fwd.hpp>
#include <sge/shader/parameter/is_projection_matrix.hpp>
#include <sge/shader/parameter/matrix_fwd.hpp>
#include <sge/shader/parameter/name.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/math/matrix/static.hpp>


namespace sge
{
namespace shader
{
namespace parameter
{
template
<
	typename ValueType,
	fcppt::math::size_type M,
	fcppt::math::size_type N
>
class matrix
{
FCPPT_NONCOPYABLE(
	matrix);
public:
	typedef
	ValueType
	value_type;

	typedef typename
	fcppt::math::matrix::static_<value_type,M,N>::type
	matrix_type;

	static fcppt::math::size_type const rows =
		M;

	static fcppt::math::size_type const columns =
		N;

	matrix(
		sge::cg::program::object &,
		sge::shader::parameter::name const &,
		sge::shader::parameter::is_projection_matrix const &,
		matrix_type const &);

	void
	set(
		matrix_type const &);

	~matrix();
private:
	sge::cg::parameter::named const parameter_;
	sge::shader::parameter::is_projection_matrix const is_projection_matrix_;
};
}
}
}

#endif
