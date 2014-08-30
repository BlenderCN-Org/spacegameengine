/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/rucksack/alignment.hpp>
#include <sge/rucksack/axis.hpp>
#include <sge/rucksack/axis_policy.hpp>
#include <sge/rucksack/axis_policy2.hpp>
#include <sge/rucksack/dim.hpp>
#include <sge/rucksack/make_axis_policy.hpp>
#include <sge/rucksack/minimum_size.hpp>
#include <sge/rucksack/preferred_size.hpp>
#include <sge/rucksack/scalar.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <sge/rucksack/widget/box.hpp>
#include <sge/rucksack/widget/optional_ref.hpp>
#include <sge/rucksack/widget/reference_alignment.hpp>
#include <sge/rucksack/widget/reference_alignment_container.hpp>
#include <sge/src/rucksack/extract_size.hpp>
#include <sge/src/rucksack/flip_axis.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/reference_wrapper_comparison.hpp>
#include <fcppt/algorithm/fold.hpp>
#include <fcppt/algorithm/remove_if.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/variant/apply_binary.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/variant/holds_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/pair.hpp>
#include <algorithm>
#include <iterator>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace
{

typedef
boost::mpl::map<
	boost::mpl::pair<
		boost::mpl::pair<
			sge::rucksack::minimum_size,
			sge::rucksack::minimum_size
		>,
		sge::rucksack::minimum_size
	>,
	boost::mpl::pair<
		boost::mpl::pair<
			sge::rucksack::minimum_size,
			sge::rucksack::preferred_size
		>,
		sge::rucksack::minimum_size
	>,
	// TODO: Generate symmetric cases automatically
	boost::mpl::pair<
		boost::mpl::pair<
			sge::rucksack::preferred_size,
			sge::rucksack::minimum_size
		>,
		sge::rucksack::minimum_size
	>,
	boost::mpl::pair<
		boost::mpl::pair<
			sge::rucksack::preferred_size,
			sge::rucksack::preferred_size
		>,
		sge::rucksack::preferred_size
	>
>
policy_map;

struct major_combiner
{
	typedef
	sge::rucksack::axis_policy
	result_type;

	template<
		typename P1,
		typename P2
	>
	result_type
	operator()(
		P1 const _p1,
		P2 const _p2
	) const
	{
		return
			typename
			boost::mpl::at<
				policy_map,
				boost::mpl::pair<
					P1,
					P2
				>
			>::type{
				_p1.get()
				+
				_p2.get()
			};
	}
};

struct minor_combiner
{
	typedef
	sge::rucksack::axis_policy
	result_type;

	template<
		typename P1,
		typename P2
	>
	result_type
	operator()(
		P1 const _p1,
		P2 const _p2
	) const
	{
		return
			typename
			boost::mpl::at<
				policy_map,
				boost::mpl::pair<
					P1,
					P2
				>
			>::type{
				std::max(
					_p1.get(),
					_p2.get()
				)
			};
	}
};

}

sge::rucksack::widget::box::box(
	sge::rucksack::axis const _axis
)
:
	sge::rucksack::widget::base(),
	children_(),
	axis_{
		_axis
	},
	position_(
		sge::rucksack::vector::null()
	),
	size_(
		sge::rucksack::dim::null()
	)
{
}

sge::rucksack::widget::box::box(
	sge::rucksack::axis const _axis,
	sge::rucksack::widget::reference_alignment_container const &_children
)
:
	sge::rucksack::widget::box(
		_axis
	)
{
	for(
		sge::rucksack::widget::reference_alignment const &element
		:
		_children
	)
		this->push_back_child(
			element.reference().get(),
			element.alignment()
		);
}

void
sge::rucksack::widget::box::size(
	sge::rucksack::dim const &_size
)
{
	size_ =
		_size;
}

void
sge::rucksack::widget::box::position(
	sge::rucksack::vector const &_position
)
{
	position_ =
		_position;
}

