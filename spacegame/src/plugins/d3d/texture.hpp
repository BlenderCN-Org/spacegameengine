#ifndef SGE_D3D_TEXTURE_HPP_INCLUDED
#define SGE_D3D_TEXTURE_HPP_INCLUDED

#include "../../renderer/texture.hpp"
#include "./texture_base.hpp"
#include "./resource.hpp"

#include "./d3dinclude.hpp"

namespace sge
{
namespace d3d
{

class renderer;

class texture : public d3d::texture_base, public sge::texture, public resource {
	friend class renderer;
private:
	texture(renderer* r, d3d_device_ptr device, const_pointer data, size_type width, size_type height, unsigned mip_levels, resource_flag_t flags);
public:
	size_type width() const;
	size_type height() const;
	size_type size() const;
			
	void set_data(const_pointer data, const lock_rect* r);
	
	resource_flag_t flags() const;
			
	void lock(const lock_rect* r);
	void unlock();
private:
	void on_loss();
	void on_reset();

	void init();

	d3d_device_ptr   device;
	d3d_texture_ptr  tex;
	d3d_texture_ptr  temp_tex;
	resource_flag_t  _flags;
	size_type        _width;
	size_type        _height;
	unsigned         mip_levels;
	pointer          lock_dest;
};

}
}

#endif
