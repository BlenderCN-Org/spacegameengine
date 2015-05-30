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


#ifndef SGE_SRC_SYSTEMS_MODULES_AUDIO_LOADER_HPP_INCLUDED
#define SGE_SRC_SYSTEMS_MODULES_AUDIO_LOADER_HPP_INCLUDED

#include <sge/audio/multi_loader_fwd.hpp>
#include <sge/audio/loader_plugin/collection_fwd.hpp>
#include <sge/log/option_container.hpp>
#include <sge/src/systems/modules/audio/loader_fwd.hpp>
#include <sge/systems/audio_loader_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sge
{
namespace systems
{
namespace modules
{
namespace audio
{

class loader
{
	FCPPT_NONCOPYABLE(
		loader
	);
public:
	loader(
		sge::audio::loader_plugin::collection const &,
		sge::log::option_container const &,
		sge::systems::audio_loader const &
	);

	~loader();

	sge::audio::loader &
	get() const;
private:
	typedef
	fcppt::unique_ptr<
		sge::audio::multi_loader
	>
	audio_multi_loader_ptr;

	audio_multi_loader_ptr const audio_multi_loader_;
};

}
}
}
}

#endif
