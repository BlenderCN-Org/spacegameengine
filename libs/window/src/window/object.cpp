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


#include <sge/window/dim.hpp>
#include <sge/window/event_combiner.hpp>
#include <sge/window/event_function.hpp>
#include <sge/window/object.hpp>
#include <sge/window/system.hpp>
#include <sge/window/system_event_function.hpp>
#include <awl/event/base.hpp>
#include <awl/event/container.hpp>
#include <awl/window/object.hpp>
#include <awl/window/event/base.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::window::object::object(
	sge::window::system &_system,
	awl::window::object &_awl_window
)
:
	system_{
		_system
	},
	awl_object_{
		_awl_window
	},
	event_signal_{
		event_signal::combiner_function{
			&sge::window::event_combiner
		}
	},
	connection_{
		_system.event_handler(
			sge::window::system_event_function{
				[
					this
				](
					awl::event::base const &_event
				)
				{
					return
						fcppt::optional::maybe(
							fcppt::cast::dynamic<
								awl::window::event::base const
							>(
								_event
							),
							[]{
								return
									awl::event::container{};
							},
							[
								this
							](
								fcppt::reference<
									awl::window::event::base const
								> const _ref
							)
							{
								return
									this->event_signal_(
										event_signal::initial_value{
											awl::event::container{}
										},
										_ref.get()
									);
							}
						);
				}
			}
		)
	}
{
}

FCPPT_PP_POP_WARNING

sge::window::object::~object()
{
}

sge::window::dim
sge::window::object::size() const
{
	return
		fcppt::math::dim::structure_cast<
			sge::window::dim,
			fcppt::cast::size_fun
		>(
			this->awl_object().size()
		);
}

void
sge::window::object::show()
{
	this->awl_object().show();
}

awl::window::object &
sge::window::object::awl_object() const
{
	return
		awl_object_;
}

fcppt::signal::auto_connection
sge::window::object::event_handler(
	sge::window::event_function _function
)
{
	return
		event_signal_.connect(
			std::move(
				_function
			)
		);
}

sge::window::system &
sge::window::object::system() const
{
	return
		system_;
}
