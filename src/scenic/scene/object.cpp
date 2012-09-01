
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


#include <sge/camera/base.hpp>
#include <sge/camera/coordinate_system/object.hpp>
#include <sge/camera/first_person/object.hpp>
#include <sge/camera/matrix_conversion/world.hpp>
#include <sge/image/colors.hpp>
#include <sge/model/obj/parse_mtllib.hpp>
#include <sge/model/obj/prototype.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/vertex_declaration.hpp>
#include <sge/scenic/scene/manager.hpp>
#include <sge/renderer/context/object.hpp>
#include <sge/scenic/render_context/base.hpp>
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/color.hpp>
#include <sge/renderer/state/cull_mode.hpp>
#include <sge/renderer/state/depth_func.hpp>
#include <sge/renderer/state/float.hpp>
#include <sge/renderer/state/fog_mode.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/scoped.hpp>
#include <sge/renderer/target/base.hpp>
#include <sge/renderer/target/viewport_size.hpp>
#include <sge/renderer/texture/scoped.hpp>
#include <sge/renderer/texture/filter/mipmap.hpp>
#include <sge/renderer/texture/filter/object.hpp>
#include <sge/renderer/texture/filter/scoped.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/scenic/exception.hpp>
#include <sge/scenic/render_queue/object.hpp>
#include <sge/scenic/scene/object.hpp>
#include <sge/scenic/scene/material_from_obj_material.hpp>
#include <sge/scenic/scene/prototype.hpp>
#include <sge/scenic/scene/mesh/object.hpp>
#include <sge/scenic/vf/format.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/move.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/string.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/math/dim/object_impl.hpp>
#include <fcppt/math/matrix/arithmetic.hpp>
#include <fcppt/math/matrix/scaling.hpp>
#include <fcppt/math/matrix/translation.hpp>
#include <fcppt/math/vector/output.hpp>


sge::scenic::scene::object::object(
	sge::scenic::scene::manager &_scene_manager,
	sge::viewport::manager &_viewport_manager,
	sge::charconv::system &_charconv_system,
	sge::camera::first_person::object &_camera,
	sge::scenic::scene::prototype_unique_ptr _prototype,
	model_base_path const &_model_base_path,
	material_base_path const &_material_base_path,
	texture_base_path const &_texture_base_path)
:
	scene_manager_(
		_scene_manager),
	camera_(
		_camera),
	charconv_system_(
		_charconv_system),
	model_base_path_(
		_model_base_path),
	material_base_path_(
		_material_base_path),
	texture_base_path_(
		_texture_base_path),
	prototype_(
		fcppt::move(
			_prototype)),
	camera_viewport_connection_(
		camera_,
		_scene_manager.renderer(),
		_viewport_manager,
		prototype_->camera().near(),
		prototype_->camera().far(),
		prototype_->camera().fov()),
	mesh_name_to_instance_(),
	materials_(),
	state_changes_()
{
	this->load_entities();

	camera_.update_coordinate_system(
		prototype_->camera().coordinate_system());
}

void
sge::scenic::scene::object::render(
	sge::scenic::render_context::base &_context)
{
	if(
		!sge::renderer::target::viewport_size(
			_context.target()).content())
		return;

	state_changes_ =
		0u;

	_context.transform(
		sge::renderer::matrix_mode::projection,
		camera_.projection_matrix().get());

	/*
	sge::renderer::state::scoped scoped_global_state(
		_context,
		sge::renderer::state::list
			(sge::renderer::state::bool_::enable_lighting = true)
			(sge::renderer::state::depth_func::less)
			(sge::renderer::state::color::ambient_light_color = prototype_->ambient_color().get())
			(prototype_->fog() ? sge::renderer::state::fog_mode::linear : sge::renderer::state::fog_mode::off)
			(sge::renderer::state::cull_mode::counter_clockwise));

	sge::renderer::texture::filter::scoped scoped_filter(
		_context,
		sge::renderer::texture::stage(
			0u),
		sge::renderer::texture::filter::mipmap());

	fcppt::scoped_ptr<sge::renderer::state::scoped> scoped_fog_state;

	if(prototype_->fog())
	{
		scoped_fog_state.take(
			fcppt::make_unique_ptr<sge::renderer::state::scoped>(
				fcppt::ref(
					_context),
				fcppt::cref(
					sge::renderer::state::list
						(sge::renderer::state::float_::fog_start = prototype_->fog()->start().get())
						(sge::renderer::state::float_::fog_end = prototype_->fog()->end().get())
						(sge::renderer::state::color::fog_color = prototype_->fog()->color().get()))));
	}

	this->activate_lights(
		_context);
	*/

	sge::scenic::render_queue::object current_render_queue;
	for(
		sge::scenic::scene::entity_sequence::const_iterator it =
			prototype_->entities().begin();
		it != prototype_->entities().end();
		++it)
		this->render_entity(
			*it,
			current_render_queue);

	std::cout
		<< "\r"
		<< prototype_->entities().size()
		<< " entities, "
		<< current_render_queue.render(_context).get()
		<< " state changes";

	std::cout.flush();
}

