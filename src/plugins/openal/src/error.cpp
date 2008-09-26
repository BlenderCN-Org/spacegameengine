#include "../error.hpp"
#include "../openal.hpp"
#include <sge/text.hpp>
#include <sge/format.hpp>
#include <sge/string.hpp>
#include <sge/audio/exception.hpp>

namespace
{
sge::string const alc_error_string(ALCenum const error)
{
	switch (error)
	{
		case ALC_NO_ERROR:
			return SGE_TEXT("no error in openal (maybe somewhere else)");
		case ALC_INVALID_DEVICE:
			return SGE_TEXT("the device handle specifies an inaccessible driver/server");
		case ALC_INVALID_CONTEXT:
			return SGE_TEXT("the context argument does not name a valid context");
		case ALC_INVALID_ENUM:
			return SGE_TEXT("a token used is not valid, or not acceptable");
		case ALC_INVALID_VALUE:
			return SGE_TEXT("a value (e.g. attribute) is not valid, or not applicable");
		case ALC_OUT_OF_MEMORY:
			return SGE_TEXT("unable to allocate memory");
	}

	if (!std::uncaught_exception())
		throw sge::audio::exception(
			sge::str(
				sge::format(SGE_TEXT("invalid alc error code: %1%")) % error));
}

sge::string const error_string(ALenum const error)
{
	switch (error)
	{
		case AL_NO_ERROR:
			return SGE_TEXT("no error in openal (maybe somewhere else)");
		case AL_INVALID_NAME:
			return SGE_TEXT("invalid name parameter");
		case AL_INVALID_ENUM:
			return SGE_TEXT("invalid parameter");
		case AL_INVALID_VALUE:
			return SGE_TEXT("invalid enum parameter value");
		case AL_INVALID_OPERATION:
			return SGE_TEXT("illegal call");
		case AL_OUT_OF_MEMORY:
			return SGE_TEXT("unable to allocate memory");
	}

	if (!std::uncaught_exception())
		throw sge::audio::exception(
			sge::str(sge::format(SGE_TEXT("invalid openal error code: %1%")) % error));
}
}

void sge::openal::error_check(string const &file,string const &line)
{
	ALenum const error = alGetError();
	if (error != AL_NO_ERROR)
		if (!std::uncaught_exception())
			throw audio::exception(str(format(SGE_TEXT("openal error %1%:%2%: %3%")) % file % line % error_string(error)));
}

void sge::openal::alc_error_check(ALCdevice * const device,string const &file,string const &line)
{
	ALCenum const error = alcGetError(device);

	if (error != ALC_NO_ERROR)
		if (!std::uncaught_exception())
			throw audio::exception(str(format(SGE_TEXT("alc error %1%:%2%: %3%")) % file % line % alc_error_string(error)));
}
