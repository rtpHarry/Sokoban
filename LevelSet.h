#pragma once

#include <string>
#include <vector>
using namespace std;

#include "EncodedLevel.h"

class LevelSet
{
public:
	LevelSet(void);
	~LevelSet(void);
	// Name of the episode
	string m_EpisodeName;
	// The comment block for the episode
	vector<string> m_CommentBlock;
	// The data for each level
	vector<EncodedLevel> m_Levels;
	// Load an SLC level set into memory
	void LoadSLCFile(char* FileName);
	// Dump the level set to screen
	void DEBUG_DumpLevelSet(void);
private:
	// Reset all data in Level Set
	void Reset(void);
};
