/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_RENDERER_CONST_LINEAR_BUFFER_SCOPED_LOCK_HPP_INCLUDED
#define SGE_RENDERER_CONST_LINEAR_BUFFER_SCOPED_LOCK_HPP_INCLUDED

#include <sge/renderer/npos.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{

/**
\brief A linear buffer lock that is readonly.

\ingroup sge_renderer

Creates a box with value type renderer::size_type.
Used for locking sge::renderer::vertex::buffer and
sge::renderer::index::buffer. It locks the buffer in the constructor and
unlocks it in the destructor.

\see sge::renderer::vertex::const_scoped_lock
\see sge::renderer::index::const_scoped_lock
*/
template<
	typename Buffer,
	typename Types
>
class const_linear_buffer_scoped_lock
{
	FCPPT_NONCOPYABLE(
		const_linear_buffer_scoped_lock
	);
public:
	/**
	 * \brief The offset type
	 *
	 * Used to tell at which element the lock will start.
	*/
	typedef typename Types::first_type first_type;

	/**
	 * \brief The count type
	 *
	 * Used to tell how many elements will be locked.
	*/
	typedef typename Types::count_type count_type;

	/**
	 * \brief The view type of the lock.
	*/
	typedef typename Types::const_view_type view_type;

	/**
	 * \brief Locks a buffer
	 *
	 * Locks \a buffer. The buffer will be locked starting from \a first to
	 * \a first + \a count, or the entire will be locked if \a first is 0
	 * and \a count is renderer::npos, which is the default.
	 *
	 * \param buffer The buffer to lock
	 *
	 * \param first The offset to lock the buffer from
	 *
	 * \param count The number of elements to lock, or npos for all
	 * elements
	 *
	 * \warning The behaviour is undefined if the buffer is already locked
	 * or if the region is out of range
	 *
	 * \warning The behaviour is undefined if the buffer hasn't been
	 * created with resource_flags::readable
	*/
	SGE_RENDERER_DETAIL_SYMBOL
	explicit const_linear_buffer_scoped_lock(
		Buffer const &buffer,
		first_type first =
			first_type(0u),
		count_type count =
			count_type(
				renderer::npos()
			)
	);

	/**
	 * \brief Obtain the view of the locked region
	 *
	 * \return The view of the locked region
	*/
	SGE_RENDERER_DETAIL_SYMBOL
	view_type const
	value() const;

	/**
	 * \brief Unlocks the buffer
	 *
	 * \warning The behaviour is undefined if the buffer has been locked
	 * again or unlocked in between the constructor and destructor
	*/
	SGE_RENDERER_DETAIL_SYMBOL
	~const_linear_buffer_scoped_lock();
private:
	Buffer const &buffer_;

	view_type const view_;
};

}
}

#endif
