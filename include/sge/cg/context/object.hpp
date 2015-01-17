/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_CG_CONTEXT_OBJECT_HPP_INCLUDED
#define SGE_CG_CONTEXT_OBJECT_HPP_INCLUDED

#include <sge/cg/detail/symbol.hpp>
#include <sge/cg/context/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cg.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace cg
{
namespace context
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	SGE_CG_DETAIL_SYMBOL
	object();

	SGE_CG_DETAIL_SYMBOL
	~object();

	SGE_CG_DETAIL_SYMBOL
	CGcontext
	get() const;
private:
	CGcontext const context_;
};

}
}
}

#endif
