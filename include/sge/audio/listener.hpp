#ifndef SGE_AUDIO_LISTENER_HPP_INCLUDED
#define SGE_AUDIO_LISTENER_HPP_INCLUDED

#include "types.hpp"
#include "../export.hpp"
#include <boost/noncopyable.hpp>

namespace sge
{
namespace audio
{
class SGE_CLASS_SYMBOL listener : boost::noncopyable
{
	public:
	virtual point const pos() const = 0;
	virtual void pos(point const &) = 0;
	virtual point const vel() const = 0;
	virtual void vel(point const &) = 0;
	virtual angle const direction() const = 0;
	virtual void direction(angle const &) = 0;
	SGE_SYMBOL virtual ~listener();
};
}
}

#endif
