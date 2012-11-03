#pragma once

#include <string>
#include <vector>
#include <iostream>
using namespace std;

class EncodedLevel
{
public:
	EncodedLevel(void);
	~EncodedLevel(void);
	// Name of the Level
	string m_LevelName;
	vector<string> m_EncodedData;
	// Debug function to display an Encoded Level
	void DEBUG_DumpEncodedLevel(void);
};
