/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef MAJUTSU_MEMORY_DETAIL_STORE_HPP_INCLUDED
#define MAJUTSU_MEMORY_DETAIL_STORE_HPP_INCLUDED

#include <memory>
#include <algorithm>
#include <iterator>

namespace majutsu
{
namespace memory
{
namespace detail
{

template<
	typename T,
	typename Alloc = std::allocator<T>
>
class store {
public:
	typedef T value_type;
	typedef Alloc allocator_type;
	typedef typename allocator_type::size_type size_type;
	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::pointer pointer;
	typedef typename allocator_type::const_pointer const_pointer;
	typedef pointer iterator;
	typedef const_pointer const_iterator;

	explicit store(
		allocator_type const &alloc = allocator_type())
	:
		alloc(alloc),
		data_(0),
		data_end_(0),
		cap_(0)
	{}

	explicit store(
		size_type const sz,
		allocator_type const &alloc = allocator_type())
	:
		alloc(
			alloc
		),
		data_(
			alloc.allocate(
				sz
			)
		),
		data_end_(
			data_ + sz
		),
		cap_(
			data_end_
		)
	{}

	store(
		store const &s)
	:
		alloc(
			s.alloc
		),
		data_(
			alloc.allocate(s.size())
		),
		data_end_(
			data_ + s.size()
		),
		cap_(
			data_end_
		)
	{
		std::copy(
			s.data(),
			s.data_end(),
			data()
		);
	}

	store &
	operator=(
		store const &s)
	{
		deallocate();

		data_ = alloc.allocate(s.size());
		data_end_ = data_ + s.size();
		cap_ = data_end_;

		std::copy(
			s.data(),
			s.data_end(),
			data()
		);

		return *this;
	}

	~store()
	{
		deallocate();
	}

	size_type
	size() const
	{
		return
			static_cast<
				size_type
			>(
				std::distance(
					begin(),
					end()
				)
			);
	}
	
	size_type
	capacity() const
	{
		return
			static_cast<
				size_type
			>(
				cap_ - data_
			);
	}

	pointer
	data()
	{
		return data_;
	}

	const_pointer
	data() const
	{
		return data_;
	}

	pointer
	data_end()
	{
		return data_end_;
	}

	const_pointer
	data_end() const
	{
		return data_end_;
	}

	iterator begin()
	{
		return data();
	}

	const_iterator begin() const
	{
		return data();
	}

	iterator end()
	{
		return data_end();
	}

	const_iterator end() const
	{
		return data_end();
	}

	void make_space(
		iterator const first,
		size_type const sz)
	{
		size_type const nsz(
			size() + sz
		);

		if(nsz > capacity())
		{
			size_type const new_cap(
				std::max(
					nsz,
					capacity() * 2
				)
			);

			pointer const new_data(
				alloc.allocate(
					new_cap
				)
			);
		
			std::copy(
				data_,
				first,
				new_data
			);

			std::copy(
				first,
				data_end_,
				new_data + (first - begin()) + sz
			);

			deallocate();

			data_ = new_data;
			data_end_ = data_ + nsz;
			cap_ = data_ + new_cap;
		}
		else
		{
			std::copy_backward(
				first,
				end(),
				data_end() + sz
			);

			data_end_ += sz;
		}
	}

	void erase(
		iterator const first,
		iterator const last)
	{
		std::copy(
			last,
			end(),
			first
		);

		data_end_ -= std::distance(
			first,
			last
		);
	}
private:
	void deallocate()
	{
		if(data_)
			alloc.deallocate(
				data_,
				capacity()
			);
	}

	allocator_type alloc;
	pointer
		data_,
		data_end_,
		cap_;
};

}
}
}

#endif
