/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_CONSOLE_IMPL_EVAL_GRAMMAR_HPP_INCLUDED
#define SGE_CONSOLE_IMPL_EVAL_GRAMMAR_HPP_INCLUDED

#include <sge/console/arg_list.hpp>
#include <sge/console/impl/eval_grammar_fwd.hpp>
#include <sge/font/char_type.hpp>
#include <sge/font/string.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/parse/epsilon.hpp>
#include <fcppt/parse/grammar_decl.hpp>


namespace sge
{
namespace console
{
namespace impl
{

class eval_grammar final
:
public
	fcppt::parse::grammar<
		sge::console::arg_list,
		sge::font::char_type,
		fcppt::parse::epsilon
	>
{
	FCPPT_NONCOPYABLE(
		eval_grammar
	);
public:
	eval_grammar();

	~eval_grammar();
private:
	base_type<
		sge::font::string
	> word_;

	base_type<
		sge::font::string
	> quoted_string_;

	base_type<
		sge::font::string
	> argument_;

	base_type<
		sge::console::arg_list
	> start_;
};

}
}
}

#endif
