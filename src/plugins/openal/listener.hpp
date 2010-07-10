/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENAL_LISTENER_HPP_INCLUDED
#define SGE_OPENAL_LISTENER_HPP_INCLUDED

#include <sge/audio/listener.hpp>
#include <sge/audio/angle.hpp>
#include <fcppt/math/vector/basic_decl.hpp>

namespace sge
{
namespace openal
{
class listener : public sge::audio::listener
{
	public:
	listener();
	void pos(audio::vector const &);
	audio::vector const pos() const;
	void vel(audio::vector const &);
	audio::vector const vel() const;
	void direction(audio::angle const &);
	audio::angle const direction() const;
	private:
	audio::vector pos_;
	audio::vector vel_;
	audio::angle angle_;
};
}
}

#endif
