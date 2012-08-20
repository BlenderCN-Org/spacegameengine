#ifndef SGE_SCENIC_RENDER_CONTEXT_BASE_UNIQUE_PTR_HPP_INCLUDED
#define SGE_SCENIC_RENDER_CONTEXT_BASE_UNIQUE_PTR_HPP_INCLUDED

#include <sge/scenic/render_context/base_fwd.hpp>
#include <fcppt/unique_ptr.hpp>

namespace sge
{
namespace scenic
{
namespace render_context
{
typedef
fcppt::unique_ptr
<
	sge::scenic::render_context::base
>
base_unique_ptr;
}
}
}

#endif