#include <Windows.h>
#include ".\sokobanlevelmanager.h"

SokobanLevelManager::SokobanLevelManager(void)
{
}

SokobanLevelManager::~SokobanLevelManager(void)
{
}

// Setup the level manager
void SokobanLevelManager::Setup(void)
{
	LevelSet NewSet;
	NewSet.LoadSLCFile(".\\levels\\original.slc");
	m_Episodes.push_back(NewSet);

	NewSet.LoadSLCFile(".\\levels\\Dimitri-Yorick.slc");
	m_Episodes.push_back(NewSet);

	NewSet.LoadSLCFile(".\\levels\\MicroCosmos.slc");
	m_Episodes.push_back(NewSet);

	m_CurrentEpisode = 0;
	m_CurrentLevel = 0;
}

// Get the first level in the game
EncodedLevel SokobanLevelManager::GetNewGameLevel(void)
{
	// reset iterators to first level / first episode
	// this is done by the menu system (URGH!)
	//m_CurrentEpisode = 0;
	//m_CurrentLevel = 0;

	// return the level
	return m_Episodes[m_CurrentEpisode].m_Levels[m_CurrentLevel];
}

// Get the next available level in this episode
EncodedLevel SokobanLevelManager::GetNextLevel(void)
{
	if (m_CurrentLevel < (m_Episodes[m_CurrentEpisode].m_Levels.size() - 1))
	{
		m_CurrentLevel++;
	}

	return m_Episodes[m_CurrentEpisode].m_Levels[m_CurrentLevel];
}

// Get the previous level in this episode
EncodedLevel SokobanLevelManager::GetPrevLevel(void)
{
	if (m_CurrentLevel != 0)
	{
		m_CurrentLevel--;
	}

	return m_Episodes[m_CurrentEpisode].m_Levels[m_CurrentLevel];
}

// Get the current level
EncodedLevel SokobanLevelManager::GetCurrentLevel(void)
{
	return m_Episodes[m_CurrentEpisode].m_Levels[m_CurrentLevel];
}

// Get the first level in the next available episode
EncodedLevel SokobanLevelManager::GetNextEpisode(void)
{
	if (m_CurrentEpisode < (m_Episodes.size() - 1))
	{
		m_CurrentEpisode++;
	}

	m_CurrentLevel = 0;

	return m_Episodes[m_CurrentEpisode].m_Levels[m_CurrentLevel];
}

// Get the first level in the previous episode
EncodedLevel SokobanLevelManager::GetPrevEpisode(void)
{
	// change episode
	if (m_CurrentEpisode != 0)
	{
		m_CurrentEpisode--;
	}

	// reset level
	m_CurrentLevel = 0;

	return m_Episodes[m_CurrentEpisode].m_Levels[m_CurrentLevel];
}
// Get a unique string that will identify the level
string SokobanLevelManager::GetLevelIDString(void)
{
	string LevelID;

	LevelID = m_Episodes[m_CurrentEpisode].m_EpisodeName;
	LevelID += "\\";
	LevelID += m_Episodes[m_CurrentEpisode].m_Levels[m_CurrentLevel].m_LevelName;

	return LevelID;
}

// Get a list of all the names of the episodes
vector<EpisodeInfo> SokobanLevelManager::GetEpisodeInfo(void)
{
	vector<EpisodeInfo> ActiveEpisodes;

	// build the list
	vector<LevelSet>::iterator ii;

	for(ii=m_Episodes.begin(); ii!=m_Episodes.end(); ii++)
	{
		EpisodeInfo ThisEpisode;

		ThisEpisode.EpisodeName = (*ii).m_EpisodeName;
		ThisEpisode.NumberOfLevels = (*ii).m_Levels.size();

		ActiveEpisodes.push_back(ThisEpisode);
	}

	return ActiveEpisodes;
}

// Get the total number of active episodes
int SokobanLevelManager::GetActiveEpisodeTotal(void)
{
	return m_Episodes.size() - 1;
}


// Set the current active episode
void SokobanLevelManager::SetActiveEpisode(int NewActiveEpisode)
{
	// new episode within valid range
	if((NewActiveEpisode > m_Episodes.size()) || (NewActiveEpisode < 0))
	{
		// just abort
		return;
	}

	// set the episode
	m_CurrentEpisode = NewActiveEpisode;
	m_CurrentLevel = 0;
}