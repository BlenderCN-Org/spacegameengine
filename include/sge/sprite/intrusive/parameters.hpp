#ifndef SGE_SPRITE_INTRUSIVE_PARAMETERS_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_PARAMETERS_HPP_INCLUDED

#include <sge/sprite/intrusive/object_fwd.hpp>
#include <sge/sprite/intrusive/system_fwd.hpp>
#include <sge/sprite/intrusive/order.hpp>
#include <sge/sprite/point.hpp>
#include <sge/sprite/dim.hpp>
#include <sge/sprite/color.hpp>
#include <sge/sprite/depth_type.hpp>
#include <sge/sprite/rotation_type.hpp>
#include <sge/sprite/repetition_type.hpp>
#include <sge/sprite/parameters.hpp>
#include <sge/texture/part_fwd.hpp>
#include <sge/export.hpp>

namespace sge
{
namespace sprite
{
namespace intrusive
{

class parameters
{
public:
	SGE_SYMBOL parameters(
		system &,
		order);

	SGE_SYMBOL parameters &pos(point const &);
	SGE_SYMBOL parameters &texture(texture::const_part_ptr);
	SGE_SYMBOL parameters &size(dim const &);
	SGE_SYMBOL parameters &color(sge::sprite::color const &);
	SGE_SYMBOL parameters &depth(depth_type);
	SGE_SYMBOL parameters &rotation(rotation_type);
	SGE_SYMBOL parameters &visible(bool);

	SGE_SYMBOL operator object() const;
private:
	system &system_;
	order order_;
	point pos_;
	texture::const_part_ptr texture_;
	dim size_;
	sge::sprite::color color_;
	depth_type depth_;
	rotation_type rotation_;
	bool visible_;

};

}
}
}

#endif
