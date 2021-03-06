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


#include <sge/charconv/utf8_string.hpp>
#include <sge/parse/exception.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/float_type.hpp>
#include <sge/parse/json/int_type.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/null.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/start.hpp>
#include <sge/parse/json/value.hpp>
#include <sge/parse/json/output/tabbed_to_stream.hpp>
#include <fcppt/output_to_std_string.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/variant/apply.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/format.hpp>
#include <iterator>
#include <ostream>
#include <string>
#include <fcppt/config/external_end.hpp>


namespace
{

// TODO: Simplify this
struct output_visitor
{
public:
	typedef
	void
	result_type;

	typedef
	sge::charconv::utf8_string::size_type
	tab_count;

	output_visitor(
		std::ostream &_stream,
		tab_count const _tabs
	)
	:
		stream_(
			_stream
		),
		tabs_(
			_tabs
		)
	{
	}

	result_type
	operator()(
		sge::parse::json::object const &_object
	) const
	{
		this->stream_.get()
			<<
			(
				boost::format(
					"%s{\n"
				)
				% this->make_tabs()
			).str();

		for(
			sge::parse::json::member_map::const_iterator it(
				_object.members.begin()
			);
			it != _object.members.end();
			++it
		)
		{
			this->stream_.get()
				<<
				(
					boost::format(
						"%s\"%s\" :\n"
					)
					% this->make_more_tabs()
					% it->first
				).str();

			fcppt::variant::apply(
				output_visitor(
					this->stream_.get(),
					tabs_+2
				),
				it->second.get().get()
			);

			if(
				std::next(it)
				!=
				_object.members.end()
			)
				this->stream_.get()
					<< ',';

			this->stream_.get()
				<< '\n';
		}

		this->stream_.get()
			<< this->make_tabs()
			<< '}';
	}

	result_type
	operator()(
		sge::parse::json::array const &_array
	) const
	{
		this->stream_.get()
			<<
			(
				boost::format(
					"%s[\n"
				)
				%
				this->make_tabs()
			).str();

		for(
			sge::parse::json::element_vector::const_iterator it(
				_array.elements.begin()
			);
			it != _array.elements.end();
			++it
		)
		{
			fcppt::variant::apply(
				output_visitor(
					this->stream_.get(),
					tabs_+1
				),
				it->get().get()
			);

			if(
				std::next(it)
				!=
				_array.elements.end()
			)
				this->stream_.get()
					<< ',';

			this->stream_.get()
				<< '\n';
		}

		this->stream_.get()
			<< this->make_tabs()
			<< ']';
	}

	result_type
	operator()(
		std::string const &_string
	) const
	{
		if(
			_string.find(
				'\"'
			)
			!= std::string::npos
		)
			throw sge::parse::exception(
				FCPPT_TEXT("quoted strings are unsupported")
			);

		this->stream_.get()
			<< this->make_tabs()
			<< '"'
			<< _string
			<< '"';
	}

	result_type
	operator()(
		bool const _bool
	) const
	{
		this->stream_.get()
			<< this->make_tabs()
			<<
			(
				_bool
				?
					sge::charconv::utf8_string{
						"true"
					}
				:
					sge::charconv::utf8_string{
						"false"
					}
			);
	}

	result_type
	operator()(
		sge::parse::json::null const &
	) const
	{
		this->stream_.get()
			<< this->make_tabs()
			<< "null";
	}

	result_type
	operator()(
		sge::parse::json::int_type const _int
	) const
	{
		this->stream_.get()
			<< this->make_tabs()
			<<
			fcppt::output_to_std_string(
				_int
			);
	}

	result_type
	operator()(
		sge::parse::json::float_type const _float
	) const
	{
		this->stream_.get()
			<< this->make_tabs()
			<<
			(
				boost::format(
					"%1$.2f"
				)
				%
				_float
			).str();
	}
private:
	fcppt::reference<
		std::ostream
	> stream_;

	tab_count tabs_;

	sge::charconv::utf8_string
	make_tabs() const
	{
		return
			sge::charconv::utf8_string(
				tabs_,
				'\t'
			);
	}

	sge::charconv::utf8_string
	make_more_tabs() const
	{
		return
			sge::charconv::utf8_string(
				tabs_ + 1u,
				'\t'
			);
	}
};

}

void
sge::parse::json::output::tabbed_to_stream(
	std::ostream &_stream,
	sge::parse::json::start const &_start
)
{
	return
		fcppt::variant::apply(
			[
				&_stream
			](
				auto const &_value
			)
			{
				output_visitor{
					_stream,
					0u
				}(
					_value
				);
			},
			_start.variant
		);
}
