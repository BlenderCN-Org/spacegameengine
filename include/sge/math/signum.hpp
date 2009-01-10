#ifndef SGE_MATH_SIGNUM_HPP_INCLUDED
#define SGE_MATH_SIGNUM_HPP_INCLUDED

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_unsigned.hpp>

namespace sge
{
namespace math
{

template<
	typename T
>
inline typename boost::disable_if<boost::is_unsigned<T>,T>::type
signum(
	T const t)
{
	if (t > static_cast<T>(0))
		return static_cast<T>(1);
	if (t < static_cast<T>(0))
		return static_cast<T>(-1);
	return static_cast<T>(0);
}

template<
	typename T
>
inline typename boost::enable_if<boost::is_unsigned<T>, T>::type
signum(
	T const t)
{
	return t != static_cast<T>(0)
		? static_cast<T>(1)
		: static_cast<T>(0);
}

}
}

#endif
