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


#ifndef SGE_SRC_CEGUI_TEXTURE_TARGET_HPP_INCLUDED
#define SGE_SRC_CEGUI_TEXTURE_TARGET_HPP_INCLUDED

#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/caps/render_target_inverted.hpp>
#include <sge/renderer/target/offscreen_scoped_ptr.hpp>
#include <sge/src/cegui/optional_render_context_ref.hpp>
#include <sge/src/cegui/texture_fwd.hpp>
#include <sge/src/cegui/texture_parameters.hpp>
#include <sge/src/cegui/texture_target_fwd.hpp>
#include <sge/src/cegui/fwds/sizef_fwd.hpp>
#include <sge/src/cegui/fwds/vector2f_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Rect.h>
#include <CEGUI/TextureTarget.h>
#include <fcppt/config/external_end.hpp>


namespace CEGUI
{
class GeometryBuffer;
class RenderQueue;
class Texture;
}

namespace sge
{
namespace cegui
{

class texture_target
:
	public CEGUI::TextureTarget
{
	FCPPT_NONCOPYABLE(
		texture_target
	);
public:
	texture_target(
		sge::cegui::texture_parameters const &,
		sge::renderer::matrix4 const &projection,
		sge::cegui::optional_render_context_ref const &
	);

	~texture_target();
private:
	void
	draw(
		CEGUI::GeometryBuffer const &
	);

	void
	draw(
		CEGUI::RenderQueue const &
	);

	void
	setArea(
		CEGUI::Rectf const &
	);

	CEGUI::Rectf const &
	getArea() const;

	bool
	isImageryCache() const;

	void
	activate();

	void
	deactivate();

	void
	unprojectPoint(
		CEGUI::GeometryBuffer const & buff,
		CEGUI::Vector2f const &p_in,
		CEGUI::Vector2f & p_out
	) const;

	void
	clear();

	CEGUI::Texture &
	getTexture() const;

	void
	declareRenderSize(
		CEGUI::Sizef const &
	);

	bool
	isRenderingInverted() const;
private:
	sge::cegui::texture_parameters const texture_parameters_;

	typedef fcppt::scoped_ptr<
		sge::cegui::texture
	> texture_scoped_ptr;

	sge::renderer::target::offscreen_scoped_ptr const target_;

	sge::cegui::optional_render_context_ref const &render_context_;

	texture_scoped_ptr texture_;

	CEGUI::Rectf area_;

	sge::renderer::matrix4 const default_projection_;

	sge::renderer::caps::render_target_inverted const is_inverted_;
};

}
}

#endif
