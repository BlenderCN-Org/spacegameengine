#include "mpeg_file.hpp"
#include <sge/log/headers.hpp>
#include <sge/raw_vector_impl.hpp>
#include <sge/audio/exception.hpp>
#include <sge/iostream.hpp>
#include <algorithm>
#include <iterator>

namespace
{
template<typename T,typename U>
void append(T &t,U const &u)
{
	std::copy(u.begin(),u.end(),std::back_inserter(t));
}

template<typename S,typename T,typename U>
void move(S &container,T it,T const end,U dest)
{
	std::copy(it,end,dest);
	container.erase(it,end);
}
}

sge::mad::mpeg_file::mpeg_file(path const &p)
	: stdstream(p),
	  s(stdstream)
{
	if (!stdstream.is_open())
		throw audio::exception(SGE_TEXT("couldn't open file \"")+p.string()+SGE_TEXT("\""));

	frame &f = s.decode();

	sample_rate_ = f.sample_rate();

	SGE_LOG_INFO(
		log::global(),
		log::_1 << "mad: file info: \n" << f.info());

	append(buffered_,f.synthesize());
}

sge::mad::mpeg_file::sample_count sge::mad::mpeg_file::read(
	sample_count const samples,
	sample_container &dest)
{
	sample_count const samples_bytes = 
		static_cast<sample_count>(samples*bytes_per_sample());

	move(buffered_,buffered_.begin(),buffered_.end(),std::back_inserter(dest));

	while (dest.size() < samples_bytes)
		append(dest,s.decode().synthesize());
	
	move(dest,dest.begin()+samples_bytes,dest.end(),std::back_inserter(buffered_));

	return dest.size()/bytes_per_sample();
}

sge::mad::mpeg_file::sample_count sge::mad::mpeg_file::read_all(sample_container &dest)
{
	while (!s.eof())
		read(static_cast<sample_count>(1024),dest);
	return dest.size();
}

void sge::mad::mpeg_file::reset()
{

}
