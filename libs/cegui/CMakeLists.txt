set(
	SGE_CEGUI_FILES
	libs/cegui/impl/include/sge/cegui/impl/batch.hpp
	libs/cegui/impl/include/sge/cegui/impl/batch_fwd.hpp
	libs/cegui/impl/include/sge/cegui/impl/cegui_logger.hpp
	libs/cegui/impl/include/sge/cegui/impl/clip.hpp
	libs/cegui/impl/include/sge/cegui/impl/convert_cursor_button.hpp
	libs/cegui/impl/include/sge/cegui/impl/convert_key.hpp
	libs/cegui/impl/include/sge/cegui/impl/convert_pixel_format.hpp
	libs/cegui/impl/include/sge/cegui/impl/default_target.hpp
	libs/cegui/impl/include/sge/cegui/impl/detail/system_impl.hpp
	libs/cegui/impl/include/sge/cegui/impl/from_cegui_rect.hpp
	libs/cegui/impl/include/sge/cegui/impl/from_cegui_size.hpp
	libs/cegui/impl/include/sge/cegui/impl/from_cegui_vector2.hpp
	libs/cegui/impl/include/sge/cegui/impl/from_cegui_vector3.hpp
	libs/cegui/impl/include/sge/cegui/impl/fwds/rectf_fwd.hpp
	libs/cegui/impl/include/sge/cegui/impl/fwds/sizef_fwd.hpp
	libs/cegui/impl/include/sge/cegui/impl/fwds/vector2f_fwd.hpp
	libs/cegui/impl/include/sge/cegui/impl/fwds/vector3f_fwd.hpp
	libs/cegui/impl/include/sge/cegui/impl/geometry_buffer.hpp
	libs/cegui/impl/include/sge/cegui/impl/geometry_buffer_fwd.hpp
	libs/cegui/impl/include/sge/cegui/impl/image_codec.hpp
	libs/cegui/impl/include/sge/cegui/impl/image_codec_fwd.hpp
	libs/cegui/impl/include/sge/cegui/impl/log_name.hpp
	libs/cegui/impl/include/sge/cegui/impl/make_rasterizer_parameters.hpp
	libs/cegui/impl/include/sge/cegui/impl/matrix_from_quaternion.hpp
	libs/cegui/impl/include/sge/cegui/impl/optional_key_scan.hpp
	libs/cegui/impl/include/sge/cegui/impl/optional_key_scan_fwd.hpp
	libs/cegui/impl/include/sge/cegui/impl/optional_mouse_button.hpp
	libs/cegui/impl/include/sge/cegui/impl/optional_mouse_button_fwd.hpp
	libs/cegui/impl/include/sge/cegui/impl/optional_render_context_ref.hpp
	libs/cegui/impl/include/sge/cegui/impl/optional_render_context_ref_fwd.hpp
	libs/cegui/impl/include/sge/cegui/impl/prefix.hpp
	libs/cegui/impl/include/sge/cegui/impl/renderer.hpp
	libs/cegui/impl/include/sge/cegui/impl/renderer_fwd.hpp
	libs/cegui/impl/include/sge/cegui/impl/resource_provider.hpp
	libs/cegui/impl/include/sge/cegui/impl/resource_provider_fwd.hpp
	libs/cegui/impl/include/sge/cegui/impl/scoped_render_context.hpp
	libs/cegui/impl/include/sge/cegui/impl/scoped_system.hpp
	libs/cegui/impl/include/sge/cegui/impl/texel_scaling.hpp
	libs/cegui/impl/include/sge/cegui/impl/texture.hpp
	libs/cegui/impl/include/sge/cegui/impl/texture_fwd.hpp
	libs/cegui/impl/include/sge/cegui/impl/texture_parameters.hpp
	libs/cegui/impl/include/sge/cegui/impl/texture_parameters_fwd.hpp
	libs/cegui/impl/include/sge/cegui/impl/texture_target.hpp
	libs/cegui/impl/include/sge/cegui/impl/texture_target_fwd.hpp
	libs/cegui/impl/include/sge/cegui/impl/to_absolute_path.hpp
	libs/cegui/impl/include/sge/cegui/impl/to_blend_parameters.hpp
	libs/cegui/impl/include/sge/cegui/impl/to_cegui_rect.hpp
	libs/cegui/impl/include/sge/cegui/impl/to_cegui_size.hpp
	libs/cegui/impl/include/sge/cegui/impl/to_cegui_vector2.hpp
	libs/cegui/impl/include/sge/cegui/impl/vf/color.hpp
	libs/cegui/impl/include/sge/cegui/impl/vf/format.hpp
	libs/cegui/impl/include/sge/cegui/impl/vf/part.hpp
	libs/cegui/impl/include/sge/cegui/impl/vf/position.hpp
	libs/cegui/impl/include/sge/cegui/impl/vf/texcoord.hpp
	libs/cegui/impl/include/sge/cegui/impl/vf/vertex_view.hpp
	libs/cegui/impl/src/cegui/impl/batch.cpp
	libs/cegui/impl/src/cegui/impl/cegui_logger.cpp
	libs/cegui/impl/src/cegui/impl/convert_cursor_button.cpp
	libs/cegui/impl/src/cegui/impl/convert_key.cpp
	libs/cegui/impl/src/cegui/impl/convert_pixel_format.cpp
	libs/cegui/impl/src/cegui/impl/default_target.cpp
	libs/cegui/impl/src/cegui/impl/detail/system_impl.cpp
	libs/cegui/impl/src/cegui/impl/geometry_buffer.cpp
	libs/cegui/impl/src/cegui/impl/image_codec.cpp
	libs/cegui/impl/src/cegui/impl/log_name.cpp
	libs/cegui/impl/src/cegui/impl/make_rasterizer_parameters.cpp
	libs/cegui/impl/src/cegui/impl/matrix_from_quaternion.cpp
	libs/cegui/impl/src/cegui/impl/renderer.cpp
	libs/cegui/impl/src/cegui/impl/resource_provider.cpp
	libs/cegui/impl/src/cegui/impl/scoped_render_context.cpp
	libs/cegui/impl/src/cegui/impl/scoped_system.cpp
	libs/cegui/impl/src/cegui/impl/texel_scaling.cpp
	libs/cegui/impl/src/cegui/impl/texture.cpp
	libs/cegui/impl/src/cegui/impl/texture_parameters.cpp
	libs/cegui/impl/src/cegui/impl/texture_target.cpp
	libs/cegui/impl/src/cegui/impl/to_absolute_path.cpp
	libs/cegui/impl/src/cegui/impl/to_blend_parameters.cpp
	libs/cegui/include/sge/cegui/cursor_visibility.hpp
	libs/cegui/include/sge/cegui/cursor_visibility_fwd.hpp
	libs/cegui/include/sge/cegui/default_cursor.hpp
	libs/cegui/include/sge/cegui/default_focus.hpp
	libs/cegui/include/sge/cegui/default_font.hpp
	libs/cegui/include/sge/cegui/detail/system_impl_fwd.hpp
	libs/cegui/include/sge/cegui/duration.hpp
	libs/cegui/include/sge/cegui/exception.hpp
	libs/cegui/include/sge/cegui/load_context.hpp
	libs/cegui/include/sge/cegui/load_context_fwd.hpp
	libs/cegui/include/sge/cegui/log_location.hpp
	libs/cegui/include/sge/cegui/syringe.hpp
	libs/cegui/include/sge/cegui/syringe_fwd.hpp
	libs/cegui/include/sge/cegui/system.hpp
	libs/cegui/include/sge/cegui/system_fwd.hpp
	libs/cegui/include/sge/cegui/to_cegui_color.hpp
	libs/cegui/include/sge/cegui/to_cegui_string.hpp
	libs/cegui/include/sge/cegui/to_fcppt_string.hpp
	libs/cegui/include/sge/cegui/to_wstring.hpp
	libs/cegui/include/sge/cegui/toolbox/append_row.hpp
	libs/cegui/include/sge/cegui/toolbox/row.hpp
	libs/cegui/include/sge/cegui/toolbox/scoped_gui_sheet.hpp
	libs/cegui/include/sge/cegui/toolbox/scoped_layout.hpp
	libs/cegui/include/sge/cegui/unit.hpp
	libs/cegui/src/cegui/default_cursor.cpp
	libs/cegui/src/cegui/default_focus.cpp
	libs/cegui/src/cegui/default_font.cpp
	libs/cegui/src/cegui/exception.cpp
	libs/cegui/src/cegui/load_context.cpp
	libs/cegui/src/cegui/log_location.cpp
	libs/cegui/src/cegui/syringe.cpp
	libs/cegui/src/cegui/system.cpp
	libs/cegui/src/cegui/to_cegui_color.cpp
	libs/cegui/src/cegui/to_cegui_string.cpp
	libs/cegui/src/cegui/to_fcppt_string.cpp
	libs/cegui/src/cegui/to_wstring.cpp
	libs/cegui/src/cegui/toolbox/append_row.cpp
	libs/cegui/src/cegui/toolbox/scoped_gui_sheet.cpp
	libs/cegui/src/cegui/toolbox/scoped_layout.cpp
)

