#include "SokobanSoundManager.h"

SokobanSoundManager::SokobanSoundManager(void): m_bIsSetup(false)
{
}

SokobanSoundManager::~SokobanSoundManager(void)
{
}

// Start the sound sub-system
void SokobanSoundManager::Setup(void)
{
	// Initialise ALUT and eat any ALUT-specific command line flags
	if (!alutInit (NULL, NULL))
	{
		ALenum error = alutGetError ();
		fprintf (stderr, "%s\n", alutGetErrorString (error));
		// exit (EXIT_FAILURE);
		m_bIsSetup = false;
		return;
	}

	// Load the default sound
	//////////////////////////////////////////////////////////////////////////
	// NOTE: Cant use LoadSampleFromFile because if it fails it returns m_DefaultSoundID
	
	// Create an AL buffer from the given sound file
	m_DefaultSoundID = alutCreateBufferFromFile (".\\audio\\default.wav");
	if (m_DefaultSoundID == AL_NONE)
	{
		ALenum error = alutGetError ();
		fprintf (stderr, "Error loading file: '%s'\n", alutGetErrorString (error));
		alutExit ();
		// exit (EXIT_FAILURE);
		m_bIsSetup = false;
		return;
	}

	// Generate a single source
	alGenSources (1, &source);

	// Error check source generation
	ALenum error = alGetError ();
	if (error != ALUT_ERROR_NO_ERROR)
	{
		//	fprintf (stderr, "%s\n", alGetString (error));
		MessageBox (HWND_DESKTOP, alGetString(error), "Error 1", MB_OK | MB_ICONEXCLAMATION);
		alutExit ();
		exit (EXIT_FAILURE);
	}

	// toggle IsSetup
	m_bIsSetup = true;

	return;
}

// shut down the sound sub-system
void SokobanSoundManager::Destroy(void)
{

	// free sources
	alDeleteSources(1, &source);

	if (!alutExit ())
	{
		ALenum error = alutGetError ();
		fprintf (stderr, "%s\n", alutGetErrorString (error));
		exit (EXIT_FAILURE);
	}

	m_bIsSetup = false;
}


// Load a sample into the cache
SampleID SokobanSoundManager::_CacheSampleFromFile(string FileName)
{
	// error check
	if(!IsSetup()) return false;

	// Create an AL buffer from the given FileName
	ALuint buffer = m_SoundCache.LoadSample(FileName);

	// error check
	if (buffer == AL_NONE)
	{
		// error loading, no need to quit just use default sound
		return m_DefaultSoundID;
	}

	return buffer;
}

// Load a sample into the cache for a specific move event
SampleID SokobanSoundManager::CacheSampleFromFile(MoveEvent EventType, string FileName)
{
	// error check
	if(!IsSetup()) return false;

	// Create an AL buffer from the given sound file
	ALuint buffer = _CacheSampleFromFile(FileName);

	// Add it to the cache
	m_MoveEventSounds.push_back(SoundEvent(EventType.Type, buffer));

	// Return the reference to the caller
	return buffer;
}

// Load a sample into the cache for a specific game event
SampleID SokobanSoundManager::CacheSampleFromFile(GameEvent EventType, string FileName)
{
	// error check
	if(!IsSetup()) return false;

	// Create an AL buffer from the given sound file
	ALuint buffer = _CacheSampleFromFile(FileName);

	// Add it to the cache
	m_GameEventSounds.push_back(SoundEvent(EventType, buffer));

	// Return the reference to the caller
	return buffer;
}

// Load a sample into the cache for a specific menu event
SampleID SokobanSoundManager::CacheSampleFromFile(MenuEvent EventType, string FileName)
{
	// error check
	if(!IsSetup()) return false;

	// Create an AL buffer from the given sound file
	ALuint buffer = _CacheSampleFromFile(FileName);

	// Add it to the cache
	m_MenuEventSounds.push_back(SoundEvent(EventType, buffer));

	// Return the reference to the caller
	return buffer;
}

// play a sample from a sound id
void SokobanSoundManager::PlaySample(SampleID _SampleID)
{
	// error check
	if(!IsSetup()) return;

	ALenum error;

	// clear errors
	alGetError();

	// if the source is in use then the new sound takes priorty
	ALint status;
	alGetSourcei (source, AL_SOURCE_STATE, &status);
	if (status == AL_PLAYING)
	{
		// stop the current sound playing
		alSourceStop(source);
	}

	// attach the buffer to it and start playing.
	alSourcei (source, AL_BUFFER, _SampleID);

	// Normally nothing should go wrong above, but one never knows...
	error = alGetError ();
	if (error != ALUT_ERROR_NO_ERROR)
	{
		// fprintf (stderr, "%s\n", alGetString (error));
		MessageBox (HWND_DESKTOP, alGetString(error), "Error Attaching Buffer", MB_OK | MB_ICONEXCLAMATION);
		alutExit ();
		exit (EXIT_FAILURE);
	}

	alSourcePlay (source);
	// Normally nothing should go wrong above, but one never knows...
	error = alGetError ();
	if (error != ALUT_ERROR_NO_ERROR)
	{
		//	fprintf (stderr, "%s\n", alGetString (error));
		MessageBox (HWND_DESKTOP, alGetString(error), "Error Playing Buffer", MB_OK | MB_ICONEXCLAMATION);
		alutExit ();
		exit (EXIT_FAILURE);
	}

	// add to list of active sounds
	//m_ActiveSounds.push_back(source);

	return;
}

// play a sample from the MoveEvent cache (players actions)
void SokobanSoundManager::PlaySample(MoveEvent EventType)
{
	// look for it in the list
	vector<SoundEvent>::iterator ii;
	for(ii=m_MoveEventSounds.begin(); ii!=m_MoveEventSounds.end(); ii++)
	{
		// look for a matching level
		if ( ii->EventType == EventType.Type )
		{
			// play the sample
			PlaySample(ii->OpenALSampleID);

			return;
		}
	}

	// if its not found play default sample
	PlaySample(m_DefaultSoundID);

}

// play a sample from the game event cache (level completion, etc)
void SokobanSoundManager::PlaySample(GameEvent EventType)
{
	// look for it in the list
	vector<SoundEvent>::iterator ii;
	for(ii=m_GameEventSounds.begin(); ii!=m_GameEventSounds.end(); ii++)
	{
		// look for a matching level
		if ( ii->EventType == EventType )
		{
			// play the sample
			PlaySample(ii->OpenALSampleID);

			return;
		}
	}

	// if its not found play default sample
	PlaySample(m_DefaultSoundID);
}

// play a sample from the menu event cache (navigation through the menus)
void SokobanSoundManager::PlaySample(MenuEvent EventType)
{
	// look for it in the list
	vector<SoundEvent>::iterator ii;
	for(ii=m_MenuEventSounds.begin(); ii!=m_MenuEventSounds.end(); ii++)
	{
		// look for a matching level
		if ( ii->EventType == EventType )
		{
			// play the sample
			PlaySample(ii->OpenALSampleID);

			return;
		}
	}

	// if its not found play default sample
	PlaySample(m_DefaultSoundID);
}


// update - check if there are sources that can be released
void SokobanSoundManager::Update(void)
{
/*	vector<ALuint>::iterator ii;
	for(ii = m_ActiveSounds.begin(); ii <= m_ActiveSounds.end(); ii++)
	{
		ALint status;
		
		alGetSourcei ((*ii), AL_SOURCE_STATE, &status);

		if (status == AL_STOPPED)
		{
			// remove from active sounds list
			m_ActiveSounds.erase(ii);

			//m_ActiveSounds[ii];
		}
	}
*/
	return;
}