sge::rucksack::dim const
sge::rucksack::widget::box::size() const
{
	return
		size_;
}

sge::rucksack::vector const
sge::rucksack::widget::box::position() const
{
	return
		position_;
}

sge::rucksack::axis_policy2 const
sge::rucksack::widget::box::axis_policy() const
{
	// major (Min x, Min y) -> Min x + y
	// major (Min x, Opt y) -> Min x + y
	// major (Opt x, Opt y) -> Opt x + y
	//
	// minor (Min x, Min y) -> Min (max x + y)
	// minor (Min x, Opt y) -> Min (max x + y)
	// minor (Opt x, Opt y) -> Opt (max x + y)

	return
		fcppt::algorithm::fold(
			children_,
			sge::rucksack::make_axis_policy(
				[](
					sge::rucksack::axis
				)
				{
					return
						sge::rucksack::axis_policy{
							sge::rucksack::preferred_size{
								0
							}
						};
				}
			),
			[
				this
			](
				sge::rucksack::widget::box::child_list::value_type const &_pair,
				sge::rucksack::axis_policy2 const _prev
			)
			{
				sge::rucksack::axis_policy const major{
					fcppt::variant::apply_binary(
						major_combiner(),
						_pair.first.get().axis_policy()[
							this->major_axis()
						],
						_prev[
							this->major_axis()
						]
					)
				};

				sge::rucksack::axis_policy const minor{
					fcppt::variant::apply_binary(
						minor_combiner(),
						_pair.first.get().axis_policy()[
							this->minor_axis()
						],
						_prev[
							this->minor_axis()
						]
					)
				};

				return
					sge::rucksack::make_axis_policy(
						[
							major,
							minor,
							this
						](
							sge::rucksack::axis const _axis
						)
						{
							return
								_axis
								==
								axis_
								?
									major
								:
									minor
								;
						}
					);
			}
		);
}

