#ifndef SGE_GRAPH_OBJECT_HPP_INCLUDED
#define SGE_GRAPH_OBJECT_HPP_INCLUDED

#include <sge/graph/scalar.hpp>
#include <sge/graph/symbol.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/sprite/buffers/single.hpp>
#include <sge/sprite/buffers/with_declaration.hpp>
#include <sge/sprite/config/choices.hpp>
#include <sge/sprite/config/float_type.hpp>
#include <sge/sprite/config/normal_size.hpp>
#include <sge/sprite/config/texture_coordinates.hpp>
#include <sge/sprite/config/texture_level_count.hpp>
#include <sge/sprite/config/texture_ownership.hpp>
#include <sge/sprite/config/type_choices.hpp>
#include <sge/sprite/config/unit_type.hpp>
#include <sge/sprite/config/with_texture.hpp>
#include <sge/sprite/object.hpp>
#include <sge/sprite/parameters.hpp>
#include <sge/renderer/texture/planar_scoped_ptr.hpp>
#include <sge/renderer/context/object.hpp>
#include <sge/renderer/device.hpp>

namespace sge
{
namespace graph
{
class object
{
FCPPT_NONCOPYABLE(
	object);
public:
	SGE_GRAPH_SYMBOL
	object(
		sge::image2d::dim &,
		sge::renderer::device &);

	SGE_GRAPH_SYMBOL
	void
	push(
		sge::graph::scalar _datum);

	SGE_GRAPH_SYMBOL
	void
	render(
		sge::renderer::context::object &);

	SGE_GRAPH_SYMBOL
	~object();

private:
	typedef sge::sprite::config::choices<
		sge::sprite::config::type_choices<
			sge::sprite::config::unit_type<
				int
			>,
			sge::sprite::config::float_type<
				float
			>
		>,
		sge::sprite::config::normal_size,
		boost::mpl::vector1<
			sge::sprite::config::with_texture<
				sge::sprite::config::texture_level_count<
					1u
				>,
				sge::sprite::config::texture_coordinates::automatic,
				sge::sprite::config::texture_ownership::shared
			>
		>
	> sprite_choices;

	typedef sge::sprite::object<
		sprite_choices
	> sprite_object;

	typedef sge::sprite::parameters<
		sprite_choices
	> sprite_parameters;

	typedef sge::sprite::buffers::with_declaration<
		sge::sprite::buffers::single<
			sprite_choices
		>
	> sprite_buffers_type;

	sge::renderer::texture::planar_scoped_ptr const
	texture_;

	sprite_object const
	sprite_object_;

	sprite_buffers_type
	sprite_buffers_;

};
}
}

#endif