sge::scenic::scene::object::~object()
{
	std::cout << "\n";
}

void
sge::scenic::scene::object::load_entities()
{
	for(
		sge::scenic::scene::entity_sequence::const_iterator current_entity =
			prototype_->entities().begin();
		current_entity != prototype_->entities().end();
		++current_entity)
	{
		sge::scenic::scene::identifier const mesh_name(
			current_entity->mesh().get());

		mesh_map::iterator mesh_name_and_instance(
			mesh_name_to_instance_.find(
				mesh_name));

		if(mesh_name_and_instance != mesh_name_to_instance_.end())
			continue;

		sge::model::obj::prototype const new_prototype(
			model_base_path_.get() / (mesh_name.get()+FCPPT_TEXT(".obj")),
			charconv_system_);

		for(
			sge::model::obj::material_file_sequence::const_iterator current_material_file =
				new_prototype.material_files().begin();
			current_material_file != new_prototype.material_files().end();
			++current_material_file)
		{
			sge::model::obj::material_map const new_materials(
				sge::model::obj::parse_mtllib(
					material_base_path_.get() / (*current_material_file),
					charconv_system_));

			for(
				sge::model::obj::material_map::const_iterator current_obj_material =
					new_materials.begin();
				current_obj_material != new_materials.end();
				++current_obj_material)
			{
				materials_.insert(
					std::make_pair(
						sge::scenic::scene::identifier(
							current_obj_material->first.get()),
						sge::scenic::scene::material_from_obj_material(
							current_obj_material->second)));
			}
		}

		fcppt::container::ptr::insert_unique_ptr_map(
			mesh_name_to_instance_,
			mesh_name,
			fcppt::make_unique_ptr<sge::scenic::scene::mesh::object>(
				fcppt::ref(
					scene_manager_.renderer()),
				fcppt::ref(
					scene_manager_.vertex_declaration()),
				fcppt::cref(
					new_prototype)));
	}
}

	/*
void
sge::scenic::scene::object::activate_lights(
	sge::renderer::context::object &_context)
{
	sge::renderer::scoped_transform scoped_world(
		_context,
		sge::renderer::matrix_mode::world,
		sge::camera::matrix_conversion::world(
			camera_.coordinate_system()));

	if(prototype_->lights().size() > 8u)
		throw
			sge::scenic::exception(
				FCPPT_TEXT("Found more than 8 lights in the scene.\nThat's currently not supported."));

	sge::renderer::light::index current_light_index(
		0u);

	for(
		sge::scenic::render_context::light_sequence::const_iterator current_light =
			prototype_->lights().begin();
		current_light != prototype_->lights().end();
		current_light++)
	{
		_context.enable_light(
			current_light_index,
			true);

		_context.light(
			current_light_index,
			*current_light);

		++current_light_index;
	}
}
	*/

void
sge::scenic::scene::object::render_entity(
	sge::scenic::scene::entity const &_entity,
	sge::scenic::render_queue::object &_context)
{
	sge::scenic::scene::mesh::object &mesh(
		*(mesh_name_to_instance_.find(
			_entity.mesh())->second));

	_context.current_vertex_buffer(
		mesh.vertex_buffer());

	for(
		sge::scenic::scene::mesh::material_to_index_buffer_range::const_iterator material_name_and_index_buffer_range =
			mesh.parts().begin();
		material_name_and_index_buffer_range != mesh.parts().end();
		++material_name_and_index_buffer_range)
	{
		material_map::const_iterator const material_name_and_material =
			materials_.find(
				material_name_and_index_buffer_range->first);

		FCPPT_ASSERT_PRE(
			material_name_and_material != materials_.end());

		sge::scenic::scene::material const &material(
			material_name_and_material->second);

		_context.current_material(
			material.renderer_material());

		if(material.texture().get().empty())
		{
			_context.current_texture(
				fcppt::optional<sge::renderer::texture::planar &>());
		}
		else
		{
			_context.current_texture(
				fcppt::optional<sge::renderer::texture::planar &>(
					scene_manager_.texture_manager().texture_for_path(
						texture_base_path_.get() / material.texture().get())));
		}

		_context.add_mesh(
			sge::camera::matrix_conversion::world(
				camera_.coordinate_system()) *
			fcppt::math::matrix::translation(
				_entity.position().get()) *
			_entity.rotation().get() *
			fcppt::math::matrix::scaling(
				_entity.scale().get()),
			mesh.index_buffer(),
			material_name_and_index_buffer_range->second);
	}
}
