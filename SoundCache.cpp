#include "SoundCache.h"

SoundCache::SoundCache(void)
{
}

SoundCache::~SoundCache(void)
{
}

// Add a new sample into the cache
// Note: Check return value, if its AL_NONE then sample has not been cached
SampleID SoundCache::LoadSample(string FileName)
{
	// check for file in loaded sounds list
	vector<SoundCacheSample>::iterator ii;
	for(ii=m_SoundCache.begin(); ii!=m_SoundCache.end(); ii++)
	{
		// check if sample matches
		if ( ii->FileName == FileName )
		{
			// found: +1 to its references, return its OpenALSoundID
			ii->References++;

			return ii->OpenALSampleID;
		}
	}

	// not found:
	SoundCacheSample NewSample;

	// load sample in OpenAL
	NewSample.OpenALSampleID = _LoadSampleFromFile(FileName);

	// updates its references
	NewSample.References = 1;

	// set the filename
	NewSample.FileName = FileName;

	// add it to the cache list
	m_SoundCache.push_back(NewSample);

	// return its SampleID
	return NewSample.OpenALSampleID;
}


// Load a sample from a file
SampleID SoundCache::_LoadSampleFromFile(string FileName)
{
	// Load the sound into OpenAL
	//////////////////////////////////////////////////////////////////////////
	ALuint buffer;
	ALenum error;

	// Create an AL buffer from the given sound file
	buffer = alutCreateBufferFromFile (FileName.c_str());
	
	if (buffer == AL_NONE)
	{
		error = alutGetError ();
		fprintf (stderr, "Error loading file: '%s'\n", alutGetErrorString (error));
		//alutExit ();
		//exit (EXIT_FAILURE);

		return AL_NONE;
	}

	// Return the reference to the caller
	//////////////////////////////////////////////////////////////////////////
	return buffer;

}