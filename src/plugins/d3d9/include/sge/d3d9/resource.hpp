/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_D3D9_RESOURCE_HPP_INCLUDED
#define SGE_D3D9_RESOURCE_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/needs_reset_fwd.hpp>
#include <sge/d3d9/resource_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/intrusive/list_hook.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace d3d9
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

class resource
:
	public boost::intrusive::list_base_hook<
		boost::intrusive::link_mode<
			boost::intrusive::auto_unlink
		>
	>
{
	FCPPT_NONCOPYABLE(
		resource
	);
public:
	explicit
	resource(
		D3DPOOL
	);

	explicit
	resource(
		sge::d3d9::needs_reset
	);

	virtual ~resource();

	void
	loss();

	void
	reset();

	D3DPOOL
	pool() const;

	bool
	needs_reset() const ;
private:
	virtual void
	on_loss() = 0;

	virtual void
	on_reset() = 0;

	D3DPOOL const pool_;
};

FCPPT_PP_POP_WARNING

}
}

#endif
