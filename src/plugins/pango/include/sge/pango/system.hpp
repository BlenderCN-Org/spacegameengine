/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_PANGO_SYSTEM_HPP_INCLUDED
#define SGE_PANGO_SYSTEM_HPP_INCLUDED

#include <sge/font/added_unique_ptr.hpp>
#include <sge/font/object_unique_ptr.hpp>
#include <sge/font/parameters_fwd.hpp>
#include <sge/font/system.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace pango
{

class system
:
	public sge::font::system
{
	FCPPT_NONCOPYABLE(
		system
	);
public:
	system();

	~system()
	override;
private:
	sge::font::object_unique_ptr
	create_font(
		sge::font::parameters const &
	)
	override;

	sge::font::added_unique_ptr
	add_font(
		boost::filesystem::path const &
	)
	override;
};

}
}

#endif
