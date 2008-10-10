#include "../source.hpp"
#include "../error.hpp"
#include "../log.hpp"
#include <sge/audio/exception.hpp>

sge::openal::source::source()
	: status_(audio::sound_status::stopped),
	  positional_(false),
		pos_(sge::su(0),sge::su(0),sge::su(0)),
		vel_(sge::su(0),sge::su(0),sge::su(0)),
		attenuation_(sge::su(1))
{
	alGenSources(static_cast<ALsizei>(1),&source_); SGE_OPENAL_ERROR_CHECK;

	// we just impose our default values 
	positional(positional_);
	pos(pos_);
	vel(vel_);
	attenuation(attenuation_);
	rolloff(sge::su(1));
}

sge::openal::source::source(ALuint const buffer)
	: status_(audio::sound_status::stopped),
	  positional_(false),
		pos_(sge::su(0),sge::su(0),sge::su(0)),
		vel_(sge::su(0),sge::su(0),sge::su(0)),
		attenuation_(sge::su(1))
{
	SGE_LOG_DEBUG(log(),log::_1 << "creating a source bound to a buffer");
	alGenSources(static_cast<ALsizei>(1),&source_); SGE_OPENAL_ERROR_CHECK;
	alSourcei(alsource(),AL_BUFFER,buffer); SGE_OPENAL_ERROR_CHECK;

	// we just impose our default values 
	positional(positional_);
	pos(pos_);
	vel(vel_);
	attenuation(attenuation_);
	rolloff(sge::su(1));
}

void sge::openal::source::sync() const
{
	ALint play;
	alGetSourcei(alsource(), AL_SOURCE_STATE, &play); SGE_OPENAL_ERROR_CHECK;
	switch (play)
	{
		case AL_STOPPED:
		case AL_INITIAL:
			status_ = audio::sound_status::stopped;
		break;
		case AL_PAUSED:
			status_ = audio::sound_status::paused;
		break;
		case AL_PLAYING:
			status_ = audio::sound_status::playing;
		break;
		default:
			throw audio::exception(SGE_TEXT("OpenAL error: invalid playing status"));
		break;
	}
}

void sge::openal::source::play(audio::play_mode::type const _play_mode)
{
	sync();
	play_mode(_play_mode);
	do_play();

	if (status() != audio::sound_status::playing)
	{
		status_ = audio::sound_status::playing;
		alSourcePlay(alsource()); SGE_OPENAL_ERROR_CHECK;
	}
}

void sge::openal::source::toggle_pause()
{
	sync();

	switch (status_)
	{
		case audio::sound_status::stopped:
			return;
		case audio::sound_status::paused:
			play_mode(play_mode_);
			alSourcePlay(alsource()); SGE_OPENAL_ERROR_CHECK;
		break;
		case audio::sound_status::playing:
			alSourcePause(alsource()); SGE_OPENAL_ERROR_CHECK;
		break;
	}
}

sge::audio::sound_status::type sge::openal::source::status() const
{
	sync();
	return status_;
}

void sge::openal::source::stop()
{
	sync();

	if (status_ == audio::sound_status::stopped)
		return;

	alSourceStop(alsource()); SGE_OPENAL_ERROR_CHECK;
	status_ = audio::sound_status::stopped;
}

void sge::openal::source::attenuation(audio::unit const n)
{
	attenuation_ = n;
	alSourcef(alsource(),AL_GAIN,static_cast<ALfloat>(attenuation_)); SGE_OPENAL_ERROR_CHECK;
}

void sge::openal::source::rolloff(audio::unit const n)
{
	rolloff_ = n;
	alSourcef(alsource(),AL_ROLLOFF_FACTOR,static_cast<ALfloat>(n)); SGE_OPENAL_ERROR_CHECK;
}

void sge::openal::source::pos(audio::point const &n)
{
	pos_ = n;

	ALfloat const vec[3] = 
		{ 
			static_cast<ALfloat>(n.x()),
			static_cast<ALfloat>(n.y()),
			static_cast<ALfloat>(n.z()) 
		};

	alSourcefv(alsource(),AL_POSITION,vec); SGE_OPENAL_ERROR_CHECK;
}

void sge::openal::source::vel(audio::point const &n)
{
	vel_ = n;

	ALfloat const vec[3] = 
		{ 
			static_cast<ALfloat>(n.x()),
			static_cast<ALfloat>(n.y()),
			static_cast<ALfloat>(n.z()) 
		};

	alSourcefv(alsource(),AL_VELOCITY,vec); SGE_OPENAL_ERROR_CHECK;
}

void sge::openal::source::positional(bool const n)
{
	if (n == positional_)
		return;

	positional_ = n;

	if (n)
	{
		alSourcef(alsource(),AL_ROLLOFF_FACTOR,static_cast<ALfloat>(1)); SGE_OPENAL_ERROR_CHECK;
		alSourcei(alsource(),AL_SOURCE_RELATIVE, AL_FALSE); SGE_OPENAL_ERROR_CHECK;
	}
	else
	{
		alSourcef(alsource(),AL_ROLLOFF_FACTOR,static_cast<ALfloat>(0)); SGE_OPENAL_ERROR_CHECK;
		// make source relative to listener and set it's position to (0,0,0), so directly on the listener
		alSourcei(alsource(),AL_SOURCE_RELATIVE, AL_TRUE); SGE_OPENAL_ERROR_CHECK;
		pos(
			audio::point(static_cast<audio::unit>(0),
			             static_cast<audio::unit>(0),
			             static_cast<audio::unit>(0)));
	}
}

void sge::openal::source::play_mode(audio::play_mode::type const pm)
{
	play_mode_ = pm;
}

sge::openal::source::~source()
{
	alDeleteSources(static_cast<ALsizei>(1),&source_); SGE_OPENAL_ERROR_CHECK;
}
