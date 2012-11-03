#pragma once

#include "Singleton.h"
#include "LevelSet.h"
#include "EncodedLevel.h"

struct EpisodeInfo
{
	string EpisodeName;
	int NumberOfLevels;
};

class SokobanLevelManager : public Singleton<SokobanLevelManager>
{
	// 
	friend class Singleton<SokobanLevelManager>;

protected:
	SokobanLevelManager(void);
public:
	~SokobanLevelManager(void);

private:
	vector<LevelSet> m_Episodes;
	int m_CurrentEpisode;
	int m_CurrentLevel;

public:
	// Setup the level manager
	void Setup(void);

	// Get the first level in the game
	EncodedLevel GetNewGameLevel(void);

	// Get the next available level in this episode
	EncodedLevel GetNextLevel(void);
	// Get the previous level in this episode
	EncodedLevel GetPrevLevel(void);

	// Get the current level
	EncodedLevel GetCurrentLevel(void);


	// Get the first level in the next available episode
	EncodedLevel GetNextEpisode(void);
	// Get the first level in the previous episode
	EncodedLevel GetPrevEpisode(void);


	// Is the current level the last one in the episode?
	bool IsLastLevelInEpisode(void)
	{
		return ((m_CurrentLevel == m_Episodes[m_CurrentEpisode].m_Levels.size()) ? true : false);
	}

	// Is this the last episode in the game?
	bool IsLastLevelInGame(void)
	{
		if ((m_CurrentEpisode == m_Episodes.size())
			&& (m_CurrentLevel == m_Episodes[m_CurrentEpisode].m_Levels.size()))
		{
			return true;
		}

		return false;
	}

	// Get a unique string that will identify the level
	string GetLevelIDString(void);

	// Get a list of all the names of the episodes available
	vector<EpisodeInfo> GetEpisodeInfo(void);

	// Get the total number of active episodes
	int GetActiveEpisodeTotal(void);

	// Change the current episode
	void SetActiveEpisode(int NewActiveEpisode);
};