#include "SokobanActiveLevel.h"

#include <assert.h>

//#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;



SokobanActiveLevel::SokobanActiveLevel(void)
{
	// set default values
	Reset();
}

SokobanActiveLevel::~SokobanActiveLevel(void)
{
}

void SokobanActiveLevel::Reset(void)
{
	m_WallData.clear();
	m_ItemList.clear();
	m_Player.ItemType = SYMBOL_PLAYER;
	m_Player.ItemLocation.x = 0;
	m_Player.ItemLocation.y = 0;
	m_LevelDimensions.x = 0;
	m_LevelDimensions.y = 0;
	m_TargetQuota = 0;
	m_TargetsTagged = 0;

	m_MoveList.Reset();
}

// Replace all data with a new level and reset move list
void SokobanActiveLevel::Reset(SokobanActiveLevel NewLevel)
{
	// clear current data
	Reset();

	// apply new
	m_WallData = NewLevel.m_WallData;
	m_ItemList = NewLevel.m_ItemList;
	m_Player = NewLevel.m_Player;
	m_LevelDimensions = NewLevel.m_LevelDimensions;
	m_TargetQuota = NewLevel.m_TargetQuota;
	m_TargetsTagged = NewLevel.m_TargetsTagged;
	m_MoveList = NewLevel.m_MoveList;
}


void SokobanActiveLevel::_ExtractLevelItems(EncodedLevel NewLevel)
{
	// reset data
	Reset();

	// extract item locations
	///////////////////////////////
	string tmpLevelDataLine;
	LevelItem tmpItem;
	unsigned int tmpLongestLine = 0;	// longest line so far (width of level at end)

	for (unsigned int outer = 0; outer < NewLevel.m_EncodedData.size(); outer++)
	{
		tmpLevelDataLine = NewLevel.m_EncodedData[outer];

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
				m_Player.ItemLocation.x = outer;
				m_Player.ItemLocation.y = inner;
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
				m_ItemList.push_back (tmpItem);
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
				m_ItemList.push_back (tmpItem);

				// increase taret quota
				m_TargetQuota++;

				// tagged targets
				if (tmpLevelDataLine[inner] == SYMBOL_CRATE_ON_TARGET)
					m_TargetsTagged++;
			}

		}
	}

	// build wall list
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	for (unsigned int outer = 0; outer < NewLevel.m_EncodedData.size(); outer++)
	{
		tmpLevelDataLine = NewLevel.m_EncodedData[outer];

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
		m_WallData.push_back (tmpLevelDataLine);
	}


	// save max level width
	m_LevelDimensions.x = tmpLongestLine - 1;

	// save max level height
	m_LevelDimensions.y = NewLevel.m_EncodedData.size() - 1;

	// done
	return;
}



// extracts a list of all items in the level of type ItemType
//////////////////////////////////////////////////////////////////////////
LevelItemList SokobanActiveLevel::GetMatchingItems(char ItemType)
{
	LevelItemList FilteredItemList;

	// loop all items in level
	for (unsigned int indx = 0; indx < m_ItemList.size(); indx++)
	{
		// if find matching item type
		if (m_ItemList[indx].ItemType == ItemType)
		{
			// add it to the filtered list
			FilteredItemList.push_back( m_ItemList[indx] );
		}
	}

	// return the filtered list
	return FilteredItemList;
}


// extracts a list of all items located at SourceItemLocation
//////////////////////////////////////////////////////////////////////////
LevelItemList SokobanActiveLevel::GetItemsAtLocation(Vector2 SourceItemLocation)
{
	LevelItemList FilteredItemList;

	// loop all items in level
	for (unsigned int indx = 0; indx < m_ItemList.size(); indx++)
	{
		// if find matching item type
		if (m_ItemList[indx].ItemLocation == SourceItemLocation)
		{
			// add it to the filtered list
			FilteredItemList.push_back( m_ItemList[indx] );
		}
	}

	// also check architecture
	LevelItem tmpArchitecture;

	tmpArchitecture.ItemType = m_WallData[SourceItemLocation.x][SourceItemLocation.y];
	tmpArchitecture.ItemLocation = SourceItemLocation;

	FilteredItemList.push_back(tmpArchitecture);

	// return the filtered list
	return FilteredItemList;
}


void SokobanActiveLevel::ChangeItem(LevelItem ItemToMatch, LevelItem NewItemValues)
{
	// loop all items in filtered list
	for (unsigned int indx = 0; indx < m_ItemList.size(); indx++)
	{
		// if find matching item type
		if (m_ItemList[indx] == ItemToMatch)
		{
			// update crate location
			m_ItemList[indx] = NewItemValues;
		}
	}
}


