#pragma once
// loads samples into and out of the OpenAL cache
//////////////////////////////////////////////////////////////////////////
// TODO: presumes that sound system is enabled and working - implement a
//       way to make this more resiliant to errors!
// TODO: make singleton

#include <string>
#include <vector>
using namespace std;

#include <al/alut.h>

// clean name for a reference to a sound
typedef ALuint SampleID;

// simple structure to hold together information about a sound sample
struct SoundCacheSample
{
	SampleID OpenALSampleID;
	string FileName;
	unsigned int References;
};


class SoundCache
{
public:
	SoundCache(void);
	~SoundCache(void);

	// Load a new sample into the system
	SampleID LoadSample(string FileName);

private:
	vector<SoundCacheSample> m_SoundCache;

	// Load a sample from a file
	SampleID _LoadSampleFromFile(string FileName);
};
