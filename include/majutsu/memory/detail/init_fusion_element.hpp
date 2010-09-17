#ifndef MAJUTSU_MEMORY_DETAIL_INIT_FUSION_ELEMENT_HPP_INCLUDED
#define MAJUTSU_MEMORY_DETAIL_INIT_FUSION_ELEMENT_HPP_INCLUDED

#include <majutsu/memory/detail/index_of.hpp>
#include <majutsu/is_constant.hpp>
#include <majutsu/is_role.hpp>
#include <boost/mpl/filter_view.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/or.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/utility/enable_if.hpp>

namespace majutsu
{
namespace memory
{
namespace detail
{

template<
	typename Elements,
	typename Arguments
>
struct init_fusion_element {
	template<
		typename
	>
	struct result;

	template<
		typename Elem
	>
	struct result<
		init_fusion_element(
			Elem
		)
	>
	{
		typedef typename boost::remove_const<
			typename boost::remove_reference<
				Elem
			>::type
		>::type::type type;
	};
	

	explicit init_fusion_element(
		Arguments const &arguments_
	)
	:
		arguments_(arguments_)
	{}

	template<
		typename Type
	>
	typename boost::enable_if<
		majutsu::is_constant<
			Type
		>,
		typename Type::type
	>::type
	operator()(
		Type const &
	) const
	{
		return Type::value;
	}

	template<
		typename Type
	>
	typename boost::enable_if<
		majutsu::is_role<
			Type
		>,
		typename Type::type
	>::type
	operator()(
		Type const &
	) const
	{
		typedef boost::mpl::filter_view<
			Elements,
			majutsu::is_role<
				boost::mpl::_1
			>
		> roles;

		return
			boost::fusion::at<
				typename index_of<
					roles,
					typename boost::mpl::find<
						roles,
						Type
					>::type
				>::type
			>(
				arguments_
			);
	}

	template<
		typename Type
	>
	typename boost::disable_if<
		boost::mpl::or_<
			majutsu::is_constant<
				Type
			>,
			majutsu::is_role<
				Type
			>
		>,
		typename Type::type
	>::type
	operator()(
		Type const &
	) const
	{
		return typename Type::type();
	}
private:
	Arguments const &arguments_;
};

}
}
}

#endif
