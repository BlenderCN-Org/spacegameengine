/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SRC_PLUGIN_INSTANTIATE_TYPES_HPP_INCLUDED
#define SGE_SRC_PLUGIN_INSTANTIATE_TYPES_HPP_INCLUDED

#include <sge/src/export_class_instantiation.hpp>
#include <sge/src/export_function_instantiation.hpp>
#include <sge/src/plugin/context_impl.hpp>
#include <sge/src/plugin/iterator_impl.hpp>
#include <sge/src/plugin/manager_impl.hpp>
#include <sge/src/plugin/object_impl.hpp>


#define SGE_PLUGIN_INSTANTIATE_TYPES(\
	plugin_type\
)\
template SGE_EXPORT_FUNCTION_INSTANTIATION \
sge::plugin::iterator<plugin_type> \
sge::plugin::manager::begin<plugin_type>();\
\
template SGE_EXPORT_FUNCTION_INSTANTIATION \
sge::plugin::iterator<plugin_type> \
sge::plugin::manager::end<plugin_type>();\
\
template SGE_EXPORT_FUNCTION_INSTANTIATION \
sge::plugin::context<plugin_type> \
sge::plugin::manager::plugin<plugin_type>(\
	sge::plugin::manager::size_type\
);\
\
template SGE_EXPORT_FUNCTION_INSTANTIATION \
sge::plugin::manager::size_type \
sge::plugin::manager::size<plugin_type>() const;\
\
template \
class \
SGE_EXPORT_CLASS_INSTANTIATION \
sge::plugin::iterator<plugin_type>;\
\
template \
class \
SGE_EXPORT_CLASS_INSTANTIATION \
sge::plugin::object<plugin_type>;\
\
template \
class \
SGE_EXPORT_CLASS_INSTANTIATION \
sge::plugin::context<plugin_type>;

#endif
