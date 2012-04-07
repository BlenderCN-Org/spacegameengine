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


#ifndef SGE_PARSE_INI_OUTPUT_GRAMMAR_HPP_INCLUDED
#define SGE_PARSE_INI_OUTPUT_GRAMMAR_HPP_INCLUDED

#include <sge/parse/encoding.hpp>
#include <sge/parse/ini/entry.hpp>
#include <sge/parse/ini/entry_vector.hpp>
#include <sge/parse/ini/section.hpp>
#include <sge/parse/ini/section_vector.hpp>
#include <sge/parse/ini/string.hpp>
#include <sge/parse/ini/detail/adapt_entry.hpp>
#include <sge/parse/ini/detail/adapt_section.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/text.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/spirit/include/karma_char.hpp>
#include <boost/spirit/include/karma_directive.hpp>
#include <boost/spirit/include/karma_grammar.hpp>
#include <boost/spirit/include/karma_nonterminal.hpp>
#include <boost/spirit/include/karma_operator.hpp>
#include <boost/spirit/include/karma_rule.hpp>
#include <boost/spirit/include/karma_string.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace parse
{
namespace ini
{
namespace output
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename Out
>
class grammar
:
	public boost::spirit::karma::grammar<
		Out,
		section_vector()
	>
{
	FCPPT_NONCOPYABLE(
		grammar
	);
public:
	grammar()
	:
		grammar::base_type(
			ini_
		),
		entry_(),
		header_(),
		section_(),
		ini_()
	{
		using encoding::char_;
		using boost::spirit::lit;

		entry_ %=
			*char_
			<< lit(FCPPT_TEXT(" = "))
			<< *char_;

		header_ %=
			lit(FCPPT_TEXT('['))
			<< +char_
			<< lit(FCPPT_TEXT(']'));

		section_ %=
			header_
			<< lit(FCPPT_TEXT('\n'))
			<< *(
				lit(FCPPT_TEXT('\t'))
				<< entry_
				<< lit(FCPPT_TEXT('\n'))
			);

		ini_ %=
			*section_;
	}

	~grammar()
	{
	}
private:
	boost::spirit::karma::rule<
		Out,
		entry()
	> entry_;

	boost::spirit::karma::rule<
		Out,
		string()
	> header_;

	boost::spirit::karma::rule<
		Out,
		section()
	> section_;

	boost::spirit::karma::rule<
		Out,
		section_vector()
	> ini_;
};

FCPPT_PP_POP_WARNING

}
}
}
}

#endif
