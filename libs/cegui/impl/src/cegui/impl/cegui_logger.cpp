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


#include <sge/cegui/to_fcppt_string.hpp>
#include <sge/cegui/impl/cegui_logger.hpp>
#include <sge/log/default_parameters.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/name.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/verbose.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/optional/from.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Logger.h>
#include <fcppt/config/external_end.hpp>


sge::cegui::impl::cegui_logger::cegui_logger(
	fcppt::log::object &_log
)
:
	CEGUI::Logger(),
	log_{
		_log,
		sge::log::default_parameters(
			fcppt::log::name{
				FCPPT_TEXT("CEGUI")
			}
		)
	}
{
}

sge::cegui::impl::cegui_logger::~cegui_logger()
{
}

void
sge::cegui::impl::cegui_logger::logEvent(
	CEGUI::String const &_message,
	CEGUI::LoggingLevel const _level
)
{
	fcppt::string const converted(
		fcppt::optional::from(
			sge::cegui::to_fcppt_string(
				_message
			),
			[]{
				return
					fcppt::string{
						FCPPT_TEXT("Failed to convert CEGUI string!")
					};
			}
		)
	);

	switch(
		_level
	)
	{
		case CEGUI::Errors:
			FCPPT_LOG_ERROR(
				log_,
				fcppt::log::out
					<< converted
			)
			break;
		case CEGUI::Warnings:
			FCPPT_LOG_WARNING(
				log_,
				fcppt::log::out
					<< converted
			)
			break;
		case CEGUI::Standard:
		case CEGUI::Informative:
			FCPPT_LOG_DEBUG(
				log_,
				fcppt::log::out
					<< converted
			)
			break;
		case CEGUI::Insane:
			FCPPT_LOG_VERBOSE(
				log_,
				fcppt::log::out
					<< converted
			)
			break;
	}
}

void
sge::cegui::impl::cegui_logger::setLogFilename(
	CEGUI::String const &,
	bool
)
{
	// ignored
}
