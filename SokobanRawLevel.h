#pragma once

#include "SokobanActiveLevel.h"		// for LevelWallData

#define SOKOBANLEVELFILEVERSION "// sokoban level file - v0.1"

#include "LevelSet.h"

class SokobanRawLevel
{
public:
	SokobanRawLevel(void);
	~SokobanRawLevel(void);

	// reset all values to defaults
	void Reset(void);

	// load a level from a file
	int LoadFromFile(char* cpLevelFileName);

	// extract the level into a SokobanActiveLevel file
	SokobanActiveLevel Extract(void);

	LevelSet m_EpisodeOne;

private:
	string				m_DefaultTheme;
	LevelWallData		m_RawLevelData;


	int _LoadRawLevelFile(char* cLevelFileName);
	SokobanActiveLevel _ExtractLevelItems(void);

	// Insert the void areas (areas outside of the level walls)
	//void _InsertVoidAreas(void);

};
