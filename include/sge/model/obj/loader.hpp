/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_MODEL_OBJ_LOADER_HPP_INCLUDED
#define SGE_MODEL_OBJ_LOADER_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/model/obj/instance_ptr.hpp>
#include <sge/model/obj/loader_fwd.hpp>
#include <sge/model/obj/symbol.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>



namespace sge
{
namespace model
{
namespace obj
{

class SGE_CLASS_SYMBOL loader
{
	FCPPT_NONCOPYABLE(
		loader
	);
protected:
	loader();
public:
	virtual obj::instance_ptr const
	load(
		boost::filesystem::path const &
	) = 0;

	SGE_MODEL_OBJ_SYMBOL
	virtual ~loader() = 0;
};

}
}
}

#endif
