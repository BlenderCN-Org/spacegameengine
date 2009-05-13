#ifndef SGE_GUI_LAYOUTS_GRID_HPP_INCLUDED	
#define SGE_GUI_LAYOUTS_GRID_HPP_INCLUDED	

#include <sge/gui/layouts/base.hpp>
#include <sge/gui/widgets/fwd.hpp>
#include <sge/gui/export.hpp>
#include <sge/gui/dim.hpp>
#include <sge/gui/size_policy.hpp>
#include <sge/gui/unit.hpp>
#include <sge/container/field.hpp>
#include <sge/container/raw_vector.hpp>
#include <boost/multi_array.hpp>
#include <utility>
#include <vector>
#include <map>

namespace sge
{
namespace gui
{
namespace layouts
{
class SGE_CLASS_SYMBOL grid : public base
{
public:
	SGE_GUI_SYMBOL void compile(invalidation::type const &);
	SGE_GUI_SYMBOL void compile_static();
	SGE_GUI_SYMBOL dim const optimal_size() const;
private:
	class cache;
	friend class cache;
	typedef scoped_ptr<cache> cache_ptr;
	cache_ptr cache_;


	typedef container::field<
		widgets::base*,
		container::raw_vector
		> child_container;
	typedef container::field<
		widgets::base const *,
		container::raw_vector
		> const_child_container;
	typedef child_container::size_type size_type;
	typedef std::map<
		widgets::base*,
		dim
		> sizes_map;
	typedef container::field<
		size_policy,
		std::vector
		> policy_cache_type;
	typedef container::field<
		dim,
		std::vector
		> rolumn_cache_type;

	sizes_map sizes_;
	policy_cache_type policy_cache_;
	rolumn_cache_type rolumn_cache_;
	const_child_container children_;

	dim const dimensions() const;
	const_child_container const children() const;
	void adapt_outer(
		dim const &,
		dim const &,
		axis_type);
	void shrink(
		dim const &,
		dim const &,
		axis_type);
	void expand(
		dim const &,
		dim const &,
		axis_type);
	void adapt(
		dim const &,
		dim const &,
		axis_policy::type,
		axis_type);
	void update_rolumn(
		axis_type,
		policy_cache_type::size_type,
		axis_policy::type,
		unit);
	unsigned count_flags(
		axis_policy::type,
		axis_type) const;
	void update_cache();
	void update_policy_cache();
	void update_size_cache();
	void update_rolumn_cache();
	void update_widgets();
	void update_widget(
		widgets::base &,
		point const &,
		dim const &);
};
}
}
}

#endif
