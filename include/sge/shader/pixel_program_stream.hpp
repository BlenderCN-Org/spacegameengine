#ifndef SGE_SHADER_PIXEL_PROGRAM_STREAM_HPP_INCLUDED
#define SGE_SHADER_PIXEL_PROGRAM_STREAM_HPP_INCLUDED

#include <fcppt/strong_typedef.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace shader
{
FCPPT_MAKE_STRONG_TYPEDEF(
	std::istream &,
	pixel_program_stream);
}
}

#endif
