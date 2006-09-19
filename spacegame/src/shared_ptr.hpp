#ifndef SGE_SHARED_PTR_HPP_INCLUDED
#define SGE_SHARED_PTR_HPP_INCLUDED

#include <ostream>
#include "./smart_ptr_policies.hpp"
#include <cstddef>
#include <boost/shared_ptr.hpp>

namespace sge
{
/*
namespace detail {
struct dynamic_cast_struct{};
}
	
template<typename T, template <typename> class Deleter = heap_deleter> class shared_ptr : Deleter<T> {
	typedef std::size_t counter_type;
public:
	typedef T&    reference;
	typedef T*    pointer;
	
	shared_ptr()
		: ptr(0), counter(new counter_type(1)) {}

	explicit shared_ptr(pointer p)
		: ptr(p), counter(new counter_type(1)) {}

	shared_ptr(const shared_ptr& r) { _assign(r); }
	template<typename Other> shared_ptr(const shared_ptr<Other,Deleter>& r) { _assign(r); }
	template<typename Other> shared_ptr(const shared_ptr<Other,Deleter>& r, detail::dynamic_cast_struct)
	{
		counter = r.counter;
		++(*counter);
		ptr = dynamic_cast<pointer>(r.get());
	}
		
	shared_ptr& operator=(const shared_ptr& r)
	{
		if(r != *this)
		{
			_release();
			_assign(r);
		}
		return *this;
	}
		
	pointer get() const { return ptr; }
	pointer operator->() const { return ptr; }
	reference operator*() const { return *ptr; }

	~shared_ptr() { _release(); }

	void reset(pointer p = 0)
	{
		if(p != get())
		{
			_release();
			ptr = p;
			counter = new counter_type(1);
		}
	}
private:
	template<typename Other, template<typename> class OtherDeleter> friend class shared_ptr;

	void _release()
	{
		if(--(*counter) == 0)
		{
			delete_(ptr);
			ptr = 0;
			delete counter;
			counter = 0;
		}
	}

	void _assign(const shared_ptr& r)
	{
		counter = r.counter;
		ptr = r.get();
		++(*counter);
	}
	template<typename Other> void _assign(const shared_ptr<Other,Deleter>& r)
	{
		counter = r.counter;
		ptr = r.get();
		++(*counter);
	}
private:
	pointer        ptr;
	counter_type*  counter;
};

template<typename T, template<typename> class D> bool operator< (const shared_ptr<T,D>& l, const shared_ptr<T,D>& r)
{
	return l.get() < r.get();
}

template<typename T, template<typename> class D> bool operator== (const shared_ptr<T,D>& l, const shared_ptr<T,D>& r)
{
	return l.get() == r.get();
}

template<typename T, template<typename> class D> bool operator!= (const shared_ptr<T,D>& l, const shared_ptr<T,D>& r)
{
	return !(l == r);
}

template<typename T, template<typename> class D> std::ostream& operator<< (std::ostream& s, const shared_ptr<T,D>& r)
{
	return s << r.get();
}

template<typename T, typename U, template<typename> class D> shared_ptr<T,D> dynamic_pointer_cast(const shared_ptr<U,D>& s)
{
	return shared_ptr<T,D>(s, detail::dynamic_cast_struct());
}
*/

using boost::shared_ptr;
using boost::dynamic_pointer_cast;

}

#endif
