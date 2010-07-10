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


#ifndef SGE_MAINLOOP_ASIO_IO_SERVICE_HPP_INCLUDED
#define SGE_MAINLOOP_ASIO_IO_SERVICE_HPP_INCLUDED

#include <sge/mainloop/io_service.hpp>
#include <sge/symbol.hpp>
#include <boost/asio/io_service.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace mainloop
{

class asio_io_service
:
	public mainloop::io_service
{
	FCPPT_NONCOPYABLE(asio_io_service)
public:
	SGE_SYMBOL
	asio_io_service();

	SGE_SYMBOL
	~asio_io_service();

	SGE_SYMBOL
	void
	run_one();

	SGE_SYMBOL
	void
	run();

	SGE_SYMBOL
	void
	poll();

	SGE_SYMBOL
	void
	stop();

	SGE_SYMBOL
	void
	reset();
private:
	boost::asio::io_service io_service_;
};

}
}

#endif
