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


#include <sge/charconv/system_fwd.hpp>
#include <sge/font/object.hpp>
#include <sge/font/parameters_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text.hpp>
#include <sge/font/text_parameters_fwd.hpp>
#include <sge/font/text_unique_ptr.hpp>
#include <sge/pango/create_layout.hpp>
#include <sge/pango/glib_deleter.hpp>
#include <sge/pango/object.hpp>
#include <sge/pango/text.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/scoped_ptr_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <pango/pango-types.h>
#include <fcppt/config/external_end.hpp>


sge::pango::object::object(
	sge::charconv::system &_charconv_system,
	PangoContext &_context,
	sge::font::parameters const &_parameters
)
:
	sge::font::object(),
	charconv_system_(
		_charconv_system
	),
	layout_(
		sge::pango::create_layout(
			_context,
			_parameters
		)
	)
{
}

sge::pango::object::~object()
{
}

sge::font::text_unique_ptr
sge::pango::object::create_text(
	sge::font::string const &_text,
	sge::font::text_parameters const &_parameters
)
{
	return
		sge::font::text_unique_ptr(
			fcppt::make_unique_ptr<
				sge::pango::text
			>(
				fcppt::ref(
					charconv_system_
				),
				fcppt::ref(
					*layout_
				),
				fcppt::cref(
					_text
				),
				fcppt::cref(
					_parameters
				)
			)
		);
}