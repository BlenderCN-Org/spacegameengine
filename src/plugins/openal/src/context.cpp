#include "../context.hpp"
#include "../device.hpp"
#include "../error.hpp"
#include "../openal.hpp"
#include "../log.hpp"
#include <sge/audio/exception.hpp>
#include <sge/iostream.hpp>
#include <sge/assert.hpp>
#include <boost/foreach.hpp>
#include <vector>

sge::openal::context::context(
	device &device_,
	attribute_container const &attributes)
	: device_(device_)
{
	std::vector<ALCint> al_attributes;
	BOOST_FOREACH(attribute_container::value_type const &v,attributes)
	{
		al_attributes.push_back(v.first);
		al_attributes.push_back(v.second);
	}
	// attribute array has to be null terminated
	al_attributes.push_back(static_cast<ALCint>(0));
	al_attributes.push_back(static_cast<ALCint>(0));

	SGE_LOG_DEBUG(log(),log::_1 << SGE_TEXT("creating audio context"))

	context_ = alcCreateContext(device_.aldevice(),&(al_attributes[0]));

	if (!context_)
	{
		SGE_ALC_ERROR_CHECK(device_.aldevice());
		SGE_OPENAL_ERROR_CHECK;
	}

	SGE_ASSERT(context_);
	SGE_LOG_DEBUG(log(),log::_1 << SGE_TEXT("created audio context"))
}

void sge::openal::context::make_current()
{
	SGE_LOG_DEBUG(log(),
		log::_1 << SGE_TEXT("making audio context the current context"));

	alcMakeContextCurrent(context_);

	SGE_ALC_ERROR_CHECK(device_.aldevice());
	SGE_OPENAL_ERROR_CHECK;
	SGE_LOG_DEBUG(log(),
		log::_1 << SGE_TEXT("made audio context the current context"));
}

sge::openal::context::~context()
{
	ALCcontext const * const current = alcGetCurrentContext();
	SGE_ALC_ERROR_CHECK(device_.aldevice());
	SGE_OPENAL_ERROR_CHECK;
	if (current == context_)
	{
		SGE_LOG_DEBUG(log(),
			log::_1 << SGE_TEXT("context is the current context, so resetting current context"));
		alcMakeContextCurrent(0); 
		SGE_ALC_ERROR_CHECK(device_.aldevice());
		// at this point: DO NOT CHECK FOR OPENAL ERRORS. IT'S ILLEGAL
		//SGE_OPENAL_ERROR_CHECK;
	}

	alcDestroyContext(context_); 
	SGE_ALC_ERROR_CHECK(device_.aldevice());
}
