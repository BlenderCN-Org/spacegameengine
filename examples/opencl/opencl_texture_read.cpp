/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/config/media_path.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/save_from_view.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/to_const.hpp>
#include <sge/media/all_extensions.hpp>
#include <sge/opencl/clinclude.hpp>
#include <sge/opencl/dim2.hpp>
#include <sge/opencl/command_queue/enqueue_kernel.hpp>
#include <sge/opencl/command_queue/map_flags.hpp>
#include <sge/opencl/command_queue/scoped.hpp>
#include <sge/opencl/command_queue/scoped_planar_mapping.hpp>
#include <sge/opencl/event/object.hpp>
#include <sge/opencl/kernel/object.hpp>
#include <sge/opencl/memory_object/flags_field.hpp>
#include <sge/opencl/memory_object/image/planar.hpp>
#include <sge/opencl/program/build_parameters.hpp>
#include <sge/opencl/program/file_to_source_string_sequence.hpp>
#include <sge/opencl/program/object.hpp>
#include <sge/opencl/single_device_system/object.hpp>
#include <sge/opencl/single_device_system/parameters.hpp>
#include <sge/systems/image2d.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/make_list.hpp>
#include <sge/systems/with_image2d.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <cstddef>
#include <iostream>
#include <ostream>
#include <fcppt/config/external_end.hpp>


int
main(
	int argc,
	char *argv[])
try
{
	// TODO: Use args
	if(argc == 1)
	{
		fcppt::io::cerr()
			<< FCPPT_TEXT("This program creates an image in OpenCL and writes it to a png file on disk.\n\n")
			<< FCPPT_TEXT("Usage: ")
			<< fcppt::from_std_string(argv[0])
			<< FCPPT_TEXT(" <png-image-file-name>\n");
		return EXIT_FAILURE;
	}

	fcppt::io::cout()
		<< FCPPT_TEXT("Creating systems object\n");

	sge::systems::instance<
		boost::mpl::vector1<
			sge::systems::with_image2d
		>
	> const sys(
		sge::systems::make_list
		(
			sge::systems::image2d(
				sge::media::all_extensions
			)
		)
	);

	fcppt::io::cout()
		<< FCPPT_TEXT("Done, creating opencl system\n");

	boost::filesystem::path const target_file_name(
		fcppt::from_std_string(
			argv[1]));

	// Mind the extra parens
	sge::opencl::single_device_system::object opencl_system(
		sys.log_context(),
		sge::opencl::single_device_system::parameters()
			.execution_mode(
				sge::opencl::command_queue::execution_mode::out_of_order));

	fcppt::io::cout()
		<< FCPPT_TEXT("Done, creating planar image\n");

	cl_image_format image_format;
	image_format.image_channel_order = CL_RGBA;
	image_format.image_channel_data_type = CL_UNORM_INT8;

	sge::opencl::dim2 image_size(
		512u,
		512u);

	sge::opencl::memory_object::image::planar image(
		opencl_system.context(),
		sge::opencl::memory_object::flags_field{
			sge::opencl::memory_object::flags::read,
			sge::opencl::memory_object::flags::write
		},
		image_format,
		image_size,
		sge::opencl::memory_object::image::planar_pitch(
			0u));

	fcppt::io::cout()
		<< FCPPT_TEXT("Done, creating program\n");

	sge::opencl::program::object main_program(
		sys.log_context(),
		opencl_system.context(),
		sge::opencl::program::file_to_source_string_sequence(
			sge::config::media_path() / FCPPT_TEXT("kernels") / FCPPT_TEXT("texture.cl")),
		sge::opencl::program::optional_build_parameters());

	fcppt::io::cout()
		<< FCPPT_TEXT("Program created, building the program...\n");

	main_program.build(
		sge::opencl::program::build_parameters());

	fcppt::io::cout()
		<< FCPPT_TEXT("Program built, now creating a kernel...\n");

	sge::opencl::kernel::object main_kernel(
		main_program,
		sge::opencl::kernel::name(
			"hello_kernel"));

	main_kernel.argument(
		sge::opencl::kernel::argument_index(
			0u),
		image);

	fcppt::io::cout()
		<< FCPPT_TEXT("Kernel created, executing it\n");

	sge::opencl::command_queue::scoped scoped_queue(
		opencl_system.command_queue());

	sge::opencl::event::sequence events;

	events.push_back(
		sge::opencl::command_queue::enqueue_kernel(
			opencl_system.command_queue(),
			main_kernel,
			sge::opencl::command_queue::global_dim2(
				image_size),
			sge::opencl::event::sequence()));

	fcppt::io::cout()
		<< FCPPT_TEXT("Done, now creating an image file from the image in memory...\n");

	sge::opencl::command_queue::scoped_planar_mapping scoped_image(
		opencl_system.command_queue(),
		image,
		sge::opencl::command_queue::map_flags::read,
		sge::opencl::memory_object::rect(
			fcppt::math::vector::null<
				sge::opencl::memory_object::rect::vector
			>(),
			image.size()
		),
		events
	);

	sge::image2d::save_from_view(
		sys.image_system(),
		sge::image2d::view::to_const(
			scoped_image.view()),
		target_file_name);

	opencl_system.update();
}
catch(
	fcppt::exception const &_error
)
{
	fcppt::io::cerr()
		<< _error.string()
		<< FCPPT_TEXT('\n');

	return EXIT_FAILURE;
}
catch(
	std::exception const &_error
)
{
	std::cerr
		<< _error.what()
		<< '\n';

	return EXIT_FAILURE;
}
