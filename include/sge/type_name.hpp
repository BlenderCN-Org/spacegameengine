#ifndef SGE_TYPE_NAME_HPP_INCLUDED
#define SGE_TYPE_NAME_HPP_INCLUDED

#include <sge/string.hpp>
#include <sge/type_info.hpp>
#include <sge/export.hpp>

namespace sge
{

SGE_SYMBOL string const
type_name(
	type_info const &);

}

#endif
