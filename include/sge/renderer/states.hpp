/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2008       Simon Stienen    (s.stienen@slashlife.org)

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


#ifndef SGE_RENDERER_STATES_HPP_INCLUDED
#define SGE_RENDERER_STATES_HPP_INCLUDED

#include "../export.hpp"
#include "color.hpp"
#include <boost/variant.hpp>
#include <set>

namespace sge
{
namespace renderer
{

template<typename T>
struct state_var_traits;

template<> struct state_var_traits<int> { enum available_states {
	stencil_clear_val
}; };

template<> struct state_var_traits<float> { enum available_states {
	zbuffer_clear_val,
	fog_start,
	fog_end,
	fog_density
}; };

template<> struct state_var_traits<bool> { enum available_states {
	clear_zbuffer,
	clear_backbuffer,
	clear_stencil,
	enable_alpha_blending,
	enable_lighting
}; };

template<> struct state_var_traits<color> { enum available_states {
	clear_color,
	ambient_light_color,
	fog_color
}; };

namespace state_cull_mode_type {
	enum type {
		off,
		back,
		front
	};
}

template<>
struct state_var_traits<state_cull_mode_type::type> {
	enum available_states {
		singular
	};
};

namespace state_depth_func_type
{
	enum type {
		off,
		never,
		less,
		equal,
		less_equal,
		greater,
		not_equal,
		greater_equal,
		always
	};
}

template<>
struct state_var_traits<state_depth_func_type::type> {
	enum available_states {
		singular
	};
};

namespace state_stencil_func_type
{
	enum type {
		off,
		never,
		less,
		equal,
		less_equal,
		greater,
		not_equal,
		greater_equal,
		always
	};
}

template<>
struct state_var_traits<state_stencil_func_type::type> {
	enum available_states {
		singular
	};
};

namespace state_fog_mode_type {
	enum type {
		off,
		linear,
		exp,
		exp2
	};
}

template<>
struct state_var_traits<state_fog_mode_type::type> {
	enum available_states {
		singular
	};
};

namespace state_draw_mode_type
{
	enum type {
		point,
		line,
		fill
	};
}

template<>
struct state_var_traits<state_draw_mode_type::type> {
	enum available_states {
		singular
	};
};

namespace state_source_blend_func_type
{
	enum type {
		zero,
		one,
		dest_color,
		inv_dest_color,
		src_alpha,
		inv_src_alpha,
		dest_alpha,
		inv_dest_alpha,
		src_alpha_sat
	};
}

template<>
struct state_var_traits<state_source_blend_func_type::type> {
	enum available_states {
		singular
	};
};

namespace state_dest_blend_func_type
{
	enum type {
		zero,
		one,
		src_color,
		inv_src_color,
		src_alpha,
		inv_src_alpha,
		dest_alpha,
		inv_dest_alpha
	};
}

template<>
struct state_var_traits<state_dest_blend_func_type::type> {
	enum available_states {
		singular
	};
};

template<typename T>
struct state_var {
	typedef T value_type;

	SGE_SYMBOL state_var<T> operator=(T newval);
	
	SGE_SYMBOL T value() const;

	const typename state_var_traits<T>::available_states state_id;

	SGE_SYMBOL explicit state_var(
		const typename state_var_traits<T>::available_states state_id,
		const T defval = T());

	SGE_SYMBOL bool operator<(state_var const&) const;
private:
	T val;
};

namespace int_state {
	typedef state_var<int> type;
	SGE_SYMBOL extern type
		stencil_clear_val;
}

namespace float_state {
	typedef state_var<float> type;
	SGE_SYMBOL extern type
		zbuffer_clear_val,
		fog_start,
		fog_end,
		fog_density;
}

namespace bool_state {
	typedef state_var<bool> type;
	SGE_SYMBOL extern type
		clear_zbuffer,
		clear_backbuffer,
		clear_stencil,
		enable_alpha_blending,
		enable_lighting;
}

namespace color_state {
	typedef state_var<color> type;
	SGE_SYMBOL extern type
		clear_color,
		ambient_light_color,
		fog_color;
}

namespace cull_mode {
	typedef state_var<state_cull_mode_type::type> type;
	SGE_SYMBOL extern const type
		off,
		back,
		front;
}

namespace depth_func {
	typedef state_var<state_depth_func_type::type> type;
	SGE_SYMBOL extern const type
		off,
		never,
		less,
		equal,
		less_equal,
		greater,
		not_equal,
		greater_equal,
		always;
}

namespace stencil_func {
	typedef state_var<state_stencil_func_type::type> type;
	SGE_SYMBOL extern const type
		off,
		never,
		less,
		equal,
		less_equal,
		greater,
		not_equal,
		greater_equal,
		always;
}

namespace fog_mode {
	typedef state_var<state_fog_mode_type::type> type;
	SGE_SYMBOL extern const type
		off,
		linear,
		exp,
		exp2;
}

namespace draw_mode {
	typedef state_var<state_draw_mode_type::type> type;
	SGE_SYMBOL extern const type
		point,
		line,
		fill;
}

namespace source_blend_func {
	typedef state_var<state_source_blend_func_type::type> type;
	SGE_SYMBOL extern const type
		zero,
		one,
		dest_color,
		inv_dest_color,
		src_alpha,
		inv_src_alpha,
		dest_alpha,
		inv_dest_alpha,
		src_alpha_sat;
}

namespace dest_blend_func {
	typedef state_var<state_dest_blend_func_type::type> type;
	SGE_SYMBOL extern const type
		zero,
		one,
		src_color,
		inv_src_color,
		src_alpha,
		inv_src_alpha,
		dest_alpha,
		inv_dest_alpha;
}

typedef boost::variant<
	int_state::type,
	float_state::type,
	bool_state::type,
	color_state::type,
	cull_mode::type,
	depth_func::type,
	stencil_func::type,
	fog_mode::type,
	draw_mode::type,
	source_blend_func::type,
	dest_blend_func::type
> any_state;


class state_list {
public:
	SGE_SYMBOL state_list();
	SGE_SYMBOL explicit state_list(
		any_state const &);
	SGE_SYMBOL const state_list operator()(
		any_state const&) const;

	SGE_SYMBOL void overwrite(
		any_state const&);

	typedef std::set<any_state> set_type;
	SGE_SYMBOL set_type const& get() const;
private:
	set_type set_;
};

}
}

#endif // SGE_RENDERER_STATES_HPP_INCLUDED
