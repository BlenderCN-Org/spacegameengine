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


#ifndef SGE_VIEWPORT_MANAGER_HPP_INCLUDED
#define SGE_VIEWPORT_MANAGER_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/target/viewport_fwd.hpp>
#include <sge/viewport/manage_callback.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <sge/viewport/resize_callback.hpp>
#include <sge/viewport/symbol.hpp>
#include <sge/viewport/detail/manager_impl_fwd.hpp>
#include <sge/window/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr_decl.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>


namespace sge
{
namespace viewport
{

class SGE_CLASS_SYMBOL manager
{
	FCPPT_NONCOPYABLE(
		manager
	);
public:
	SGE_VIEWPORT_SYMBOL
	manager(
		sge::renderer::device::core &,
		sge::window::object &,
		sge::viewport::resize_callback const &
	);

	SGE_VIEWPORT_SYMBOL
	~manager();

	SGE_VIEWPORT_SYMBOL
	fcppt::signal::auto_connection
	manage_callback(
		sge::viewport::manage_callback const &
	);

	SGE_VIEWPORT_SYMBOL
	void
	resize_callback(
		sge::viewport::resize_callback const &
	);

	SGE_VIEWPORT_SYMBOL
	sge::renderer::target::viewport const
	viewport() const;
private:
	typedef fcppt::scoped_ptr<
		sge::viewport::detail::manager_impl
	> impl_ptr;

	impl_ptr const impl_;
};

}
}

#endif
