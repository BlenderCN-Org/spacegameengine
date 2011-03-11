/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "detail/converter_impl.hpp"
#include "detail/lock_interval.hpp"
#include "detail/locked_part_interval.hpp"
#include <sge/renderer/vf/dynamic/converter.hpp>
#include <fcppt/assert.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/scoped_ptr_impl.hpp>

sge::renderer::vf::dynamic::converter::converter(
	dynamic::part const &_part,
	dynamic::color_format_vector const &_accepted_formats
)
:
	part_(_part),
	accepted_formats_(_accepted_formats),
	written_intervals_(),
	locked_part_(),
	converter_()
{
}

sge::renderer::vf::dynamic::converter::~converter()
{
}

void
sge::renderer::vf::dynamic::converter::lock(
	dynamic::locked_part const &_locked_part
)
{
	FCPPT_ASSERT(
		!locked_part_
	);

	if(
		_locked_part.read()
		&& converter_ 
	)
		converter_->convert_lock(
			_locked_part.data(),
			written_intervals_,
			detail::locked_part_interval(
				_locked_part
			)
		);

	locked_part_ = _locked_part;
}

void
sge::renderer::vf::dynamic::converter::unlock()
{
	FCPPT_ASSERT(
		locked_part_
	);

	if(
		!converter_
	)
		converter_.take(
			fcppt::make_unique_ptr<
				detail::converter_impl
			>(
				part_,
				accepted_formats_
			)
		);
	
	if(
		locked_part_->write()
	)
	{
		dynamic::detail::lock_interval const current_unlock(
			detail::locked_part_interval(
				*locked_part_
			)
		);
			
		converter_->convert_unlock(
			locked_part_->data(),
			current_unlock
		);

		written_intervals_.insert(
			current_unlock
		);	
	}

	locked_part_.reset();
}
