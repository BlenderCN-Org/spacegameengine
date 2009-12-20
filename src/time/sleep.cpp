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


#include <sge/time/sleep.hpp>
#include <sge/time/unit.hpp>
#include <fcppt/chrono/duration_impl.hpp>
#include <fcppt/chrono/duration_cast.hpp>
#include <fcppt/ratio.hpp>
#include <fcppt/config.h>
#ifdef FCPPT_WINDOWS_PLATFORM
#include <sge/windows/windows.hpp>
#elif FCPPT_POSIX_PLATFORM
#include <unistd.h>
#endif

void
sge::time::sleep(
	duration const &res
)
{
#ifdef FCPPT_WINDOWS_PLATFORM
	Sleep(
		static_cast<
			DWORD
		>(
			fcppt::chrono::duration_cast<
				fcppt::chrono::duration<
					unit,
					fcppt::milli
				>
			>(
				res
			).count()
		)
	);
#elif FCPPT_POSIX_PLATFORM
	usleep(
		static_cast<
			useconds_t
		>(
			fcppt::chrono::duration_cast<
				fcppt::chrono::duration<
					unit,
					fcppt::micro
				>
			>(
				res
			).count()
		)
	);
#else
#error "Implement me!"
#endif
}
