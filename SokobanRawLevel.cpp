#include ".\sokobanrawlevel.h"

SokobanRawLevel::SokobanRawLevel(void)
{
}

SokobanRawLevel::~SokobanRawLevel(void)
{
}

void SokobanRawLevel::Reset(void)
{
	m_RawLevelData.clear();
}

int SokobanRawLevel::LoadFromFile(char* cpLevelFileName)
{
	// load level
	//_LoadRawLevelFile(cpLevelFileName);
	m_EpisodeOne.LoadSLCFile(cpLevelFileName);

	// TODO :: Insert Theme Mgr
	m_DefaultTheme = "Simple";

	// FAKE ATTACH THE LEVEL DATA
	m_RawLevelData = m_EpisodeOne.m_Levels[0].m_EncodedData;

	// removed: was buggy with strange level layouts, hard coded into file instead
	// convert void areas
	//_InsertVoidAreas();

	// return success
	return 1;
}

SokobanActiveLevel SokobanRawLevel::Extract(void)
{
	// extract info
	return _ExtractLevelItems();
}

int SokobanRawLevel::_LoadRawLevelFile(char* cLevelFileName)
{
	string tmpLevelDataLine;

	// clear any level data
	Reset();

	// open level file
	ifstream LevelFile(cLevelFileName, ios::in);

	// check level open success
	if(!LevelFile)
	{
		cout << "Error: Could not open file located at: " << endl
			<< "   " << cLevelFileName << endl << endl;
		return 0;
	}


	// get sokoban level version
	getline(LevelFile, tmpLevelDataLine);

	// check valid sokoban level file
	if(tmpLevelDataLine != SOKOBANLEVELFILEVERSION)
	{
		cout << "Error: Could not identify file version: " << endl
			<< "   " << tmpLevelDataLine << endl << endl;
		return 0;
	}


	// load data line by line from file into vector
	while (getline(LevelFile, tmpLevelDataLine))
	{
		// add line of data
		m_RawLevelData.push_back (tmpLevelDataLine);

	}

	// Close file, not strictly needed as destructor will call it anyway
	LevelFile.close();

	// loaded ok  
	return 1;  

}

SokobanActiveLevel SokobanRawLevel::_ExtractLevelItems(void)
{
	SokobanActiveLevel ReturnLevel;

	// extract item locations
	///////////////////////////////
	string tmpLevelDataLine;
	LevelItem tmpItem;
	unsigned int tmpLongestLine = 0;	// longest line so far (width of level at end)

	for (unsigned int outer = 0; outer < m_RawLevelData.size(); outer++)
	{
		tmpLevelDataLine = m_RawLevelData[outer];

		// loop through current line
		for (unsigned int inner = 0; inner < tmpLevelDataLine.length(); inner++)
		{
			// calculate level width
			//////////////////////////////////////////////////////////////////////////
			if(tmpLevelDataLine.length() > tmpLongestLine)
			{
				tmpLongestLine = tmpLevelDataLine.length();
			}

			// look for a player symbol
			//////////////////////////////////////////////////
			if (tmpLevelDataLine[inner] == SYMBOL_PLAYER ||
				tmpLevelDataLine[inner] == SYMBOL_PLAYER_ON_TARGET)
			{
				ReturnLevel.m_Player.ItemLocation.x = outer;
				ReturnLevel.m_Player.ItemLocation.y = inner;
			}

			// look for all crate symbols
			//////////////////////////////////////////////////
			if (tmpLevelDataLine[inner] == SYMBOL_CRATE ||
				tmpLevelDataLine[inner] == SYMBOL_CRATE_ON_TARGET)
			{
				// add item to list
				tmpItem.ItemType = SYMBOL_CRATE;
				tmpItem.ItemLocation.x = outer;
				tmpItem.ItemLocation.y = inner;
				ReturnLevel.m_ItemList.push_back (tmpItem);
			}

			// look for all target symbols
			//////////////////////////////////////////////////
			if (tmpLevelDataLine[inner] == SYMBOL_TARGET ||
				tmpLevelDataLine[inner] == SYMBOL_CRATE_ON_TARGET ||
				tmpLevelDataLine[inner] == SYMBOL_PLAYER_ON_TARGET)
			{
				// add item to list
				tmpItem.ItemType = SYMBOL_TARGET;
				tmpItem.ItemLocation.x = outer;
				tmpItem.ItemLocation.y = inner;
				ReturnLevel.m_ItemList.push_back (tmpItem);

				// increase taret quota
				ReturnLevel.m_TargetQuota++;

				// tagged targets
                if (tmpLevelDataLine[inner] == SYMBOL_CRATE_ON_TARGET)
					ReturnLevel.m_TargetsTagged++;
			}

		}
	}

	// build wall list
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	for (unsigned int outer = 0; outer < m_RawLevelData.size(); outer++)
	{
		tmpLevelDataLine = m_RawLevelData[outer];

		// loop through current line
		for (unsigned int inner = 0; inner < tmpLevelDataLine.length(); inner++)
		{
			// discard any non wall/floor/void items
			//////////////////////////////////////////////////
			if (tmpLevelDataLine[inner] == SYMBOL_PLAYER ||
				tmpLevelDataLine[inner] == SYMBOL_PLAYER_ON_TARGET ||
				tmpLevelDataLine[inner] == SYMBOL_CRATE ||
				tmpLevelDataLine[inner] == SYMBOL_CRATE_ON_TARGET ||
				tmpLevelDataLine[inner] == SYMBOL_TARGET)
			{
				// clear item
				tmpLevelDataLine[inner] = SYMBOL_FLOOR;
			}

		}

		// add clean line to wall list
		ReturnLevel.m_WallData.push_back (tmpLevelDataLine);
	}


	// save max level width
	ReturnLevel.m_LevelDimensions.x = tmpLongestLine - 1;

	// save max level height
	ReturnLevel.m_LevelDimensions.y = m_RawLevelData.size() - 1;

	// done
	return ReturnLevel;
}

/*
// Insert the void areas (areas outside of the level walls)
void SokobanRawLevel::_InsertVoidAreas(void)
{
	bool bFirstWallEncountered;

	// replace SYMBOL_FLOOR outside of level with SYMBOL_VOID
	for (unsigned int outer = 0; outer < m_WallData.size(); outer++)
	{
		bFirstWallEncountered = false; // reset line checker

		// loop through current line
		for (unsigned int inner = 0; inner < m_WallData[outer].length(); inner++)
		{
			// when first wall found stop checking
			if (m_WallData[outer][inner] == SYMBOL_WALL)
				bFirstWallEncountered = true;

			// convert to void if a floor found before a wall
			if ((bFirstWallEncountered == false) && (m_WallData[outer][inner] == SYMBOL_FLOOR))
				m_WallData[outer][inner] = SYMBOL_VOID;
		}

		// if this line is shorter than the max level width
		if ((signed int)m_WallData[outer].length() < m_LevelDimensions.y)
		{
			// calculate difference between line-length and level width
			int totalVoids = m_LevelDimensions.y - m_WallData[outer].length();

			// insert SYMBOL_VOID times the difference on the end
			for (int indx = 0; indx <= totalVoids; indx++)
				m_WallData[outer].insert(m_WallData[outer].end(), SYMBOL_VOID);

		}
	}

}*/