#pragma once

#include "GLee.h"
//#include <Windows.h>
//#include <gl/gl.h>

#include <string>
using namespace std;

#include <al.h>
#include <al/alut.h>
#include "Singleton.h"
#include "SoundCache.h" // sound sample cache
#include "MoveList.h"	// for MoveEvent
#include "Shared.h"		// for GameEvent & MenuEvent

// all the possible sound events in the game
struct SoundEvent
{
	SoundEvent(int _et, SampleID _sid): EventType(_et), OpenALSampleID(_sid) { };

	int EventType;
	SampleID OpenALSampleID;
};

// sokoban sound cache manager
class SokobanSoundManager : public Singleton<SokobanSoundManager>
{
public:
	SokobanSoundManager(void);
	~SokobanSoundManager(void);

	// Start the sound sub-system
	void Setup(void);
	// Stop the sound sub-system
	void Destroy(void);

public:
	// Load a sample into the cache
	SampleID CacheSampleFromFile(MoveEvent EventType, string FileName);
	SampleID CacheSampleFromFile(GameEvent EventType, string FileName);
	SampleID CacheSampleFromFile(MenuEvent EventType, string FileName);

	// play a sample from a sound id
	void PlaySample(SampleID _SampleID);
	void PlaySample(MoveEvent EventType);
	void PlaySample(GameEvent EventType);
	void PlaySample(MenuEvent EventType);

	// update - check if there are sources that can be released
	void Update(void);

private:
	bool m_bIsSetup;

	// Check if the audio sound system has started
	bool IsSetup(void)
	{
		return m_bIsSetup;
	}

	// default sound id, applied to all slots as default,
	// then replaced as sounds are loaded. This ensures that
	// there are no missing sound when an event is fired
	SampleID m_DefaultSoundID;

	// the sound event lists
	vector<SoundEvent> m_MoveEventSounds;
	vector<SoundEvent> m_GameEventSounds;
	vector<SoundEvent> m_MenuEventSounds;

	// active sounds
	vector<ALuint> m_ActiveSounds;

	// source
	// TODO convert this into an rolling buffer of 10 sources so sounds dont cut off
	ALuint source;

	// sound cache
	SoundCache m_SoundCache;

	// Cache a sample
	SampleID _CacheSampleFromFile(string FileName);
};
