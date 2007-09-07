/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_PLUGIN_IMPL_HPP_INCLUDED
#define SGE_PLUGIN_IMPL_HPP_INCLUDED

template<typename T>
sge::plugin<T>::plugin(const std::string& path)
: lib(path),
  loader(lib.load_function<loader_fun>(detail::plugin_traits<T>::plugin_loader_name()))
{}

template<typename T>
typename sge::plugin<T>::loader_fun sge::plugin<T>::get() const
{
	return loader;
}

#endif
