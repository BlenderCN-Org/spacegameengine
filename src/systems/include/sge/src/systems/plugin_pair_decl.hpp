/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SRC_SYSTEMS_PLUGIN_PAIR_DECL_HPP_INCLUDED
#define SGE_SRC_SYSTEMS_PLUGIN_PAIR_DECL_HPP_INCLUDED

#include <sge/plugin/object_unique_ptr.hpp>
#include <sge/src/systems/plugin_pair_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace systems
{

template<
	typename System
>
class plugin_pair
{
	FCPPT_NONCOPYABLE(
		plugin_pair
	);
public:
	typedef
	sge::plugin::object_unique_ptr<
		System
	>
	plugin_unique_ptr;

	typedef std::unique_ptr<
		System
	> system_unique_ptr;

	plugin_pair();

	plugin_pair(
		plugin_unique_ptr &&,
		system_unique_ptr &&
	);

	plugin_pair(
		plugin_pair &&
	);

	plugin_pair &
	operator=(
		plugin_pair &&
	);

	~plugin_pair();

	System &
	system() const;

	explicit
	operator
	bool() const;
private:
	plugin_unique_ptr plugin_;

	system_unique_ptr system_;
};

}
}

#endif
