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


#ifndef SGE_OPENAL_BUFFER_HOLDER_HPP_INCLUDED
#define SGE_OPENAL_BUFFER_HOLDER_HPP_INCLUDED

#include <sge/openal/buffer_id.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/log/object_fwd.hpp>


namespace sge
{
namespace openal
{

class buffer_holder
{
	FCPPT_NONCOPYABLE(
		buffer_holder
	);
public:
	explicit
	buffer_holder(
		fcppt::log::object &
	);

	~buffer_holder();

	sge::openal::buffer_id
	get() const;
private:
	fcppt::log::object &log_;

	sge::openal::buffer_id const buffer_;
};

}
}

#endif
