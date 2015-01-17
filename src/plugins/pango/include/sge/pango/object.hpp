/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_PANGO_OBJECT_HPP_INCLUDED
#define SGE_PANGO_OBJECT_HPP_INCLUDED

#include <sge/font/metrics.hpp>
#include <sge/font/object.hpp>
#include <sge/font/parameters_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text_parameters_fwd.hpp>
#include <sge/font/text_unique_ptr.hpp>
#include <sge/image/color/optional_format_fwd.hpp>
#include <sge/pango/glib_deleter_fwd.hpp>
#include <sge/pango/pango_layout_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <pango/pango-fontmap.h>
#include <pango/pango-layout.h>
#include <pango/pango-types.h>
#include <memory>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace pango
{

class object
:
	public sge::font::object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	explicit
	object(
		sge::font::parameters const &
	);

	~object()
	override;
private:
	sge::font::text_unique_ptr
	create_text(
		sge::font::string const &,
		sge::font::text_parameters const &
	)
	override;

	sge::image::color::optional_format const
	color_format() const
	override;

	sge::font::metrics const
	metrics() const
	override;

	typedef
	std::unique_ptr<
		PangoFontMap,
		sge::pango::glib_deleter
	>
	font_map_unique_ptr;

	font_map_unique_ptr const font_map_;

	typedef
	std::unique_ptr<
		PangoContext,
		sge::pango::glib_deleter
	>
	context_unique_ptr;

	context_unique_ptr const context_;

	sge::pango::pango_layout_unique_ptr const layout_;

	sge::font::metrics const metrics_;
};

}
}

#endif