void
sge::rucksack::widget::box::relayout()
{
	if(
		children_.empty()
	)
		return;

	FCPPT_MAKE_STRONG_TYPEDEF(
		sge::rucksack::scalar,
		remaining_size
	);

	FCPPT_MAKE_STRONG_TYPEDEF(
		bool,
		all_preferred_size
	);

	FCPPT_MAKE_STRONG_TYPEDEF(
		sge::rucksack::scalar,
		minimum_size_count
	);

	class info
	{
	public:
		info(
			remaining_size const _remaining_size,
			all_preferred_size const _all_preferred_size,
			minimum_size_count const _minimum_size_count
		)
		:
			remaining_size_{
				_remaining_size
			},
			all_preferred_size_{
				_all_preferred_size
			},
			minimum_size_count_{
				_minimum_size_count
			}
		{
		}

		sge::rucksack::scalar
		remaining() const
		{
			return
				remaining_size_.get();
		}

		bool
		all_preferred() const
		{
			return
				all_preferred_size_.get();
		}

		minimum_size_count
		minimum_sizes() const
		{
			return
				minimum_size_count_;
		}
	private:
		remaining_size remaining_size_;

		all_preferred_size all_preferred_size_;

		minimum_size_count minimum_size_count_;
	};

	// Collect three values:
	// - The remaining size which is the box's size minus all the child sizes,
	// - If all children have a preferred size,
	// - How many children can expand.
	info const infos{
		fcppt::algorithm::fold(
			children_,
			info(
				remaining_size{
					this->size(
						this->major_axis()
					)
				},
				all_preferred_size{
					true
				},
				minimum_size_count(
					0
				)
			),
			[
				this
			](
				child_pair const &_child,
				info const &_info
			)
			{
				sge::rucksack::axis_policy const policy{
					_child.first.get().axis_policy()[
						this->major_axis()
					]
				};

				return
					info(
						remaining_size{
							_info.remaining()
							-
							sge::rucksack::extract_size(
								policy
							)
						},
						all_preferred_size{
							_info.all_preferred()
							&&
							fcppt::variant::holds_type<
								sge::rucksack::preferred_size
							>(
								policy
							)
						},
						_info.minimum_sizes()
						+
						minimum_size_count{
							fcppt::variant::holds_type<
								sge::rucksack::minimum_size
							>(
								policy
							)
							?
								1
							:
								0
						}
					);
			}
		)
	};

	// If all children have a preferred size, we have to insert holes
	// between them.
	sge::rucksack::scalar const hole_size{
		infos.all_preferred()
		?
			std::max(
				fcppt::literal<
					sge::rucksack::scalar
				>(
					0
				),
				infos.remaining()
			)
			/
			fcppt::cast::size<
				sge::rucksack::scalar
			>(
				fcppt::cast::to_signed(
					children_.size()
					+
					1u
				)
			)
		:
			fcppt::literal<
				sge::rucksack::scalar
			>(
				0
			)
	};

	// If at least one child is expanding, we distribute the remaining size
	// uniformly among all expanding children.
	sge::rucksack::scalar const extra_size{
		std::max(
			fcppt::literal<
				sge::rucksack::scalar
			>(
				0
			),
			infos.minimum_sizes().get() != 0
			?
				infos.remaining()
				/
				infos.minimum_sizes().get()
			:
				fcppt::literal<
					sge::rucksack::scalar
				>(
					0
				)
		)
	};

	sge::rucksack::scalar current_major_position{
		this->position(
			this->major_axis()
		)
		+
		hole_size
	};

	for(
		auto const &widget_pair
		:
		children_
	)
	{
		class major_size_visitor
		{
			FCPPT_NONASSIGNABLE(
				major_size_visitor
			);
		public:
			explicit
			major_size_visitor(
				sge::rucksack::scalar const _extra_size
			)
			:
				extra_size_{
					_extra_size
				}
			{
			}

			typedef
			sge::rucksack::scalar
			result_type;

			result_type
			operator()(
				sge::rucksack::minimum_size const _min
			) const
			{
				return
					_min.get()
					+
					extra_size_;
			}

			result_type
			operator()(
				sge::rucksack::preferred_size const _pref
			) const
			{
				return
					_pref.get();
			}
		private:
			sge::rucksack::scalar const extra_size_;
		};

		class minor_size_visitor
		{
			FCPPT_NONASSIGNABLE(
				minor_size_visitor
			);
		public:
			explicit
			minor_size_visitor(
				sge::rucksack::scalar const _minor_size
			)
			:
				minor_size_{
					_minor_size
				}
			{
			}

			typedef
			sge::rucksack::scalar
			result_type;

			result_type
			operator()(
				sge::rucksack::minimum_size const _min
			) const
			{
				return
					std::max(
						_min.get(),
						minor_size_
					);
			}

			result_type
			operator()(
				sge::rucksack::preferred_size const _pref
			) const
			{
				return
					_pref.get();
			}
		private:
			sge::rucksack::scalar const minor_size_;
		};

		sge::rucksack::widget::base &widget(
			widget_pair.first.get()
		);

		widget.size(
			this->major_axis(),
			fcppt::variant::apply_unary(
				major_size_visitor(
					extra_size
				),
				widget.axis_policy()[
					this->major_axis()
				]
			)
		);

		widget.size(
			this->minor_axis(),
			fcppt::variant::apply_unary(
				minor_size_visitor{
					this->size(
						this->minor_axis()
					)
				},
				widget.axis_policy()[
					this->minor_axis()
				]
			)
		);

		widget.position(
			this->major_axis(),
			current_major_position
		);

		auto const make_minor_position(
			[
				&widget,
				this
			](
				sge::rucksack::alignment const _alignment
			)
			{
				switch(
					_alignment
				)
				{
				case sge::rucksack::alignment::left_or_top:
					return
						this->position(
							this->minor_axis()
						);
				case sge::rucksack::alignment::center:
					return
						this->position(
							this->minor_axis()
						)
						+
						(
							this->size(
								this->minor_axis()
							)
							-
							widget.size(
								this->minor_axis()
							)
						)
						/
						2;
				case sge::rucksack::alignment::right_or_bottom:
					return
						this->position(
							this->minor_axis()
						)
						+
						this->size(
							this->minor_axis()
						)
						-
						widget.size(
							this->minor_axis()
						);
				}

				FCPPT_ASSERT_UNREACHABLE;
			}
		);

		widget.position(
			this->minor_axis(),
			make_minor_position(
				widget_pair.second
			)
		);

		widget.relayout();

		current_major_position +=
			hole_size
			+
			widget.size(
				this->major_axis()
			);
	}
}

