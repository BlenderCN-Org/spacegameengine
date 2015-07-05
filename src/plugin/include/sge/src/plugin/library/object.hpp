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


#ifndef SGE_SRC_PLUGIN_LIBRARY_OBJECT_HPP_INCLUDED
#define SGE_SRC_PLUGIN_LIBRARY_OBJECT_HPP_INCLUDED

#include <sge/plugin/detail/symbol.hpp>
#include <sge/plugin/library/object_fwd.hpp>
#include <sge/plugin/library/symbol_string.hpp>
#include <sge/src/plugin/library/loaded_symbol.hpp>
#include <fcppt/config/platform.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>

#if defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
#include <awl/backends/windows/windows.hpp>
#include <fcppt/unique_ptr_decl.hpp>
#endif


namespace sge
{
namespace plugin
{
namespace library
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	SGE_PLUGIN_DETAIL_SYMBOL
	explicit
	object(
		boost::filesystem::path const &
	);

	SGE_PLUGIN_DETAIL_SYMBOL
	~object();

	sge::plugin::library::loaded_symbol
	load(
		sge::plugin::library::symbol_string const &
	);

	boost::filesystem::path const &
	name() const;
private:
	boost::filesystem::path const name_;

#if defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
	HMODULE const handle_;

	struct destroyer;

	fcppt::unique_ptr<
		destroyer
	> const destroyer_;
#elif defined(FCPPT_CONFIG_POSIX_PLATFORM)
	void *const handle_;
#else
#error "Don't know how to implement plugin::library!"
#endif
};

}
}
}

#endif
