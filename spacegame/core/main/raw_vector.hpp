#ifndef SGE_RAW_VECTOR_HPP_INCLUDED
#define SGE_RAW_VECTOR_HPP_INCLUDED

#include <memory>
#include <iterator>
#include <stdexcept>
#include "./algorithm.hpp"

namespace sge
{
	template<typename T, typename A = std::allocator<T> > class raw_vector {
	public:
		typedef T value_type;
		typedef A allocator_type;
		typedef typename A::size_type size_type;
		typedef typename A::difference_type difference_type;
		typedef typename A::pointer pointer;
		typedef typename A::const_pointer const_pointer;
		typedef typename A::reference reference;
		typedef typename A::const_reference const_reference;
		typedef pointer iterator;
		typedef const_pointer const_iterator;
		typedef std::reverse_iterator<iterator> reverse_iterator;
		typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

		iterator begin() { return first; }
		const_iterator begin() const { return first; }
		iterator end() { return last; }
		const_iterator end() const { return last; }

		reverse_iterator rbegin() { return reverse_iterator(last); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(last); }
		reverse_iterator rend() { return reverse_iterator(first); }
		const_reverse_iterator rend() const { return const_reverse_iterator(first); }

		reference operator[] (size_type n) { return *(first+n); }
		const_reference operator[] (size_type n) const { return *(first+n); }
		reference at(size_type n) { range_check(n); return *(first+n); }
		const_reference at(size_type n) const { range_check(n); return *(first+n); }
		reference front() { return *first; }
		const_reference front() const { return *first; }
		reference back() { return *(last-1); }
		const_reference back() const { return *(last-1); }

		pointer data() { return first; }
		const_pointer data() const { return first; }

		explicit raw_vector(const A& a = A()) : a(a), first(0), last(0), cap(0) {}
		explicit raw_vector(size_type sz, const A& _a = A())
			: a(_a), first(a.allocate(sz)), last(first+sz), cap(last) {}
		raw_vector(size_type sz, const T& t, const A& _a = A())
			: a(_a), first(a.allocate(sz)), last(first+size), cap(last)
		{
			for(iterator it = begin(); it != end(); ++it)
				*it = t;
		}

		template <class In>
			raw_vector (In beg, In end, const A& _a = A())
			: a(_a)
		{
			const difference_type len = std::distance(beg,end);
			_grow(len);
			copy(beg,end,begin());
		}
		raw_vector (const raw_vector& x)
			: a(x.a), first(a.allocate(x.size())), last(first+x.size()), cap(last)
		{
			copy(x.begin(),x.end(),begin());
		}

		~raw_vector() { a.deallocate(first,_capacity()); }

		raw_vector& operator= (const raw_vector& x)
		{
			if(&x==this) return;
			_grow(x.size());
			copy(x.begin(),x.end(),begin());
		}
		template <class In>
			void assign (In beg, In end)
		{
			const difference_type len = std::distance(beg,end);
			_grow(len);
			copy(beg,end,begin());
		}

		void assign (size_type n, const T& value)
		{
			_grow(n);
			std::uninitialized_fill_n(first,n,value);
		}

		void push_back (const T& x)
		{
			_grow(size()+1);
			back()=x;
		}

		void pop_back() { --last; }

		/*iterator insert(iterator pos, const T& x)
		{
			size_type nsize = size()+1;
			if(_capacity() < nsize)
			{
				pointer n = a.allocate(nsize), c = n;
				size_type d = std::distance(begin(),pos);
				copy(begin(),begin()+d,n);
				c+=d;
				*c = x;
				copy(++pos,end(),++c);
				a.deallocate(first,_capacity());
				first = n;
				cap = last = first + nsize;
			}
			else
			{
				_copy_backwards(pos,end());
				*pos = x;
				return pos;
			}
		}*/

		/*void insert(iterator pos, size_type sz, const T& x)
		{
			size_type nsize = size()+sz;
			if(_capacity() < nsize)
			{
				pointer n = a.allocate(nsize), c = n;
				size_type d = std::distance(begin(),pos);
				copy(begin(),begin()+d,n);
				c+=d;
				std::uninitialized_fill_n(c,c+sz,x);
				c+=sz;
				copy(++pos,end(),c);
				a.deallocate(first,_capacity());
				first = n;
				cap = last = first + nsize;
			}
			else
			{
				
			}
		}*/

		void clear() { last=first; }
		
		size_type size() const { return last-first; }
		bool empty() const { return size()==0; }
		size_type max_size() const { return a.max_size(); }
		/*void resize (size_type sz)
		{
			
		}*/

		void swap (raw_vector& x)
		{
			std::swap(first,x.first);
			std::swap(last,x.last);
			std::swap(cap,x.cap);
		}

		allocator_type get_allocator() const { return a; }
	private:
		void deallocate() { a.deallocate(first,_capacity()); last=first=cap=0; }
		void _copy_backwars(pointer first, pointer last){}
		void _grow(size_type sz)
		{
			if(sz <= _capacity())
			{
				last = first + sz;
				return;
			}
			const size_type grow_min = _capacity()*2;
			const size_type grow_size = sz > grow_min ? sz : grow_min;
			a.deallocate(first,_capacity());
			first = a.allocate(grow_size);
			cap = last = first + grow_size;
		}
		size_type _capacity() const { return cap-first; }
		void range_check(size_type n) const
		{
			if(n >= size())
				throw std::range_error("raw_vector::at() out of range!");
		}

		A a;
		pointer first, last, cap;
	};
}

#endif
