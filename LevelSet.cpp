#include "LevelSet.h"

#include <Windows.h>
#include <assert.h>

#include <iostream>
#include <fstream>
#include ".\levelset.h"
using namespace std;



LevelSet::LevelSet(void)
{
}

LevelSet::~LevelSet(void)
{
}

// Load an SLC level set into memory
void LevelSet::LoadSLCFile(char* FileName)
{
	string ThisLine;

	// reset any level data;
	Reset();

	// open the level file
	ifstream LevelSetFile(FileName, ios::in);

	// check level open success
	assert(LevelSetFile && "Failed to load Level Set!");
//	if(!LevelSetFile)
//	{
//		// TODO Notify User Of Failure
//		return;
//	}

    // read first line into episode namespace
	getline(LevelSetFile, ThisLine);
	if(ThisLine[0] == ';') { ThisLine.erase(0,2); }
	m_EpisodeName = ThisLine;

	getline(LevelSetFile, ThisLine);
	assert(ThisLine.length() == 0 && "Line should be blank");

	// read lines into commentblock until blank line
	getline(LevelSetFile, ThisLine);
	if(ThisLine[0] == ';') { ThisLine.erase(0,2); }	// trim ;

	while (ThisLine.length() != 0)
	{
		m_CommentBlock.push_back(ThisLine);
        
		getline(LevelSetFile, ThisLine);
		if((ThisLine.length() > 2) && (ThisLine[0] == ';')) { ThisLine.erase(0,2); }
	}

	// keep reading lines until over
	while(!LevelSetFile.eof())
	{
		EncodedLevel NewLevel;

		// read level name
		getline(LevelSetFile, ThisLine);
		if((ThisLine.length() > 2) && (ThisLine[0] == ';')) { ThisLine.erase(0,2); }
		NewLevel.m_LevelName = ThisLine;

		// read line of level data until blank line
		getline(LevelSetFile, ThisLine);

		while (ThisLine.length() != 0)
		{
			NewLevel.m_EncodedData.push_back(ThisLine);

			getline(LevelSetFile, ThisLine);
		}

		// add new level to database
		m_Levels.push_back(NewLevel);
	}


}

// Dump the level set to screen
void LevelSet::DEBUG_DumpLevelSet(void)
{
	cout << "DUMPING LEVEL SET" << endl
		<< "---------------------------------------------------" << endl
		<< "Episode Name : " << m_EpisodeName << endl
		<< "Comment Block : " << endl << "COMMENT BEGIN" << endl;

	for (unsigned int indx = 0; indx < m_CommentBlock.size(); indx++)
	{
		cout << m_CommentBlock[indx] << endl;
	}
	
	cout << "COMMENT END" << endl << endl;

	cout << "Total Levels : " << m_Levels.size() << endl;

	for (unsigned int indx = 0; indx < m_Levels.size(); indx++)
	{
		cout << "-------------------------------------------------" << endl
			<< "Level Name : " << m_Levels[indx].m_LevelName << endl
			<< "Encoded Data : " << endl << "ENCODED DATA BEGIN" << endl;

		for (unsigned int i = 0; i < m_Levels[indx].m_EncodedData.size(); i++)
		{
			cout << m_Levels[indx].m_EncodedData[i] << endl;
		}
		
		cout << "ENCODED DATA END" << endl << endl;
		
	}

}

// Reset all data in Level Set
void LevelSet::Reset(void)
{
	m_Levels.clear();
	m_EpisodeName.clear();
	m_CommentBlock.clear();
}