add_sge_base_library(
	cegui
	HAS_IMPL_DIR
	SGE_DEPS
		sgecharconv
		sgecore
		sgeimagecolor
		sgeimage2d
		sgeinput
		sgelog
		sgerenderer
		sgeviewport
	TRANSITIVE_SGE_DEPS
		sgecore
		sgeimagecolor_interface
		sgeimage2d_interface
		sgeinput_interface
		sgerenderer_interface
		sgeviewport_interface
	ADDITIONAL_DEPS
		${fcppt_core_TARGET}
		${fcppt_filesystem_TARGET}
		${fcppt_log_TARGET}
		${CEGUI_LIBRARIES}
		${Boost_FILESYSTEM_LIBRARIES}
		${Boost_SYSTEM_LIBRARIES}
	TRANSITIVE_ADDITIONAL_DEPS
		fcppt_core_interface
		fcppt_log_interface
		${CEGUI_LIBRARIES}
		${Boost_FILESYSTEM_LIBRARIES}
		${Boost_SYSTEM_LIBRARIES}
	INCLUDE_DIRS
		${CEGUI_INCLUDE_DIRS}
	TRANSITIVE_INCLUDE_DIRS
		${CEGUI_INCLUDE_DIRS}
	COMPILE_DEFINITIONS
		"${CEGUI_DEFINITIONS}"
)
