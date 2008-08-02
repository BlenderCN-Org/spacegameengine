/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "context_base.hpp"
#include "../library.hpp"

sge::plugin::context_base::context_base(
	path const &path_)
: path_(path_)
{
	typedef void (*version_function)(sge::plugin_info*);

	library lib(get_path());
	version_function vf = lib.load_function<version_function>("plugin_version_info");
	plugin_info info;
	vf(&info);
	name_ = info.name;
	description_ = info.description;
	version_ = info.plugin_version;
	type_ = info.type;
}

const sge::string&
sge::plugin::context_base::name() const
{
	return name_;
}

const sge::string&
sge::plugin::context_base::description() const
{
	return description_;
}

unsigned sge::plugin::context_base::version() const
{
	return version_;
}

sge::plugin_type::type
sge::plugin::context_base::type() const
{
	return type_;
}

const sge::path&
sge::plugin::context_base::get_path() const
{
	return path_;
}