// Perform the operation in MoveEvent on the gameboard in Level
void SokobanActiveLevel::ExecuteMoveEvent(const MoveEvent Event)
{
	// add move to queue
	m_MoveList.AddEvent(Event);

	// get all locations
	EventLocation Location1, Location2;
	Location1 = GetOffsetLocation(Event, 1);
	Location2 = GetOffsetLocation(Event, 2);

	switch(Event.Type)
	{
	case MOVE_EVENT_NOEVENT:				// empty event (for when last event popped off stack)
		// EVENT_NOEVENT should not occur!
		break;

	case MOVE_EVENT_STEP:				// normal player move
		m_Player.ItemLocation = Location1;
		break;

	case MOVE_EVENT_BUMPCRATE:			// player walks into crate that wont move
		// do nothing
		break;

	case MOVE_EVENT_BUMPWALL:			// player walks into wall
		// do nothing
		break;

	case MOVE_EVENT_PUSHTOEMPTY:			// player push crate
	case MOVE_EVENT_PUSHTOWALL:			// player push crate and next square is a wall  (for sound of crate hitting wall)
	case MOVE_EVENT_PUSHTOCRATE:			// player push crate and next square is a crate (for sound of crate hitting crate)
	case MOVE_EVENT_PUSHBETWEENTARGETS:	// player pushed crate from one target straight onto another
		ChangeItem(LevelItem(SYMBOL_CRATE, Location1), LevelItem(SYMBOL_CRATE, Location2));
		m_Player.ItemLocation = Location1;
		break;

	case MOVE_EVENT_PUSHTOTARGET:		// player push crate onto target
		ChangeItem(LevelItem(SYMBOL_CRATE, Location1), LevelItem(SYMBOL_CRATE, Location2));
		m_Player.ItemLocation = Location1;
		m_TargetsTagged += 1;
		break;

	case MOVE_EVENT_PUSHFROMTARGET:		// player push crate out of target
		ChangeItem(LevelItem(SYMBOL_CRATE, Location1), LevelItem(SYMBOL_CRATE, Location2));
		m_Player.ItemLocation = Location1;
		m_TargetsTagged -= 1;
		break;
	}
}


// Undo the operation in MoveEvent on the gameboard in Level
void SokobanActiveLevel::ReverseMoveEvent(const MoveEvent Event)
{
	// get all locations
	EventLocation Location0, Location1, Location2;
	Location0 = Event.Location;
	Location1 = GetOffsetLocation(Event, 1);
	Location2 = GetOffsetLocation(Event, 2);

	// check that this IS the last move made
	// works but fails on empty queue because location is 0,0
	// assert(m_Player.ItemLocation == Location1); 

	switch(Event.Type)
	{
	case MOVE_EVENT_NOEVENT:				// empty event (for when last event popped off stack)
		// EVENT_NOEVENT should not occur!
		break;

	case MOVE_EVENT_STEP:				// normal player move
		m_Player.ItemLocation = Location0;
		break;

	case MOVE_EVENT_BUMPCRATE:			// player walks into crate that wont move
		// do nothing
		break;

	case MOVE_EVENT_BUMPWALL:			// player walks into wall
		// do nothing
		break;

	case MOVE_EVENT_PUSHTOEMPTY:			// player push crate
	case MOVE_EVENT_PUSHTOWALL:			// player push crate and next square is a wall  (for sound of crate hitting wall)
	case MOVE_EVENT_PUSHTOCRATE:			// player push crate and next square is a crate (for sound of crate hitting crate)
	case MOVE_EVENT_PUSHBETWEENTARGETS:	// player pushed crate from one target straight onto another
		ChangeItem(LevelItem(SYMBOL_CRATE, Location2), LevelItem(SYMBOL_CRATE, Location1));
		m_Player.ItemLocation = Location0;
		break;

	case MOVE_EVENT_PUSHTOTARGET:		// player push crate onto target
		ChangeItem(LevelItem(SYMBOL_CRATE, Location2), LevelItem(SYMBOL_CRATE, Location1));
		m_Player.ItemLocation = Location0;
		m_TargetsTagged -= 1;
		break;

	case MOVE_EVENT_PUSHFROMTARGET:		// player push crate out of target
		ChangeItem(LevelItem(SYMBOL_CRATE, Location2), LevelItem(SYMBOL_CRATE, Location1));
		m_Player.ItemLocation = Location0;
		m_TargetsTagged += 1;
		break;
	}
}

