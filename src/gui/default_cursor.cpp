#include <sge/gui/default_cursor.hpp>
#include <sge/gui/media_path.hpp>
#include <sge/renderer/device.hpp>
#include <sge/sprite/parameters.hpp>
#include <sge/image/loader.hpp>
#include <sge/image/object.hpp>
#include <sge/texture/no_fragmented.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/texture/consume_and_set_fragment.hpp>
#include <sge/renderer/filter/linear.hpp>
#include <sge/structure_cast.hpp>
#include <sge/make_shared_ptr.hpp>
#include <sge/text.hpp>

sge::gui::default_cursor::default_cursor(
	sge::image::loader_ptr const il,
	sge::renderer::device_ptr const rend)
:
	texture_(
		rend,
		renderer::color_format::rgba8,
		renderer::filter::linear),
	sprite_(
		sprite::parameters()
			.texture(
				texture::consume_and_set_fragment(
					texture_,
					il->load(
							media_path()/
							SGE_TEXT("gui")/
							SGE_TEXT("cursor.png"))
						->view()))
			.size(
				sprite::texture_dim)
			.depth(
				static_cast<sprite::depth_type>(0))),
	click_(16,16)
{
}

void sge::gui::default_cursor::pos(
	point const &p)
{
	sprite_.pos() = sge::structure_cast<sge::sprite::point>(
		p);
}

sge::gui::point const sge::gui::default_cursor::pos() const
{
	return sge::structure_cast<sge::gui::point>(
		sprite_.pos());
}

sge::sprite::object const sge::gui::default_cursor::sprite() const
{
	return sprite_;
}

sge::sprite::object &sge::gui::default_cursor::mutable_sprite()
{
	return sprite_;
}

sge::gui::default_cursor::~default_cursor() {}
