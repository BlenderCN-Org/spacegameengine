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


#include <sge/log/context.hpp>
#include <sge/log/object.hpp>
#include <sge/log/global_context.hpp>
#include <sge/log/global.hpp>
#include <sge/log/parameters/root.hpp>
#include <sge/log/parameters/inherited.hpp>
#include <sge/log/headers.hpp>
#include <sge/mainloop/catch_block.hpp>
#include <sge/function/object.hpp>
#include <sge/optional_impl.hpp>
#include <sge/text.hpp>
#include <sge/cout.hpp>
#include <sge/assert.hpp>
#include <tr1/functional>

int main()
try
{
	sge::log::context context_;

	sge::log::object logger(
		sge::log::parameters::root(
			sge::cout
		)
		.enabled(
			true
		)
		.context(
			context_
		)
		.prefix(
			SGE_TEXT("sge")
		)
		.level(
			sge::log::level::debug
		)
		.create()
	);

	sge::log::object child_logger(
		sge::log::parameters::inherited(
			logger,
			SGE_TEXT("child")
		)
	);

	sge::log::object *const ref(
		context_.find(
			logger.context_location().location()
		)
	);

	SGE_ASSERT(ref);

	SGE_LOG_INFO(
		*ref,
		sge::log::_
			<< SGE_TEXT("test output!")
	);

	sge::log::object *const child_ref(
		context_.find(
			sge::log::location(
				SGE_TEXT("sge")
			)
			+ SGE_TEXT("child")
		)
	);

	SGE_ASSERT(child_ref);

	sge::cout
		<< SGE_TEXT("location of child: ")
		<< child_ref->context_location().location().string()
		<< SGE_TEXT('\n');

	SGE_LOG_INFO(
		*child_ref,
		sge::log::_
			<< SGE_TEXT("child output!")
	);

	context_.apply(
		logger.context_location().location(),
		std::tr1::bind(
			&sge::log::object::enable,
			std::tr1::placeholders::_1,
			false
		)
	);

	SGE_LOG_INFO(
		*child_ref,
		sge::log::_
			<< SGE_TEXT("shouldn't be shown!")
	);

	sge::log::global();

	sge::log::object *const global_ref(
		sge::log::global_context().find(
			sge::log::location(
				SGE_TEXT("sge")
			)
		)
	);

	SGE_ASSERT(global_ref);

	SGE_LOG_WARNING(
		*global_ref,
		sge::log::_
			<< SGE_TEXT("Test global warning log!")
	);
}
SGE_MAINLOOP_CATCH_BLOCK
