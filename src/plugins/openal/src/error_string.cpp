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


#include "../error_string.hpp"
#include <sge/text.hpp>

sge::string const
sge::openal::error_string(
	ALenum const error)
{
	switch (error)
	{
		case AL_NO_ERROR:
			return SGE_TEXT("no error in openal (maybe somewhere else)");
		case AL_INVALID_NAME:
			return SGE_TEXT("invalid name parameter");
		case AL_INVALID_ENUM:
			return SGE_TEXT("invalid parameter");
		case AL_INVALID_VALUE:
			return SGE_TEXT("invalid enum parameter value");
		case AL_INVALID_OPERATION:
			return SGE_TEXT("illegal call");
		case AL_OUT_OF_MEMORY:
			return SGE_TEXT("unable to allocate memory");
		default:
			return SGE_TEXT("Unknown");
	}
}

