#ifndef SGE_RENDERER_TEXTURE_RW_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_RW_HPP_INCLUDED

#include "texture_fwd.hpp"
#include "texture.hpp"
#include "lock_rect.hpp"
#include "../export.hpp"
#include <boost/optional.hpp>
#include <boost/scoped_ptr.hpp>

namespace sge
{
namespace renderer
{
class SGE_CLASS_SYMBOL texture_rw : public texture
{
	public:
	SGE_SYMBOL texture_rw(texture_ptr read,texture_ptr write);
	SGE_SYMBOL ~texture_rw();
	SGE_SYMBOL dim_type const dim() const;
	SGE_SYMBOL image_view const lock(lock_rect const &, lock_flag_t);
	SGE_SYMBOL const_image_view const lock(lock_rect const &) const;
	SGE_SYMBOL void unlock() const;
	SGE_SYMBOL resource_flag_t flags() const;

	struct lock_data;
	private:
	mutable texture_ptr read, write;

	mutable boost::scoped_ptr<lock_data> locked;
};
}
}

#endif
