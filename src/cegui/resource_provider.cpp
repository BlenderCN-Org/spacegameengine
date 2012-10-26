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


#include <sge/cegui/exception.hpp>
#include <sge/cegui/from_cegui_string.hpp>
#include <sge/src/cegui/declare_local_logger.hpp>
#include <sge/src/cegui/resource_provider.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unimplemented_message.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/path.hpp>
#include <cstddef>
#include <fstream>
#include <ios>
#include <fcppt/config/external_end.hpp>


SGE_CEGUI_DECLARE_LOCAL_LOGGER(
	FCPPT_TEXT("resource_provider")
)

sge::cegui::resource_provider::resource_provider(
	sge::charconv::system &_charconv_system
)
:
	charconv_system_(
		_charconv_system
	)
{
}

// This is called for
// - Fonts
// - XML files
void
sge::cegui::resource_provider::loadRawDataContainer(
	CEGUI::String const &filename,
	CEGUI::RawDataContainer &output,
	CEGUI::String const &resource_group)
{
	fcppt::string const
		converted_filename =
			cegui::from_cegui_string(
				filename,
				charconv_system_),
		converted_resource_group =
			cegui::from_cegui_string(
				resource_group,
				charconv_system_);

	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("loadRawDataContainer(")
			<< converted_filename
			<< FCPPT_TEXT(", ")
			<< converted_resource_group
			<< FCPPT_TEXT(")"));

	boost::filesystem::path const load_path =
		!converted_resource_group.empty()
		?
			boost::filesystem::path(
				converted_resource_group)/converted_filename
		:
			boost::filesystem::path(
				converted_filename);

	boost::filesystem::ifstream file_stream(
		load_path,
		std::ios::binary);

	if(!file_stream.is_open())
		throw cegui::exception(
			FCPPT_TEXT("Coudn't open file \"")+
			fcppt::filesystem::path_to_string(
				load_path)+
			FCPPT_TEXT("\""));

	file_stream.seekg(
		0,
		std::ios_base::end);

	std::streampos const filesize =
		file_stream.tellg();

	CEGUI::uint8 *data = new CEGUI::uint8[static_cast<std::size_t>(filesize)];

	file_stream.seekg(
		0,
		std::ios_base::beg);

	file_stream.read(
		reinterpret_cast<char*>(
			data),
		static_cast<std::streamsize>(
			filesize));

	output.setData(
		data);
	output.setSize(
		static_cast<std::size_t>(
			filesize));
}

void
sge::cegui::resource_provider::unloadRawDataContainer(
	CEGUI::RawDataContainer&data)
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("unloadRawDataContainer()"));

	data.release();
}

size_t
sge::cegui::resource_provider::getResourceGroupFileNames(
	std::vector<CEGUI::String>&,
	CEGUI::String const &file_pattern,
	CEGUI::String const &resource_group)
{
	fcppt::string const
		converted_file_pattern =
			from_cegui_string(
				file_pattern,
				charconv_system_),
		converted_resource_group =
			from_cegui_string(
				resource_group,
				charconv_system_);

	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("loadRawDataContainer(")
			<< converted_file_pattern
			<< FCPPT_TEXT(", ")
			<< converted_resource_group
			<< FCPPT_TEXT(")"));
	FCPPT_ASSERT_UNIMPLEMENTED_MESSAGE(
		FCPPT_TEXT("resource_provider::getResourceGroupFilenames not implemented yet!"));
	return 0u;
}

sge::cegui::resource_provider::~resource_provider()
{
}
