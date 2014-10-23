/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_RUCKSACK_AXIS_POLICY2_HPP_INCLUDED
#define SGE_RUCKSACK_AXIS_POLICY2_HPP_INCLUDED

#include <sge/rucksack/axis_fwd.hpp>
#include <sge/rucksack/axis_policy.hpp>
#include <sge/rucksack/axis_policy2_fwd.hpp>
#include <sge/rucksack/detail/symbol.hpp>


namespace sge
{
namespace rucksack
{

class axis_policy2
{
public:
	SGE_RUCKSACK_DETAIL_SYMBOL
	axis_policy2(
		sge::rucksack::axis_policy const &,
		sge::rucksack::axis_policy const &
	);

	SGE_RUCKSACK_DETAIL_SYMBOL
	sge::rucksack::axis_policy const &
	x() const;

	SGE_RUCKSACK_DETAIL_SYMBOL
	sge::rucksack::axis_policy const &
	y() const;

	SGE_RUCKSACK_DETAIL_SYMBOL
	sge::rucksack::axis_policy const &
	operator[](
		sge::rucksack::axis
	) const;
private:
	sge::rucksack::axis_policy
		x_,
		y_;
};

}
}

#endif
