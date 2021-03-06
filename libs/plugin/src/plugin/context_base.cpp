/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/plugin/cache.hpp>
#include <sge/plugin/flags.hpp>
#include <sge/plugin/optional_cache_ref.hpp>
#include <sge/plugin/impl/context_base.hpp>
#include <sge/plugin/impl/load_info.hpp>
#include <sge/plugin/impl/library/object.hpp>
#include <sge/plugin/library/object_shared_ptr.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/weak_ptr_impl.hpp>
#include <fcppt/container/bitfield/operators.hpp>
#include <fcppt/io/ostream.hpp>
#include <fcppt/optional/from.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


sge::plugin::context_base::context_base(
	sge::plugin::optional_cache_ref const &_cache,
	boost::filesystem::path const &_path
)
:
	cache_(
		_cache
	),
	path_(
		_path
	),
	info_(
		sge::plugin::impl::load_info(
			_path
		)
	),
	library_ptr_()
{
}

sge::plugin::context_base::~context_base()
{
}

boost::filesystem::path const &
sge::plugin::context_base::path() const
{
	return
		path_;
}

sge::plugin::info const &
sge::plugin::context_base::info() const
{
	return
		info_;
}

sge::plugin::library::object_shared_ptr
sge::plugin::context_base::load()
{
	return
		fcppt::optional::from(
			library_ptr_.lock(),
			[
				this
			]{
				sge::plugin::library::object_shared_ptr const ret(
					fcppt::make_shared_ptr<
						sge::plugin::library::object
					>(
						path_
					)
				);

				library_ptr_ =
					ret;

				if(
					this->info().flags()
					&
					sge::plugin::flags::delayed_unload
				)
					fcppt::optional::maybe_void(
						cache_,
						[
							ret
						](
							fcppt::reference<
								sge::plugin::cache
							> const _cache
						)
						{
							_cache.get().add(
								ret
							);
						}
					);

				return
					ret;
			}
		);
}
