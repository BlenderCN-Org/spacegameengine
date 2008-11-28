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


#ifndef SGE_PLUGIN_CONTEXT_BASE_HPP_INCLUDED
#define SGE_PLUGIN_CONTEXT_BASE_HPP_INCLUDED

#include "base.hpp"
#include "capabilities.hpp"
#include "../export.hpp"
#include "../string.hpp"
#include "../path.hpp"
#include <boost/weak_ptr.hpp>

namespace sge
{
namespace plugin
{

template<typename T> class context;

class context_base {
public:
	SGE_SYMBOL explicit context_base(
		sge::path const &p);

	SGE_SYMBOL string const &name() const;
	SGE_SYMBOL string const &description() const;
	SGE_SYMBOL unsigned version() const;
	SGE_SYMBOL capabilities::type type() const;
	SGE_SYMBOL sge::path const &path() const;
private:
	template<typename T> friend class context;
	boost::weak_ptr<base> ref;
	sge::path          path_;
	string             name_;
	string             description_;
	unsigned           version_;
	capabilities::type type_;
};

}
}

#endif
