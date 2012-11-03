#pragma once

#include <string>
#include <vector>
#include <utility>		// for pair
#include <fstream>
using namespace std;

typedef pair<string, int> HighscorePair;

class SokobanHighscore
{
public:
	SokobanHighscore(void);
	~SokobanHighscore(void);

	// Add a new high score into the list (returns true if highscore achieved)
	bool AddHighscore(string FileName, int NumberOfMoves);

	// Get the high score for the current level
	int GetCurrentHighscore(string FileName);

	// Load a high score file into memory
	void LoadFromFile(string FileName);

	// Load the default level file into memory
	void LoadDefaultFile(void);

	// Save the current highscore information to a file
	void SaveToFile(string FileName);

	// Save the current highscore information to the default highscore file
	void SaveToDefaultFile(void);

private:
	// The list of high scores
	vector<HighscorePair> _HighScores;
public:
	// DEBUG function
	void DEBUG_DumpScoreList(void);
};
