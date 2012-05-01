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


#include <sge/cg/check_state.hpp>
#include <sge/cg/exception.hpp>
#include <sge/cg/context/object.hpp>
#include <sge/cg/profile/object.hpp>
#include <sge/cg/program/from_file_parameters.hpp>
#include <sge/cg/program/from_string_parameters.hpp>
#include <sge/cg/program/object.hpp>
#include <sge/src/cg/program/convert_source_type.hpp>
#include <fcppt/null_ptr.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cg.h>
#include <fcppt/config/external_end.hpp>


namespace
{

void
assert_program(
	CGprogram,
	fcppt::string
);

}

sge::cg::program::object::object(
	sge::cg::program::from_string_parameters const &_parameters
)
:
	profile_(
		_parameters.profile()
	),
	program_(
		::cgCreateProgram(
			_parameters.context().get(),
			sge::cg::program::convert_source_type(
				_parameters.source_type()
			),
			_parameters.source().get().c_str(),
			profile_.get(),
			_parameters.main_function().get().c_str(),
			_parameters.compile_options().get()
		)
	)
{
	::assert_program(
		program_,
		FCPPT_TEXT("cgCreateProgram")
	);
}

sge::cg::program::object::object(
	sge::cg::program::from_file_parameters const &_parameters
)
:
	profile_(
		_parameters.profile()
	),
	program_(
		::cgCreateProgramFromFile(
			_parameters.context().get(),
			sge::cg::program::convert_source_type(
				_parameters.source_type()
			),
			_parameters.path().string().c_str(),
			profile_.get(),
			_parameters.main_function().get().c_str(),
			_parameters.compile_options().get()
		)
	)
{
	::assert_program(
		program_,
		FCPPT_TEXT("cgCreateProgramFromFile")
	);
}

sge::cg::program::object::~object()
{
	::cgDestroyProgram(
		program_
	);
}

sge::cg::profile::object const &
sge::cg::program::object::profile() const
{
	return
		profile_;
}

CGprogram
sge::cg::program::object::get() const
{
	return
		program_;
}

namespace
{

void
assert_program(
	CGprogram const _program,
	fcppt::string const _what
)
{
	SGE_CG_CHECK_STATE(
		_what,
		sge::cg::exception
	)

	FCPPT_ASSERT_ERROR(
		_program
		!=
		fcppt::null_ptr()
	);
}

}