#ifndef FRUITCUT_GRAPHICS_CAMERA_OBJECT_HPP_INCLUDED
#define FRUITCUT_GRAPHICS_CAMERA_OBJECT_HPP_INCLUDED

#include <sge/camera/parameters_fwd.hpp>
#include <sge/camera/projection/object.hpp>
#include <sge/camera/gizmo_type.hpp>
#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/vector3.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/input/keyboard/key_event_fwd.hpp>
#include <sge/input/mouse/axis_event_fwd.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/math/matrix/basic_impl.hpp>

namespace sge
{
namespace camera
{
/// The camera is a class which holds a gizmo (the camera position and
/// orientation) and manipulates it via keyboard and mouse input. It
/// also offers all of the transformation matrices to be used in the
/// shaders, including the perspective matrix (the other ones you
/// could derive from the gizmo).
class object
{
public:
	object(object const &) = delete;
	object &operator=(object const &) = delete;

	explicit
	object(
		parameters const &);
	
	void
	update(
		renderer::scalar);
	
	renderer::matrix4 const
	world() const;

	renderer::matrix4 const
	rotation() const;

	renderer::matrix4 const
	translation() const;

	renderer::matrix4 const
	projection() const;

	renderer::matrix4 const 
	mvp() const;

	gizmo_type const &
	gizmo() const;

	gizmo_type &
	gizmo();
private:
	fcppt::signal::scoped_connection keyboard_connection_,mouse_axis_connection_;
	projection::object const projection_;
	renderer::matrix4 const projection_matrix_;
	// Rotation speed means mouse sensitivity, movement-speed should be
	// self-explanatory
	renderer::scalar const movement_speed_,rotation_speed_;
	// The camera's position and orientation
	gizmo_type gizmo_;
	// Those are the directions the camera currently moves in
	// (corresponds to the movement keys currently pressed)
	renderer::vector3 dirs_;

	void
	key_callback(
		sge::input::keyboard::key_event const &);

	void
	mouse_axis_callback(
		sge::input::mouse::axis_event const &);
};
}
}

#endif
