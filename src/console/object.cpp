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


#include <sge/console/exception.hpp>
#include <sge/console/function.hpp>
#include <sge/console/object.hpp>
#include <sge/console/callback/parameters.hpp>
#include <sge/font/text/lit.hpp>
#include <fcppt/insert_to_string.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/qi.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
sge::console::object::object(
	font::text::char_type const _prefix
)
:
	error_(),
	message_(),
	prefix_(
		_prefix),
	funcs_(),
	fallback_(),
	help_connection_(
		this->insert(
			callback::parameters(
				std::tr1::bind(
					&object::help_callback,
					this,
					std::tr1::placeholders::_1),
				callback::name(
					SGE_FONT_TEXT_LIT("help")))
				.short_description(
					SGE_FONT_TEXT_LIT("Display help message")))),
	man_connection_(
		this->insert(
			callback::parameters(
				std::tr1::bind(
					&object::man_callback,
					this,
					std::tr1::placeholders::_1),
				callback::name(
					SGE_FONT_TEXT_LIT("man")))
				.short_description(
					SGE_FONT_TEXT_LIT("Display information for a specific function"))))
{
}
FCPPT_PP_POP_WARNING

fcppt::signal::auto_connection
sge::console::object::insert(
	callback::parameters const &_params
)
{
	function_map::iterator i = funcs_.find(_params.name());

	if (i == funcs_.end())
	{
		typedef std::pair<
			function_map::iterator,
			bool
		> ret_type;

		ret_type const ret(
			fcppt::container::ptr::insert_unique_ptr_map(
				funcs_,
				_params.name(),
				fcppt::make_unique_ptr<
					function
				>(
					_params.short_description(),
					_params.long_description()
				)
			)
		);

		i = ret.first;

		FCPPT_ASSERT_ERROR(ret.second);
	}
	return
		i->second->signal().connect(
			_params.function(),
			std::tr1::bind(
				&object::remove_function,
				this,
				_params.name()));
}

fcppt::signal::auto_connection
sge::console::object::register_fallback(
	fallback const &c
)
{
	return fallback_.connect(c);
}

fcppt::signal::auto_connection
sge::console::object::register_error_callback(
	error_callback const &c
)
{
	return error_.connect(c);
}

fcppt::signal::auto_connection
sge::console::object::register_message_callback(
	message_callback const &c
)
{
	return message_.connect(c);
}

namespace
{
template <typename Iterator>
class eval_grammar : public boost::spirit::qi::grammar<
	Iterator,
	sge::console::arg_list()>
{
	FCPPT_NONCOPYABLE(
		eval_grammar
	);
public:
	eval_grammar() : eval_grammar::base_type(start)
	{
		namespace encoding = boost::spirit::standard_wide;

		using encoding::char_;
		using encoding::space;

		word %=
			+~space;

		quoted_string %=
			SGE_FONT_TEXT_LIT('"')
			>> +(~char_(SGE_FONT_TEXT_LIT('"')))
			>> SGE_FONT_TEXT_LIT('"');

		argument %=
			quoted_string
			| word;

		start %=
			argument % (+space);
	}

	~eval_grammar()
	{
	}

	boost::spirit::qi::rule<Iterator, sge::font::text::string()> word;
	boost::spirit::qi::rule<Iterator, sge::font::text::string()> quoted_string;
	boost::spirit::qi::rule<Iterator, sge::font::text::string()> argument;
	boost::spirit::qi::rule<Iterator, sge::console::arg_list()> start;
};
}

void
sge::console::object::eval(
	font::text::string const &sp
)
{
	if (sp.empty())
		return;

	if (sp[0] != prefix_)
	{
		fallback_(sp);
		return;
	}

	font::text::string const s = sp.substr(1);

	arg_list args;

	eval_grammar<
		font::text::string::const_iterator
	> grammar;

	font::text::string::const_iterator beg = s.begin();

	boost::spirit::qi::parse(
		beg,
		s.end(),
		grammar,
		args
	);

	object::eval(
		args
	);
}

void
sge::console::object::eval(
	console::arg_list const &args
)
{
	// just typing the prefix is not an error
	if(
		args.empty()
	)
		return;

	function_map::iterator const it(
		funcs_.find(
			args[0]
		)
	);

	if (
		it == funcs_.end()
	)
		throw console::exception(
			SGE_FONT_TEXT_LIT("couldn't find command \"")
			+
			args[0]
			+
			SGE_FONT_TEXT_LIT('"')
		);

	it->second->signal()(
		args,
		fcppt::ref(*this));
}

sge::console::function_map const &
sge::console::object::functions() const
{
	return funcs_;
}

sge::font::text::char_type
sge::console::object::prefix() const
{
	return prefix_;
}

void
sge::console::object::emit_error(
	font::text::string const &s)
{
	error_(
		s);
}

void
sge::console::object::emit_message(
	font::text::string const &s)
{
	message_(
		s);
}

void
sge::console::object::help_callback(
	arg_list const &)
{
	emit_message(
		fcppt::insert_to_string<font::text::string>(
			funcs_.size())
		+ SGE_FONT_TEXT_LIT(" available functions:"));

	for(
		function_map::const_iterator it(
			funcs_.begin()
		);
		it != funcs_.end();
		++it
	)
		this->emit_message(
			((*it)->first)
			+
			SGE_FONT_TEXT_LIT(": ")
			+
			(it->second)->short_description()
		);
}

void
sge::console::object::man_callback(
	arg_list const &v)
{
	if (v.size() < 2)
	{
		emit_error(
			SGE_FONT_TEXT_LIT("no function given"));
		return;
	}

	function_map const &fns =
		funcs_;

	function_map::const_iterator i =
		funcs_.find(
			v[1]);

	if (i == fns.end())
	{
		emit_error(
			SGE_FONT_TEXT_LIT("function \"")
			+ v[1]
			+ SGE_FONT_TEXT_LIT("\" not found")
		);

		return;
	}

	if (i->second->long_description().empty())
		emit_message(
			SGE_FONT_TEXT_LIT("No manpage available")
		);
	else
		emit_message(
			i->second->long_description());
}

void
sge::console::object::remove_function(
	font::text::string const &_name)
{
	function_map::iterator const it(
		funcs_.find(
			_name));

	FCPPT_ASSERT_PRE(
		it != funcs_.end());

	if(it->second->signal().empty())
		funcs_.erase(
			it);
}
