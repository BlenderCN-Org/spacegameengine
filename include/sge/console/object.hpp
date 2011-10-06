/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_CONSOLE_OBJECT_HPP_INCLUDED
#define SGE_CONSOLE_OBJECT_HPP_INCLUDED

#include <sge/console/callback/parameters_fwd.hpp>
#include <sge/console/fallback.hpp>
#include <sge/console/error_callback.hpp>
#include <sge/console/message_callback.hpp>
#include <sge/console/fallback_signal.hpp>
#include <sge/console/function_map.hpp>
#include <sge/console/arg_list.hpp>
#include <sge/console/symbol.hpp>
#include <sge/font/text/string.hpp>
#include <sge/font/text/char_type.hpp>
#include <sge/class_symbol.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace console
{

class SGE_CLASS_SYMBOL object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	SGE_CONSOLE_SYMBOL explicit
	object(
		font::text::char_type prefix
	);

	SGE_CONSOLE_SYMBOL fcppt::signal::auto_connection
	insert(
		callback::parameters const &
	);

	SGE_CONSOLE_SYMBOL fcppt::signal::auto_connection
	register_fallback(
		fallback const &
	);

	SGE_CONSOLE_SYMBOL fcppt::signal::auto_connection
	register_error_callback(
		error_callback const &
	);

	SGE_CONSOLE_SYMBOL fcppt::signal::auto_connection
	register_message_callback(
		message_callback const &
	);

	SGE_CONSOLE_SYMBOL void
	eval(
		font::text::string const &
	);

	SGE_CONSOLE_SYMBOL void
	eval(
		console::arg_list const &
	);

	SGE_CONSOLE_SYMBOL function_map const &
	functions() const;

	SGE_CONSOLE_SYMBOL font::text::char_type
	prefix() const;

	SGE_CONSOLE_SYMBOL void
	emit_error(
		font::text::string const &
	);

	SGE_CONSOLE_SYMBOL void
	emit_message(
		font::text::string const &
	);
private:
	fcppt::signal::object<error_callback_fn> error_;
	fcppt::signal::object<message_callback_fn> message_;
	font::text::char_type const prefix_;
	function_map funcs_;
	fallback_signal fallback_;
	fcppt::signal::scoped_connection help_connection_,man_connection_;

	void
	help_callback(
		arg_list const &);

	void
	man_callback(
		arg_list const &);

	void
	remove_function(
		font::text::string const &);
};

}
}

#endif
