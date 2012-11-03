#include ".\sokobanhighscore.h"

#include <Windows.h>
#include <sstream>
#include <iostream>
using namespace std;

SokobanHighscore::SokobanHighscore(void)
{
}

SokobanHighscore::~SokobanHighscore(void)
{
}

// Add a new high score into the list
bool SokobanHighscore::AddHighscore(string FileName, int NumberOfMoves)
{
	// check if this level has a highscore yet
	vector<HighscorePair>::iterator ii;
	for(ii=_HighScores.begin(); ii!=_HighScores.end(); ii++)
	{
		// look for a matching level
		if ( ii->first == FileName )
		{
			// check if the new score beats the old one
			if (NumberOfMoves < ii->second)
			{
				// update with improved score
				ii->second = NumberOfMoves;

				return true;
			}
			
			// score wasnt better changed
			return false;
		}
	}

	// level not found, new entry
	HighscorePair NewHighscore;
	NewHighscore.first = FileName;
	NewHighscore.second = NumberOfMoves;

	_HighScores.push_back( NewHighscore );

	return true;

}

// Get the high score for the current level
int SokobanHighscore::GetCurrentHighscore(string FileName)
{
	// check if this level has a highscore yet
	vector<HighscorePair>::const_iterator cii;
	for(cii=_HighScores.begin(); cii!=_HighScores.end(); cii++)
	{
		// look for a matching level
		if ( cii->first == FileName )
		{
			// return score
			return cii->second;
		}
	}

	// if it hasnt got a highscore yet, return 0
	return 0;
}

// Load a high score file into memory
void SokobanHighscore::LoadFromFile(string FileName)
{
	// open the file
	// read one line of filename
	// read one line of score
	// add to list


	// clear current data
	_HighScores.clear();

	// open level file
	ifstream HighScoreFile(FileName.c_str(), ios::in);

	// check level open success
	if(!HighScoreFile)
	{
		// TODO Add this message to the miniconsole when its ready
		// MessageBox (HWND_DESKTOP, "Could not open HighScore file for loading!", "Error", MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	string tmpScoreDataLine;
	vector<string> tmpFileStorage;

	// load data line by line from file into vector
	while (getline(HighScoreFile, tmpScoreDataLine))
	{
		// add line of data
		tmpFileStorage.push_back (tmpScoreDataLine);

	}

	// now loop through data and put it into format
	for (int indx = 0; indx < tmpFileStorage.size(); indx += 2)
	{
		HighscorePair NewScore;
		NewScore.first = tmpFileStorage[indx];

		stringstream ss(tmpFileStorage[indx+1]);
		ss >> NewScore.second;

		_HighScores.push_back(NewScore);
	}

	//std::stringstream ss("123"); if(ss >> myint) /* success */;
	//convert = Using the 'translators' built into the C++ stream libraries (which are extendable), a simple conversion technique is: #include <sstream> std::stringstream tempstream;   tempstream << whatever;  if ( tempstream >> whateverelse )  // conversion worked!;

/*	string TEMP_DataLine;
	string TEMP_Line1;
	int stupid_check = 1;

	// load data line by line from file into vector
	while (getline(HighScoreFile, TEMP_DataLine))
	{
		HighscorePair NewScore;
		NewScore.first = TEMP_DataLine;
		HighScoreFile << NewScore.second;

		_HighScores.push_back(NewScore);
	}*/

//	while (getline(HighScoreFile, TEMP_DataLine))
//	{
//		switch(stupid_check)
//		{
//		    case 1:
//				TEMP_DataLine = TEMP_Line1;
//				stupid_check = 2;
//		        break;
//
//			case 2:
//				HighscorePair NewScore;
//				NewScore.first = TEMP_Line1;
//				NewScore.second = (int)TEMP_DataLine.c_str();
//
//				_HighScores.push_back(NewScore);
//
//				stupid_check = 1;
//				break;
//		}
//	}
		//tmpEpisodeDataLine.insert(0, m_sLevelBasePath);

		// add line of data
		//Filenames.push_back (tmpEpisodeDataLine);

		//TotalLevels++;
	

//	 load data line by line from file into vector
//		while (!HighScoreFile.eof())
//		{
//			HighscorePair NewScore;
//			HighScoreFile.getline(NewScore.first, 1024);
//			HighScoreFile.getline(NewScore.second, 30);
//			
//			// add line of data
//			_HighScores.push_back (NewScore);
//		}

	// Close file, not strictly needed as destructor will call it anyway
	HighScoreFile.close();

}

// Load the default level file into memory
void SokobanHighscore::LoadDefaultFile(void)
{
	LoadFromFile(".\\data\\highscores.txt");
}


// Save the current highscore information to a file
void SokobanHighscore::SaveToFile(string FileName)
{
	// open level file
	ofstream HighScoreFile(FileName.c_str(), ios::out);

	// check level open success
	if(!HighScoreFile)
	{
		MessageBox (HWND_DESKTOP, "Could not open HighScore file for saving!", "Error", MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	//Students << FirstName << "\n" << LastName << "\n" << Age;
	vector<HighscorePair>::const_iterator cii;
	for(cii=_HighScores.begin(); cii!=_HighScores.end(); cii++)
	{
		HighScoreFile << cii->first << endl << cii->second << endl;
	}	

	// Close file, not strictly needed as destructor will call it anyway
	HighScoreFile.close();

	// finished
	return;
}


// Save the current highscore information to the default highscore file
void SokobanHighscore::SaveToDefaultFile(void)
{
	SaveToFile(".\\data\\highscores.txt");
}



// DEBUG function
void SokobanHighscore::DEBUG_DumpScoreList(void)
{
	cout << endl << "dumping list of size " << _HighScores.size() << endl;

	for (int indx = 0; indx < _HighScores.size(); indx++)
	{
		cout << "index [" << indx << "] :: " << _HighScores[indx].first << " :: " << _HighScores[indx].second << endl;
	}
}
