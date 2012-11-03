#include ".\EncodedLevel.h"

EncodedLevel::EncodedLevel(void)
{
}

EncodedLevel::~EncodedLevel(void)
{
}

// Debug function to display an Encoded Level
void EncodedLevel::DEBUG_DumpEncodedLevel(void)
{
	cout << "-------------------------------------------------" << endl
		<< "Level Name : " << m_LevelName << endl
		<< "Encoded Data : " << endl << "ENCODED DATA BEGIN" << endl;

	for (int i = 0; i < m_EncodedData.size(); i++)
	{
		cout << m_EncodedData[i] << endl;
	}

	cout << "ENCODED DATA END" << endl << endl;
}
