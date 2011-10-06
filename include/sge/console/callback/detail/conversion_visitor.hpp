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


#ifndef SGE_CONSOLE_CALLBACK_DETAIL_CONVERSION_VISITOR_HPP_INCLUDED
#define SGE_CONSOLE_CALLBACK_DETAIL_CONVERSION_VISITOR_HPP_INCLUDED

#include <sge/console/object.hpp>
#include <sge/console/arg_list.hpp>
#include <sge/font/text/lit.hpp>
#include <sge/font/text/from_fcppt_string.hpp>
#include <fcppt/lexical_cast.hpp>
#include <fcppt/bad_lexical_cast.hpp>
#include <fcppt/type_name.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/fusion/sequence/intrinsic/at_c.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <typeinfo>
#include <fcppt/config/external_end.hpp>

namespace sge
{
namespace console
{
namespace callback
{
namespace detail
{
template<typename ParameterTypes>
struct conversion_visitor
{
public:
	explicit
	conversion_visitor(
		console::object &_console,
		ParameterTypes &_parameters,
		console::arg_list const &_args)
	:
		console_(
			_console),
		parameters_(
			_parameters),
		args_(
			_args)
	{

	}

	template<typename Index>
	void
	operator()() const
	{
		typedef typename
		boost::remove_reference
		<
			typename boost::fusion::result_of::at_c
			<
				ParameterTypes,
				Index::value
			>::type
		>::type
		result_type;

		try
		{
			boost::fusion::at_c<Index::value>(parameters_) = 
				fcppt::lexical_cast<result_type>(
					args_[Index::value+1]);
		}
		catch(fcppt::bad_lexical_cast const &)
		{
			console_.emit_error(
				SGE_FONT_TEXT_LIT("Couldn't convert argument ")+
				fcppt::lexical_cast<sge::font::text::string>(
					Index::value)+
				SGE_FONT_TEXT_LIT(" to type ")+
				sge::font::text::from_fcppt_string(
					fcppt::type_name(
						typeid(
							result_type))));
		}
	}
private:
	console::object &console_;
	ParameterTypes &parameters_;
	console::arg_list const &args_;
};
}
}
}
}

#endif
