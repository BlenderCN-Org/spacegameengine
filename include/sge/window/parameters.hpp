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


#ifndef SGE_WINDOW_PARAMETERS_HPP_INCLUDED
#define SGE_WINDOW_PARAMETERS_HPP_INCLUDED

#include "dim_type.hpp"
#include "../string.hpp"
#include "../export.hpp"
#include <sge/math/dim/basic_impl.hpp>
#include <boost/optional.hpp>

namespace sge
{
namespace window
{

struct parameters {
	SGE_SYMBOL static string const default_class;

	SGE_SYMBOL explicit parameters(
		string const &title,
		string const &class_name = default_class);
	SGE_SYMBOL parameters(
		string const &title,
		dim_type const &dim,
		string const &class_name = default_class);
	
	SGE_SYMBOL string const &
	title() const;

	SGE_SYMBOL string const &
	class_name() const;

	typedef boost::optional<
		dim_type
	> optional_dim;

	SGE_SYMBOL optional_dim const &
	dim() const;

	SGE_SYMBOL void
	dim(
		dim_type const &);
private:
	string title_;
	optional_dim dim_;
	string class_name_;
};

}
}

#endif
