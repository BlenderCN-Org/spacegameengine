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


#ifndef SGE_OPENGL_STATE_CORE_SAMPLER_FILTER_ANISOTROPY_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_STATE_CORE_SAMPLER_FILTER_ANISOTROPY_CONTEXT_HPP_INCLUDED

#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/info/context_fwd.hpp>
#include <sge/opengl/state/core/sampler/filter/anisotropy_context_fwd.hpp>
#include <sge/opengl/state/core/sampler/filter/optional_anisotropy_config.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace state
{
namespace core
{
namespace sampler
{
namespace filter
{

class anisotropy_context
:
	public sge::opengl::context::base
{
	FCPPT_NONCOPYABLE(
		anisotropy_context
	);
public:
	typedef
	sge::opengl::info::context const &
	parameter;

	explicit
	anisotropy_context(
		sge::opengl::info::context const &
	);

	~anisotropy_context()
	override;

	sge::opengl::state::core::sampler::filter::optional_anisotropy_config const &
	config() const;

	static
	sge::opengl::context::id const
	static_id;
private:
	sge::opengl::state::core::sampler::filter::optional_anisotropy_config const config_;
};

}
}
}
}
}
}

#endif
