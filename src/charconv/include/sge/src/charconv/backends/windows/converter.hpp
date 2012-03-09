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


#ifndef SGE_CHARCONV_BACKENDS_WINDOWS_CONVERTER_HPP_INCLUDED
#define SGE_CHARCONV_BACKENDS_WINDOWS_CONVERTER_HPP_INCLUDED

#include <sge/charconv/conversion_status.hpp>
#include <sge/charconv/converter.hpp>
#include <sge/charconv/dest_encoding.hpp>
#include <sge/charconv/input_range.hpp>
#include <sge/charconv/output_range.hpp>
#include <sge/charconv/source_encoding.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace charconv
{
namespace backends
{
namespace windows
{

class converter
:
	public sge::charconv::converter
{
	FCPPT_NONCOPYABLE(
		converter
	);
public:
	converter(
		sge::charconv::source_encoding const &,
		sge::charconv::dest_encoding const &
	);

	~converter();

	sge::charconv::conversion_status::type
	convert(
		sge::charconv::input_range &,
		sge::charconv::output_range &
	);
};

}
}
}
}

#endif
