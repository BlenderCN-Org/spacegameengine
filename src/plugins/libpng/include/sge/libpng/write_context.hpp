/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_LIBPNG_WRITE_CONTEXT_HPP_INCLUDED
#define SGE_LIBPNG_WRITE_CONTEXT_HPP_INCLUDED

#include <sge/image/color/format.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/libpng/byte_vector.hpp>
#include <sge/libpng/context_base.hpp>
#include <sge/libpng/info.hpp>
#include <sge/libpng/png.hpp>
#include <sge/libpng/write_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace libpng
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

class write_context
:
	public context_base
{
	FCPPT_NONCOPYABLE(
		write_context
	);
public:
	write_context(
		boost::filesystem::path const &,
		image2d::dim const &,
		byte_vector const &,
		image::color::format
	);

	~write_context();
private:
	boost::filesystem::ofstream file_;

	byte_vector const &bytes_;

	image::color::format const format_;

	libpng::write_ptr const write_ptr_;

	libpng::info const info_;

	static void
	handle_write(
		png_structp,
		png_bytep,
		png_size_t
	);

	void
	handle_write_impl(
		png_bytep,
		png_size_t
	);

	static void
	handle_flush(
		png_structp
	);

	void
	handle_flush_impl();
};

FCPPT_PP_POP_WARNING

}
}

#endif
