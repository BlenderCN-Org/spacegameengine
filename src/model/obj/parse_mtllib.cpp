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


#include <sge/charconv/utf8_string_to_fcppt.hpp>
#include <sge/image/color/init.hpp>
#include <sge/image/color/rgb32f.hpp>
#include <sge/log/global.hpp>
#include <sge/model/obj/exception.hpp>
#include <sge/model/obj/identifier.hpp>
#include <sge/model/obj/parse_mtllib.hpp>
#include <sge/renderer/vector3.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/optional.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/fstream.hpp>
#include <sstream>
#include <string>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace
{
class parser
{
FCPPT_NONASSIGNABLE(
	parser);
public:
	parser(
		boost::filesystem::path const &_filename,
		sge::charconv::system &_charconv_system)
	:
		charconv_system_(
			_charconv_system),
		parent_path_(
			_filename.parent_path()),
		result_(),
		current_line_(
			0u),
		current_material_(
			fcppt::string()),
		shininess_(),
		ambient_(),
		diffuse_(),
		specular_(),
		emissive_(),
		diffuse_texture_(),
		specular_texture_()
	{
		boost::filesystem::ifstream stream(
			_filename);

		if(!stream.is_open())
			throw
				sge::model::obj::exception(
					FCPPT_TEXT("Couldn't open file \"")+
					fcppt::filesystem::path_to_string(
						_filename)+
					FCPPT_TEXT("\""));

		std::string line;

		while(
			std::getline(
				stream,
				line))
		{
			++current_line_;

			if(line.empty() || line[0] == '#')
				continue;

			std::string::size_type const first_space_position =
				line.find(' ');

			this->throw_error_if(
				first_space_position == std::string::npos,
				FCPPT_TEXT("No prefix found"));

			std::string const prefix =
				line.substr(
					0,
					first_space_position);

			std::string const rest_of_line(
				line.substr(
					first_space_position+1u));

			this->parse_line(
				prefix,
				rest_of_line);
		}

		this->push_material();
	}

	sge::model::obj::material_map const &
	result() const
	{
		return
			result_;
	}

	void
	throw_error_if(
		bool const _condition,
		fcppt::string const &_error_message)
	{
		if(_condition)
			throw
				sge::model::obj::exception(
					FCPPT_TEXT("Error on line ")+
					fcppt::insert_to_fcppt_string(
						current_line_)+
					FCPPT_TEXT(": ")+
					_error_message);
	}

	void
	parse_line(
		std::string const &_prefix,
		std::string const &_rest_of_line)
	{
		if(_prefix == "Ns")
		{
			std::istringstream ss(
				_rest_of_line);

			sge::renderer::scalar new_shininess;

			this->throw_error_if(
				!(ss >> new_shininess),
				FCPPT_TEXT("Invalid shininess."));

			shininess_ =
				new_shininess;
		}
		else if(_prefix == "Ka")
		{
			std::istringstream ss(
				_rest_of_line);

			sge::renderer::vector3 new_ambient;

			this->throw_error_if(
				!(ss >> new_ambient[0] >> new_ambient[1] >> new_ambient[2]),
				FCPPT_TEXT("Invalid ambient"));

			ambient_ =
				new_ambient;
		}
		else if(_prefix == "Ke")
		{
			std::istringstream ss(
				_rest_of_line);

			sge::renderer::scalar new_emissive;

			this->throw_error_if(
				!(ss >> new_emissive),
				FCPPT_TEXT("Invalid emissive"));

			emissive_ =
				sge::renderer::vector3(
					new_emissive,
					new_emissive,
					new_emissive);
		}
		else if(_prefix == "Kd")
		{
			std::istringstream ss(
				_rest_of_line);

			sge::renderer::vector3 new_diffuse;

			this->throw_error_if(
				!(ss >> new_diffuse[0] >> new_diffuse[1] >> new_diffuse[2]),
				FCPPT_TEXT("Invalid diffuse"));

			diffuse_ =
				new_diffuse;
		}
		else if(_prefix == "Ks")
		{
			std::istringstream ss(
				_rest_of_line);

			sge::renderer::vector3 new_specular;

			this->throw_error_if(
				!(ss >> new_specular[0] >> new_specular[1] >> new_specular[2]),
				FCPPT_TEXT("Invalid specular"));

			specular_ =
				new_specular;
		}
		else if(_prefix == "Ni")
		{
			// Not usable
		}
		else if(_prefix == "d")
		{
			std::istringstream ss(
				_rest_of_line);

			sge::renderer::scalar dissolve;

			this->throw_error_if(
				!(ss >> dissolve),
				FCPPT_TEXT("Invalid dissolve"));

			FCPPT_ASSERT_PRE(
				diffuse_);

			FCPPT_LOG_WARNING(
				sge::log::global(),
				fcppt::log::_ << FCPPT_TEXT("obj (mtl): dissolve currently not supported"));
			/*
			(*diffuse_)[3] =
				dissolve;
			if(std::abs(dissolve - 1.0f) > 0.0001f)
				throw
					sge::model::obj::exception(
						FCPPT_TEXT("Error on line ")+
						fcppt::insert_to_fcppt_string(
							current_line_)+
						FCPPT_TEXT(": Invalid dissolve value (!= 1, not supported)."));
			*/
		}
		else if(_prefix == "illum")
		{
			std::istringstream ss(
				_rest_of_line);

			unsigned light_model;
			this->throw_error_if(
				!(ss >> light_model),
				FCPPT_TEXT("Invalid light model"));

			switch(light_model)
			{
			case 0u:
				ambient_ =
					sge::renderer::vector3::null();
				break;
			case 1u:
				specular_ =
					sge::renderer::vector3::null();
				break;
			case 2u:
				break;
			default:
				FCPPT_LOG_WARNING(
					sge::log::global(),
					fcppt::log::_ << FCPPT_TEXT("obj (mtl): invalid light model: ") << light_model);
				break;
			}
		}
		else if(_prefix == "map_Kd")
		{
			diffuse_texture_ =
				parent_path_ /
				boost::filesystem::path(
					_rest_of_line);
		}
		else if(_prefix == "map_Ks")
		{
			specular_texture_ =
				parent_path_ /
				boost::filesystem::path(
					_rest_of_line);
		}
		else if (_prefix == "newmtl")
		{
			// First material we see? Do nothing.
			if(!current_material_.get().empty())
			{
				if(!ambient_ || !specular_ || !emissive_ || !diffuse_ || !shininess_)
					throw
						sge::model::obj::exception(
							FCPPT_TEXT("Error on line ")+
							fcppt::insert_to_fcppt_string(
								current_line_)+
							FCPPT_TEXT(": Material without ambient/specular/emissive/diffuse/shininess."));

				this->push_material();
			}

			current_material_ =
				sge::model::obj::identifier(
					sge::charconv::utf8_string_to_fcppt(
						charconv_system_,
						sge::charconv::utf8_string(
							_rest_of_line.begin(),
							_rest_of_line.end())));
		}
		else
		{
			FCPPT_LOG_WARNING(
				sge::log::global(),
				fcppt::log::_ << FCPPT_TEXT("obj (mtl): invalid prefix"));
		}
	}

	void
	push_material()
	{
		result_.insert(
			std::make_pair(
				current_material_,
				sge::model::obj::material::object(
					current_material_,
					sge::model::obj::material::diffuse_color(
						sge::image::color::any::object(
							sge::image::color::rgb32f(
								(sge::image::color::init::red() %= (*diffuse_)[0])
								(sge::image::color::init::green() %= (*diffuse_)[1])
								(sge::image::color::init::blue() %= (*diffuse_)[2])))),
					sge::model::obj::material::ambient_color(
						sge::image::color::any::object(
							sge::image::color::rgb32f(
								(sge::image::color::init::red() %= (*ambient_)[0])
								(sge::image::color::init::green() %= (*ambient_)[1])
								(sge::image::color::init::blue() %= (*ambient_)[2])))),
					sge::model::obj::material::specular_color(
						sge::image::color::any::object(
							sge::image::color::rgb32f(
								(sge::image::color::init::red() %= (*specular_)[0])
								(sge::image::color::init::green() %= (*specular_)[1])
								(sge::image::color::init::blue() %= (*specular_)[2])))),
					sge::model::obj::material::emissive_color(
						sge::image::color::any::object(
							sge::image::color::rgb32f(
								(sge::image::color::init::red() %= (*emissive_)[0])
								(sge::image::color::init::green() %= (*emissive_)[1])
								(sge::image::color::init::blue() %= (*emissive_)[2])))),
					sge::model::obj::material::shininess(
						*shininess_),
					sge::model::obj::material::diffuse_texture_path(
						diffuse_texture_
						?
							*diffuse_texture_
						:
						boost::filesystem::path()),
					sge::model::obj::material::specular_texture_path(
						specular_texture_
						?
							*specular_texture_
						:
							boost::filesystem::path()))));
	}
private:
	sge::charconv::system &charconv_system_;
	boost::filesystem::path const parent_path_;
	sge::model::obj::material_map result_;
	unsigned current_line_;
	sge::model::obj::identifier current_material_;
	fcppt::optional<sge::renderer::scalar> shininess_;
	fcppt::optional<sge::renderer::vector3> ambient_, diffuse_, specular_, emissive_;
	fcppt::optional<boost::filesystem::path> diffuse_texture_;
	fcppt::optional<boost::filesystem::path> specular_texture_;
};
}

sge::model::obj::material_map const
sge::model::obj::parse_mtllib(
	boost::filesystem::path const &_filename,
	sge::charconv::system &_charconv_system)
{
	parser p(
		_filename,
		_charconv_system);

	return
		p.result();
}
