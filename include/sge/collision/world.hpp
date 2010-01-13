/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_COLLISION_WORLD_HPP_INCLUDED
#define SGE_COLLISION_WORLD_HPP_INCLUDED

#include <sge/collision/world_fwd.hpp>
#include <sge/collision/body_ptr.hpp>
#include <sge/collision/group_ptr.hpp>
#include <sge/collision/unit.hpp>
#include <sge/collision/solidity.hpp>
#include <sge/collision/dim.hpp>
#include <sge/collision/point.hpp>
#include <sge/collision/satellite_ptr.hpp>
#include <sge/collision/time_unit.hpp>
#include <sge/collision/shapes/sphere_fwd.hpp>
#include <sge/collision/shapes/box_fwd.hpp>
#include <sge/collision/shapes/container.hpp>
#include <sge/collision/shape_callback.hpp>
#include <sge/collision/test_callback.hpp>
#include <sge/collision/test_callback_combiner.hpp>
#include <sge/symbol.hpp>
#include <sge/class_symbol.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace collision
{
class SGE_CLASS_SYMBOL world
{
	FCPPT_NONCOPYABLE(world)
protected:
	SGE_SYMBOL world();
public:
	virtual fcppt::signal::auto_connection
	register_test_callback(
		test_callback const &
	) = 0;

	virtual void
	test_callback_combiner(
		collision::test_callback_combiner const &
	) = 0;

	virtual fcppt::signal::auto_connection
	register_begin_callback(
		shape_callback const &) = 0;
		
	virtual signal::auto_connection
	register_end_callback(
		shape_callback const &) = 0;
	
	virtual signal::auto_connection
	register_solid_callback(
		shape_callback const &) = 0;
		
	// NOTE: the body gets the (shared) ownership to the shapes!
	virtual body_ptr const 
	create_body(
		shapes::container const &,
		point const &,
		point const &) = 0;
	
	virtual shapes::sphere_ptr const
	create_sphere(
		satellite_ptr,
		unit radius,
		solidity::type,
		point const & = point::null()) = 0;

	virtual shapes::box_ptr const
	create_box(
		satellite_ptr,
		dim const &,
		solidity::type,
		point const & = point::null()) = 0;
	
	virtual group_ptr const 
	create_group() = 0;

	virtual void
	update(
		time_unit delta
	) = 0;

	virtual void
	collides_with(
		group_ptr,
		group_ptr
	) = 0;

	SGE_SYMBOL virtual ~world();
};
}
}

#endif
