#ifndef MAJUTSU_CLASS_HPP_INCLUDED
#define MAJUTSU_CLASS_HPP_INCLUDED

#include <majutsu/role_return_type.hpp>
#include <majutsu/memory/init_count.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/container/generation/make_vector.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/static_assert.hpp>

#ifndef MAJUTSU_MAX_CTOR_ARGS
#define MAJUTSU_MAX_CTOR_ARGS 20
#endif

namespace majutsu
{

template<
	typename Type,
	template<
		typename
	> class Memory
>
struct class_ {
	typedef Type types;

	typedef Memory<
		types
	> memory_type;

	class_()
	:
		memory_()
	{}

	class_(
		class_ const &other_
	)
	:
		memory_(
			other_.memory_
		)
	{}

	template<
		typename Argument
	>
	explicit class_(
		Argument const &argument_,
		typename boost::disable_if<
			boost::fusion::traits::is_sequence<
				Argument	
			>,
			void
		>::type * = 0
	)
	:
		memory_(
			boost::fusion::make_vector(
				argument_
			)
		)
	{
		BOOST_STATIC_ASSERT(
			memory::init_count<
				memory_type
			>::value
			== 1u
		);
	}
		
#define MAJUTSU_CLASS_MAKE_VARIADIC_CTOR(z, n, text)\
template<\
        BOOST_PP_ENUM_PARAMS_Z(\
                z,\
                n,\
                typename T\
        )>\
explicit class_(\
        BOOST_PP_ENUM_BINARY_PARAMS_Z(\
                z,\
		n,\
                const T,\
                &t\
        )\
)\
:\
	memory_(\
		boost::fusion::make_vector(\
			BOOST_PP_ENUM_PARAMS_Z(\
				z,\
				n,\
				t\
			)\
		)\
	)\
{\
	BOOST_STATIC_ASSERT(\
		memory::init_count<\
			memory_type\
		>::value == n\
	);\
}

BOOST_PP_REPEAT_FROM_TO(
	2,
        MAJUTSU_MAX_CTOR_ARGS,
        MAJUTSU_CLASS_MAKE_VARIADIC_CTOR,
        void
)

#undef MAJUTSU_CLASS_MAKE_VARIADIC_CTOR

	template<
		typename Vector
	>
	explicit class_(
		Vector const &initializers_,
		typename boost::enable_if<
			boost::fusion::traits::is_sequence<
				Vector
			>,
			void
		>::type * = 0
	)
	:
		memory_(
			initializers_
		)
	{
		BOOST_STATIC_ASSERT(
			memory::init_count<
				memory_type
			>::value
			== boost::mpl::size<
				Vector
			>::value
		);
	}
		
	template<
		typename Role,
		typename T
	>
	void
	set(
		T const &t
	)
	{
		memory_.set<
			Role
		>(
			t
		);
	}

	template<
		typename Role
	>
	typename role_return_type<
		typename memory_type::types,
		Role
	>::type
	get() const
	{
		return memory_.get<
			Role
		>();
	}

	memory_type &
	memory()
	{
		return memory_;
	}

	memory_type const &
	memory() const
	{	
		return memory_;
	}
private:
	memory_type memory_;
};

}

#endif
