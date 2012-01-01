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


#ifndef SGE_OPENAL_BUFFER_HPP_INCLUDED
#define SGE_OPENAL_BUFFER_HPP_INCLUDED

#include <sge/openal/buffer_holder.hpp>
#include <sge/audio/buffer.hpp>
#include <sge/audio/file_fwd.hpp>
#include <sge/audio/sound/base_ptr.hpp>
#include <sge/audio/sound/positional_parameters_fwd.hpp>
#include <sge/audio/sound/nonpositional_parameters_fwd.hpp>
#include <sge/audio/sound/positional_ptr.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace openal
{
class buffer
:
	public audio::buffer
{
	FCPPT_NONCOPYABLE(
		buffer
	);
public:
	explicit
	buffer(
		audio::file &
	);

	audio::sound::positional_ptr const
	create_positional(
		audio::sound::positional_parameters const &
	);

	audio::sound::base_ptr const
	create_nonpositional(
		audio::sound::nonpositional_parameters const &);

	~buffer();
private:
	buffer_holder const holder_;
};
}
}

#endif
