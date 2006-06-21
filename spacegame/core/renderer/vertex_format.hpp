#ifndef SGE_VERTEX_FORMAT_HPP_INCLUDED
#define SGE_VERTEX_FORMAT_HPP_INCLUDED

#include <cstddef>
#include <vector>
#include <stdexcept>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/add_pointer.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/not.hpp>
#include "../main/types.hpp"
#include "./renderer_types.hpp"

namespace sge
{
	enum vertex_usage {
		VU_Pos,
		VU_Normal,
		VU_Tex,
		VU_Diffuse,
		VU_num_elements
	};

        template<vertex_usage u> struct vertex_traits;
        template<> struct vertex_traits<VU_Pos> {
		typedef space_unit            element_type;
		typedef vector3<element_type> packed_type;
	};
        template<> struct vertex_traits<VU_Normal> {
		typedef space_unit            element_type;
		typedef vector3<element_type> packed_type;
	};
        template<> struct vertex_traits<VU_Tex> {
		typedef space_unit             element_type;
		typedef vector2<element_type>* packed_type;
	};
        template<> struct vertex_traits<VU_Diffuse> {
		typedef int          element_type;
		typedef element_type packed_type;
	};
	
	typedef std::size_t vertex_size;
	typedef std::ptrdiff_t vertex_difference;

	const vertex_size vertex_element_size[] = {
		3*sizeof(vertex_traits<VU_Pos>::element_type),
		3*sizeof(vertex_traits<VU_Normal>::element_type),
		2*sizeof(vertex_traits<VU_Tex>::element_type),
		1*sizeof(vertex_traits<VU_Diffuse>::element_type)
	};

	typedef vertex_size offset_info[VU_num_elements];
	
	class vertex_element {
	public:
		vertex_element(const vertex_usage _usage, const vertex_size _count)
			: _usage(_usage), _count(_count), _size(vertex_element_size[_usage]) {}
		vertex_usage usage() const { return _usage; }
		vertex_size  size() const { return _size; }
		vertex_size  count() const { return _count; }
		vertex_size  stride() const { return size()*count(); }
	private:
		vertex_usage  _usage;
		vertex_size   _count;
		vertex_size   _size;
	};
	
	class vertex_format {
	public:
		typedef std::vector<vertex_element> usage_list;
		vertex_format() : _stride(0) {}
		const usage_list& elements() const { return ulist; }
		vertex_size stride() const { return _stride; }
		vertex_format& add(const vertex_usage u, const vertex_size count = 1)
		{
			oi[u] = _stride;
			ulist.push_back(vertex_element(u,count));
			_stride += vertex_element_size[u] * count;
			return *this;
		}
		const offset_info& offsets() const { return oi; }
	private:
		offset_info oi;
		usage_list  ulist;
		vertex_size _stride;
	};

	template<typename T, bool Deref> struct dereference_if {
		static T do_it(T t) { return t; }
	};
	template<typename T> struct dereference_if<T,true> {
		static typename boost::add_reference<typename boost::remove_pointer<T>::type >::type do_it(T t) { return *t; }
	};

        template<bool Is_Const> class vertex_pointer_impl {
        public:
                typedef char               value_type;
                typedef vertex_difference  difference_type;
                typedef vertex_size        size_type;
                typedef typename boost::mpl::if_c<Is_Const,const value_type*, value_type*>::type pointer;

                template<vertex_usage U>
			typename boost::add_reference<
			                              typename boost::mpl::if_<boost::is_const<pointer>,
			                                                       typename boost::add_const<typename vertex_traits<U>::packed_type>::type,
			                                                       typename vertex_traits<U>::packed_type>::type
			>::type element() const
		{
			typedef typename vertex_traits<U>::packed_type packed_type;
			typedef typename boost::mpl::if_<boost::is_pointer<packed_type>,
				                         packed_type,
				                         typename boost::add_pointer<packed_type>::type
							 >::type ref_to_packed;

			typedef typename boost::mpl::if_<boost::is_const<pointer>,
						         pointer_to_packed,
			                                 typename boost::add_const<pointer_to_packed>::type
							 >::type type_to_cast;
			return dereference_if<type_to_cast, boost::mpl::not_<boost::is_pointer<packed_type> >::value>::do_it(reinterpret_cast<type_to_cast>(data + oi[U]));
		}

                typename vertex_traits<VU_Pos>::packed_type pos() const { return element<VU_Pos>(); }
                typename vertex_traits<VU_Normal>::packed_type normal() const { return element<VU_Normal>(); }
                typename vertex_traits<VU_Tex>::packed_type tex() const { return element<VU_Tex>(); }
                typename vertex_traits<VU_Diffuse>::packed_type diffuse() const { return element<VU_Diffuse>(); }
		
                vertex_pointer_impl(const pointer data, const size_type stride, const offset_info& oi)
                        :data(data), stride(stride), oi(oi) {}

                template<bool OtherConst>
                vertex_pointer_impl(const vertex_pointer_impl<OtherConst>& o)
                        : data(o.data), stride(o.stride), oi(o.oi) {}

                pointer data;
        private:
                size_type stride;
                const offset_info& oi;
        };
        
	typedef vertex_pointer_impl<true>  const_vertex_pointer;
        typedef vertex_pointer_impl<false> vertex_pointer;
}

#endif
