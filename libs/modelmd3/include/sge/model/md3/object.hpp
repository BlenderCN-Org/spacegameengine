/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_MODEL_MD3_OBJECT_HPP_INCLUDED
#define SGE_MODEL_MD3_OBJECT_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/model/md3/index_sequence.hpp>
#include <sge/model/md3/normal_sequence.hpp>
#include <sge/model/md3/object_fwd.hpp>
#include <sge/model/md3/optional_normal_sequence.hpp>
#include <sge/model/md3/optional_texcoord_sequence.hpp>
#include <sge/model/md3/part_name_sequence.hpp>
#include <sge/model/md3/string.hpp>
#include <sge/model/md3/texcoord_sequence.hpp>
#include <sge/model/md3/vertex_sequence.hpp>
#include <sge/model/md3/detail/symbol.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace model
{
namespace md3
{

class SGE_CORE_DETAIL_CLASS_SYMBOL object
{
	FCPPT_NONCOPYABLE(
		object
	);
protected:
	SGE_MODEL_MD3_DETAIL_SYMBOL
	object();
public:
	virtual
	sge::model::md3::index_sequence
	indices(
		sge::model::md3::string const &name
	) const = 0;

	virtual
	sge::model::md3::vertex_sequence
	vertices(
		sge::model::md3::string const &name
	) const = 0;

	virtual
	sge::model::md3::optional_texcoord_sequence
	texcoords(
		sge::model::md3::string const &name
	) const = 0;

	virtual
	sge::model::md3::optional_normal_sequence
	normals(
		sge::model::md3::string const &name
	) const = 0;

	virtual
	sge::model::md3::part_name_sequence
	part_names() const = 0;

	SGE_MODEL_MD3_DETAIL_SYMBOL
	virtual
	~object();
};

}
}
}

#endif
