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


#ifndef SGE_RENDERER_TARGET_SCOPED_SCISSOR_AREA_HPP_INCLUDED
#define SGE_RENDERER_TARGET_SCOPED_SCISSOR_AREA_HPP_INCLUDED

#include <sge/renderer/symbol.hpp>
#include <sge/renderer/target/base_fwd.hpp>
#include <sge/renderer/target/scissor_area.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{
namespace target
{

/**
 * \brief A scoped scissor block
 *
 * This class sets a new scissor area for a target in the constructor, saving
 * the old scissor area. In the destructor the old scissor area is restored.
*/
class scoped_scissor_area
{
	FCPPT_NONCOPYABLE(
		scoped_scissor_area
	);
public:
	/**
	 * \brief Sets a new scissor area
	 *
	 * Sets the scissor area of \a target to \a area. It also saves the
	 * old scissor area of \a target which will be restored in the
	 * destructor.
	 *
	 * \param target The target to set the scissor area for
	 *
	 * \param area The new scissor area
	*/
	SGE_RENDERER_SYMBOL
	scoped_scissor_area(
		sge::renderer::target::base &target,
		sge::renderer::target::scissor_area const &area
	);

	/**
	 * \brief Resets to the old scissor area
	*/
	SGE_RENDERER_SYMBOL
	~scoped_scissor_area();
private:
	sge::renderer::target::base &target_;

	sge::renderer::target::scissor_area old_area_;
};

}
}
}

#endif
