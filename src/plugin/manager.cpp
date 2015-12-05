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


#include <sge/plugin/capabilities.hpp>
#include <sge/plugin/category_array.hpp>
#include <sge/plugin/context_base_ref.hpp>
#include <sge/plugin/context_base_unique_ptr.hpp>
#include <sge/plugin/info.hpp>
#include <sge/plugin/manager.hpp>
#include <sge/plugin/optional_cache_ref_fwd.hpp>
#include <sge/src/plugin/context_base.hpp>
#include <sge/src/plugin/load_plugins.hpp>
#include <sge/src/plugin/logger.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/enum_array_init.hpp>
#include <fcppt/algorithm/map_optional.hpp>
#include <fcppt/container/enum_array_impl.hpp>
#include <fcppt/container/bitfield/operators.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


sge::plugin::manager::manager(
	boost::filesystem::path const &_path,
	sge::plugin::optional_cache_ref const &_cache
)
:
	plugins_(
		[
			&_path,
			&_cache
		]{
			FCPPT_LOG_DEBUG(
				sge::plugin::logger(),
				fcppt::log::_
					<< FCPPT_TEXT("Scanning for plugins in ")
					<< fcppt::filesystem::path_to_string(
						_path
					)
			);

			return
				sge::plugin::load_plugins(
					_path,
					_cache
				);
		}()
	),
	categories_(
		fcppt::algorithm::enum_array_init<
			sge::plugin::manager::plugin_map
		>(
			[
				this
			](
				sge::plugin::capabilities const _capability
			)
			{
				return
					fcppt::algorithm::map_optional<
						sge::plugin::category_array
					>(
						plugins_,
						[
							_capability
						](
							sge::plugin::context_base_unique_ptr const &_context
						)
						{
							typedef
							fcppt::optional<
								sge::plugin::context_base_ref
							>
							optional_result;

							return
								_context->info().capabilities()
								&
								_capability
								?
									optional_result(
										fcppt::make_ref(
											*_context
										)
									)
								:
									optional_result()
								;
						}
					);
			}
		)
	)
{
}

sge::plugin::manager::~manager()
{
}
