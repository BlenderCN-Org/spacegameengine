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


#include <sge/console/stdlib.hpp>
#include <sge/console/object.hpp>
#include <sge/console/exception.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/signal/connection_manager.hpp>
#include <fcppt/signal/shared_connection.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/text.hpp>
#include <fcppt/lexical_cast.hpp>
#include <boost/foreach.hpp>

sge::console::stdlib::stdlib(
	object &_object,
	print_callback const &_print,
	error_callback const &_error
)
:
	object_(_object),
	print_(_print),
	error_(_error),
		connections(
			fcppt::assign::make_container<
				fcppt::signal::connection_manager::container
			>
			(
				fcppt::signal::shared_connection(
					object_.insert(
						FCPPT_TEXT("get"),
						std::tr1::bind(
							&stdlib::fn_get,
							this,
							std::tr1::placeholders::_1
						),
						FCPPT_TEXT("get <name> - display value of <name>")
					)
				)
			)
			(
				fcppt::signal::shared_connection(
					object_.insert(
						FCPPT_TEXT("set"),
						std::tr1::bind(
							&stdlib::fn_set,
							this,
							std::tr1::placeholders::_1
						),
						FCPPT_TEXT("set <name> <value> - set <name> to <value>")
					)
				)
			)
			(
				fcppt::signal::shared_connection(
					object_.insert(
						FCPPT_TEXT("help"),
						std::tr1::bind(
							&stdlib::fn_help,
							this,
							std::tr1::placeholders::_1
						),
						FCPPT_TEXT("list available functions")
					)
				)
			)
			(
				fcppt::signal::shared_connection(
					object_.insert(
						FCPPT_TEXT("lsfuncs"),
						std::tr1::bind(
							&stdlib::fn_help,
							this,
							std::tr1::placeholders::_1
						),
						FCPPT_TEXT("list available functions")
					)
				)
			)
			(
				fcppt::signal::shared_connection(
					object_.insert(
						FCPPT_TEXT("lsvars"),
						std::tr1::bind(
							&stdlib::fn_lsvars,
							this,
							std::tr1::placeholders::_1
						),
						FCPPT_TEXT("list available variables with values")
					)
				)
			)
			(
				fcppt::signal::shared_connection(
					object_.insert(
						FCPPT_TEXT("man"),
						std::tr1::bind(
							&stdlib::fn_man,
							this,
							std::tr1::placeholders::_1
						),
						FCPPT_TEXT("usage: man <function> - display help to <function>")
					)
				)
			)
		)
{
}

void sge::console::stdlib::fn_get(arg_list const &v)
{
	if (v.size() == 1 || v[1].empty())
	{
		error_(FCPPT_TEXT("no variable given"));
		return;
	}
	fcppt::string const arg = v[1];
	variable_map const &vars = object_.variables();
	variable_map::const_iterator i = vars.find(arg);
	if (i == vars.end())
	{
		error_(FCPPT_TEXT("variable ")+arg+FCPPT_TEXT(" not found"));
		return;
	}
	print_(arg+FCPPT_TEXT('=')+(i->second->string()));
}

void sge::console::stdlib::fn_set(arg_list const &v)
{
	if (v.size() < 3 || v[1].empty())
	{
		error_(FCPPT_TEXT("not enough arguments or empty variable name"));
		return;
	}
	fcppt::string const arg = v[1];
	fcppt::string const value = v[2];
	variable_map &vars = object_.variables();
	variable_map::iterator i = vars.find(arg);
	if (i == vars.end())
	{
		error_(FCPPT_TEXT("variable ")+arg+FCPPT_TEXT(" not found"));
		return;
	}
	try
	{
		i->second->string(value);
	}
	catch (exception const &e)
	{
		error_(FCPPT_TEXT("error: ")+e.string());
		return;
	}
	print_(arg+FCPPT_TEXT('=')+(i->second->string()));
}

void sge::console::stdlib::fn_help(arg_list const &)
{
	function_map const &fns = object_.functions();

	print_(
		fcppt::lexical_cast<
			fcppt::string
		>(
			fns.size()
		)
		+ FCPPT_TEXT(" available functions:")
	);

	BOOST_FOREACH(function_map::const_reference p,fns)
		print_function(p);
}

void sge::console::stdlib::fn_lsvars(arg_list const &)
{
	variable_map const &vars = object_.variables();

	print_(
		fcppt::lexical_cast<
			fcppt::string
		>(
			vars.size()
		)
		+ FCPPT_TEXT(" available variables:")
	);

	BOOST_FOREACH(variable_map::const_reference p,vars)
		print_(p.first+FCPPT_TEXT('=')+p.second->string());
}

void sge::console::stdlib::fn_man(arg_list const &v)
{
	if (v.size() < 2 || v[1].empty())
	{
		error_(FCPPT_TEXT("no function given"));
		return;
	}

	function_map const &fns = object_.functions();

	function_map::const_iterator i = fns.find(v[1]);

	if (i == fns.end())
	{
		error_(FCPPT_TEXT("function \"")+v[1]+FCPPT_TEXT("\" not found"));
		return;
	}

	print_function(*i);
}

void sge::console::stdlib::print_function(function_map::const_reference p)
{
	if (p.second->description().empty())
		print_(p.first);
	else
		print_(p.first+FCPPT_TEXT(": ")+p.second->description());
}