void
sge::rucksack::widget::box::push_back_child(
	sge::rucksack::widget::base &_new_child,
	sge::rucksack::alignment const _alignment
)
{
	this->insert_child(
		children_.end(),
		_new_child,
		_alignment
	);
}

void
sge::rucksack::widget::box::push_front_child(
	sge::rucksack::widget::base &_new_child,
	sge::rucksack::alignment const _alignment
)
{
	this->insert_child(
		children_.begin(),
		_new_child,
		_alignment
	);
}

void
sge::rucksack::widget::box::pop_back_child()
{
	this->erase_child(
		std::prev(
			children_.end()
		)
	);
}

void
sge::rucksack::widget::box::pop_front_child()
{
	this->erase_child(
		children_.begin()
	);
}

void
sge::rucksack::widget::box::clear()
{
	for(
		auto it(
			children_.begin()
		);
		it != children_.end();
		it =
			this->erase_child(
				it
			)
	)
		;
}

sge::rucksack::widget::box::iterator
sge::rucksack::widget::box::child_position(
	size_type const _pos
)
{
	return
		std::next(
			children_.begin(),
			fcppt::cast::to_signed(
				_pos
			)
		);
}

sge::rucksack::widget::box::size_type
sge::rucksack::widget::box::children_size() const
{
	return
		children_.size();
}

void
sge::rucksack::widget::box::replace_children(
	iterator const _pos,
	sge::rucksack::widget::base &_widget,
	sge::rucksack::alignment const _alignment
)
{
	this->insert_child(
		this->erase_child(
			_pos
		),
		_widget,
		_alignment
	);
}

sge::rucksack::widget::box::~box()
{
	for(
		auto &child
		:
		children_
	)
		child.first.get().parent(
			sge::rucksack::widget::optional_ref()
		);
}

void
sge::rucksack::widget::box::insert_child(
	iterator const _pos,
	sge::rucksack::widget::base &_widget,
	sge::rucksack::alignment const _alignment
)
{
	children_.insert(
		_pos,
		std::make_pair(
			fcppt::make_ref(
				_widget
			),
			_alignment
		)
	);

	_widget.parent(
		sge::rucksack::widget::optional_ref(
			*this
		)
	);
}

sge::rucksack::widget::box::iterator
sge::rucksack::widget::box::erase_child(
	iterator const _pos
)
{
	_pos->first.get().parent(
		sge::rucksack::widget::optional_ref()
	);

	return
		children_.erase(
			_pos
		);
}

sge::rucksack::axis
sge::rucksack::widget::box::major_axis() const
{
	return
		axis_;
}

sge::rucksack::axis
sge::rucksack::widget::box::minor_axis() const
{
	return
		sge::rucksack::flip_axis(
			axis_
		);
}

void
sge::rucksack::widget::box::child_destroyed(
	sge::rucksack::widget::base &_child
)
{
	FCPPT_ASSERT_ERROR(
		fcppt::algorithm::remove_if(
			children_,
			[
				&_child
			](
				child_pair const &_pair
			)
			{
				return
					_pair.first
					==
					fcppt::make_ref(
						_child
					);
			}
		)
	);
}
