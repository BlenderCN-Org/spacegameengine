#include <locale>
#include "../renderer.hpp"
#include "../vertex_buffer.hpp"
#include "../index_buffer.hpp"
#include "../renderer_types.hpp"
#include "../transform.hpp"
#include "../lock_ptr.hpp"
#include "../font.hpp"
#include "../../sprite/helper.hpp"
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>

sge::font::font(const renderer_ptr r, const font_system_ptr font_sys, const std::string& font_name, const font_weight weight)
 : r(r),
 impl(font_sys->create_font(r,font_name,weight)),
 vb(r->create_vertex_buffer(vertex_format().add(VU_Pos).add(VU_Tex),200)),
 ib(r->create_index_buffer(vb->size()*3/2))
{
	height_pixel_scale(1);
}

void sge::font::height_pixel_scale(const unsigned scale)
{
	height(font_unit(impl->optimal_height_base()*scale) / r->screen_height());
}

sge::font_unit sge::font::height() const
{
	return _height;
}

sge::font_unit sge::font::optimal_height_base() const
{
	return font_unit(impl->optimal_height_base()) / r->screen_height();
}

void sge::font::height(const space_unit h)
{
	_height = h;
}

sge::font_size sge::font::draw_text(const string_type& text, const font_pos start_pos,
                                    const font_size max_sz, const color col, const font_flag_t flags)
{
	if(text.empty() || height() > max_sz.h)
		return font_size();
	if(!last_texture)
		last_texture = impl->load_char(text[0]).tex;

	last_index = 0;

	const vertex_buffer::size_type vbsize = text.size()*4;
	const index_buffer::size_type ibsize = text.size()*6;

	if(vb->size() < vbsize)
		vb->resize(vbsize);

	if(ib->size() < ibsize)
		ib->resize(ibsize);

	font_pos pos = start_pos;
	if(flags & FTF_AlignVCenter || flags & FTF_AlignBottom)
	{
		const font_unit text_height = text_size(text.begin(), text.end(), max_sz.w, flags).h;
		if(flags & FTF_AlignVCenter)
			pos.y += (max_sz.h - text_height) / 2.f;
		else if(flags & FTF_AlignBottom)
			pos.y += max_sz.h - text_height;
		if(pos.y < start_pos.y)
			pos.y = start_pos.y;
	}

	r->set_int_state(IS_AmbientLightColor,col);

	font_size sz;
	string_type::const_iterator sbeg(text.begin()),
	                            send(text.end());

	lock_ptr<vertex_buffer_ptr> _lock(vb,LF_Discard);
	vertex_buffer::iterator vit = vb->begin();

	while(sbeg != text.end() && sz.h + height() < max_sz.h)
	{
		send = text.end();
		const font_unit width = line_width(sbeg, send, max_sz.w, flags);

		pos.x = start_pos.x;
		if(flags & FTF_AlignHCenter)
			pos.x += (max_sz.w - width) / 2;
		else if(flags & FTF_AlignRight)
			pos.x += max_sz.w - width;

		for(;sbeg != send; ++sbeg)
		{
			const font_entity reg = impl->load_char(*sbeg);
			const font_size      sz(char_width(*sbeg), height() * reg.h_scale);
			const font_rect      fp(font_pos(pos.x, pos.y + height() * reg.top), sz); // FIXME: font top positioning

			if(last_texture != reg.tex)
			{
				add_job(std::distance(text.begin(),sbeg));
				last_texture = reg.tex;
			}

			fill_sprite_in_vb(vit, fp, reg.rect);
			pos.x += sz.w;
		}

		sbeg = send;
		sz.w = std::max(sz.w, width);
		sz.h += height();

		if(flags & FTF_NoMultiLine)
			break;

		pos.y += height();
	}
	_lock.unlock();
	add_job(std::distance(text.begin(),send));
	flush();
	return sz;
}

void sge::font::add_job(const size_type cur_index)
{
	jobs.push_back(job(last_texture, last_index, cur_index));
	last_index = cur_index;
}

sge::font_unit sge::font::char_width(const char_type ch) const
{
	const font_entity entity = impl->load_char(ch);
	if(entity.rect.height() == 0)
		return 0;
	return (entity.rect.width() / entity.rect.height()) * height() * entity.h_scale;
}

sge::font_unit sge::font::text_width_unformatted(string_type::const_iterator sbeg, string_type::const_iterator& send, const font_unit width) const
{
	font_unit w(0);
	for(; sbeg != send; ++sbeg)
	{
		if(w + char_width(*sbeg) > width)
			break;
		w += char_width(*sbeg);
	}
	send = sbeg;
	return w;
}

sge::font_size sge::font::text_size(string_type::const_iterator sbeg, string_type::const_iterator send, const font_unit width, const font_flag_t flags) const
{
	if(flags & FTF_NoMultiLine)
		return font_size(line_width(sbeg, send, width, flags), height());

	font_size sz;
	while(sbeg != send)
	{
		sz.w += std::max(sz.w, line_width(sbeg, send, width, flags));
		sz.h += height();
		sbeg = send;
	}
	return sz;
}

sge::font_unit sge::font::line_width(string_type::const_iterator sbeg, string_type::const_iterator& send, const font_unit width, const font_flag_t flags) const
{
	if(flags & FTF_NoMultiLine)
		return text_width_unformatted(sbeg, send, width);

	font_unit w(0), last_width(0);
	string_type::const_iterator last_white = sbeg;

	for(;sbeg != send; ++sbeg)
	{
		if(std::isspace(*sbeg,std::locale()))
		{
			last_white = sbeg;
			last_width = w;
		}
		w += char_width(*sbeg);
		if(last_width > 0 && w > width)
		{
			send = ++last_white;
			return last_width;
		}
	}
	return w;
}

void sge::font::flush()
{
	std::sort(jobs.begin(),jobs.end(), boost::lambda::bind(&job::tex, boost::lambda::_1) < boost::lambda::bind(&job::tex, boost::lambda::_2));
	{
		lock_ptr<index_buffer_ptr> _lock(ib,LF_Discard);
		index_buffer::iterator iib = ib->begin();
		for(job_array::const_iterator it = jobs.begin(); it != jobs.end(); ++it)
			for(size_type i = it->first_index; i <= it->last_index; ++i)
				fill_sprite_indices(iib, i*4);
	}

	set_parameters();
	r->set_texture(0,last_texture);
	for(job_array::const_iterator it = jobs.begin(); it != jobs.end(); ++it)
	{
		if(it->tex != last_texture)
		{
			r->set_texture(0,it->tex);
			last_texture = it->tex;
		}
		r->render(vb, ib, 0, vb->size(), PT_Triangle, (it->last_index-it->first_index+1)*2, it->first_index*6);
	}
	jobs.clear();
}

void sge::font::set_parameters()
{
	r->projection_orthogonal();
	r->set_bool_state(BS_EnableAlphaBlending,true);
	r->set_material(material(color4(1,1,1,1),color4(1,1,1,1)));
	r->set_filter_state(0,FARG_MinFilter,FARGV_Point);
	r->set_filter_state(0,FARG_MagFilter,FARGV_Point);
}
