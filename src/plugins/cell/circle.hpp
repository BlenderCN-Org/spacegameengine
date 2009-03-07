#ifndef SGE_CELL_CIRCLE_HPP_INCLUDED
#define SGE_CELL_CIRCLE_HPP_INCLUDED

#include "register_callback.hpp"
#include "unregister_callback.hpp"
#include "collision_callback.hpp"
#include "circle_list.hpp"
#include <sge/collision/objects/circle.hpp>
#include <sge/collision/callbacks.hpp>
#include <sge/collision/satellite_fwd.hpp>
#include <sge/math/vector/basic_decl.hpp>
#include <sge/time/funit.hpp>
#include <vector>

namespace sge
{
namespace cell
{

class grid;
class backlink;

class circle : public collision::objects::circle {
public:
	circle(
		collision::satellite_ptr,
		collision::point const &center,
		collision::point const &speed,
		collision::unit radius,
		grid &,
		collision::test_callback const &,
		collision_callback const &,
		register_callback const &,
		unregister_callback const &);
	
	void center(
		collision::point const &);
	
	collision::point const
	center() const;

	void speed(
		collision::point const &);
	
	collision::point const
	speed() const;

	collision::unit radius() const;
	collision::satellite &satellite();

	void update(
		time::funit);

	~circle();
private:
	void reposition();

	collision::satellite_ptr sat;

	collision::point
		center_,
		speed_;
	collision::unit const radius_;

	grid &grid_;

	typedef std::vector<
		backlink
	> backlink_vector;

	collision::test_callback const test_callback;
	collision_callback const callback;
	register_callback const register_;
	unregister_callback const unregister_;
	circle_list::iterator const list_pos;
	backlink_vector backlinks;
};

}
}

#endif
