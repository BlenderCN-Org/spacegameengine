#include <sge/gui/impl/renderer/scoped.hpp>
#include <sge/gui/renderer/base.hpp>
#include <sge/gui/renderer/base_unique_ptr.hpp>
#include <sge/gui/renderer/create_scoped.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <fcppt/make_unique_ptr_fcppt.hpp>
#include <fcppt/unique_ptr_to_base.hpp>


sge::gui::renderer::base_unique_ptr
sge::gui::renderer::create_scoped(
	sge::renderer::device::ffp &_renderer,
	sge::renderer::context::ffp &_context
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::gui::renderer::base
		>(
			fcppt::make_unique_ptr_fcppt<
				sge::gui::impl::renderer::scoped
			>(
				_renderer,
				_context
			)
		);
}
