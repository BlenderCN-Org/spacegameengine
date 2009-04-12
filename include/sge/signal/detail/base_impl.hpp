#ifndef SGE_SIGNAL_DETAIL_BASE_IMPL_HPP_INCLUDED
#define SGE_SIGNAL_DETAIL_BASE_IMPL_HPP_INCLUDED

#include <sge/signal/detail/concrete_connection_impl.hpp>

template<typename T>
sge::signal::auto_connection
sge::signal::detail::base<T>::connect(
	function_type const &f)
{
	auto_connection a(
		new concrete_connection(f));
	connections_.push_back(static_cast<concrete_connection &>(*a));
	return a;
}

template<typename T>
sge::signal::detail::base<T>::base()
{}

template<typename T>
typename sge::signal::detail::base<T>::connection_list &
sge::signal::detail::base<T>::connections()
{
	return connections_;
}

#endif
