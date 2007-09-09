/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_ICONV_DETAIL_HPP_INCLUDED
#define SGE_ICONV_DETAIL_HPP_INCLUDED

#include <cstddef>
#include <cerrno>
#include <string>
#include <boost/array.hpp>
#include <boost/noncopyable.hpp>
#include "../iconv_types.hpp"
#include <iconv.h>

namespace sge
{

struct iconv_instance : boost::noncopyable {
	iconv_instance(const std::string &from, const std::string &to);
	~iconv_instance();
	std::size_t convert(const char **inbuf, std::size_t *inbytes, char **outbuf, std::size_t *outbytes) const;
private:
	iconv_t conv;
	const std::string from,
	                    to;
};

const encoding internal_encoding = enc_wstring_literal;

std::string encoding_to_string(const sge::encoding& to);

template<typename To, typename From>
To _iconv(const From& input, const sge::encoding from, const sge::encoding to, const typename To::allocator_type& alloc = typename To::allocator_type())
{
	const iconv_instance ic(encoding_to_string(from), encoding_to_string(to));
	To output(alloc);
	
	const std::size_t buf_size = 512;
	boost::array<char,buf_size> arr;

	const char *ib = reinterpret_cast<const char*>(input.data());
	std::size_t in_size  = sizeof(typename From::value_type) * input.size();
	while(in_size)
	{
		std::size_t out_size = buf_size;
		char *ob = arr.c_array();
		ic.convert(&ib, &in_size, &ob, &out_size);

		const std::size_t bytes_written = buf_size - out_size;

		const typename To::const_pointer dest(reinterpret_cast<typename To::const_pointer>(arr.data()));
		output += To(dest, dest + bytes_written / sizeof(typename To::value_type));
	}

	return output;
}

}

#endif
