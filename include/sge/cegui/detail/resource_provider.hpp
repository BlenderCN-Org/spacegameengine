#ifndef SGE_CEGUI_DETAIL_RESOURCE_PROVIDER_HPP_INCLUDED
#define SGE_CEGUI_DETAIL_RESOURCE_PROVIDER_HPP_INCLUDED

#include <sge/charconv/system_ptr.hpp>
#include <CEGUI/CEGUIResourceProvider.h>
#include <fcppt/noncopyable.hpp>
#include <fcppt/filesystem/path.hpp>

namespace sge
{
namespace cegui
{
namespace detail
{
class resource_provider
:
	public CEGUI::ResourceProvider
{
FCPPT_NONCOPYABLE(
	resource_provider);
public:
	explicit
	resource_provider(
		fcppt::filesystem::path const &,
		sge::charconv::system_ptr);

	void 
	loadRawDataContainer(
		CEGUI::String const &filename, 
		CEGUI::RawDataContainer &output, 
		CEGUI::String const &resourceGroup);

	void 
	unloadRawDataContainer(
		CEGUI::RawDataContainer&);

	size_t 
	getResourceGroupFileNames(
		std::vector<CEGUI::String>& out_vec,
		CEGUI::String const &file_pattern,
		CEGUI::String const &resource_group);

	fcppt::filesystem::path const
	to_absolute_path(
		CEGUI::String const &filename, 
		CEGUI::String const &resourceGroup);

	~resource_provider();
private:
	fcppt::filesystem::path const prefix_;
	sge::charconv::system_ptr charconv_system_;
};
}
}
}

#endif
