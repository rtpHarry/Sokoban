#pragma once
#include <vector>			// stl vector class
#include <string>
#include <iostream>
#include <fstream>
using namespace std;		// expose std namespace used in stl

#include "Vector2.h"		// my vector2int class
#include "MoveList.h"		// for MoveEvent

#include "EncodedLevel.h"

#define SYMBOL_PLAYER    		'@'
#define SYMBOL_PLAYER_ON_TARGET '+'
#define SYMBOL_CRATE			'$'
#define SYMBOL_CRATE_ON_TARGET  '*'
#define SYMBOL_TARGET			'.'
#define SYMBOL_FLOOR			' '
#define SYMBOL_WALL				'#'
#define SYMBOL_VOID				'X'


//////////////////////////////////////////////////////////////////////////
//
class LevelItem
{
public:
	LevelItem(void) {}
	LevelItem(char Type, Vector2 Loc) { ItemType = Type; ItemLocation = Loc; }
	~LevelItem(void) {}

public:
	char		ItemType;
	Vector2		ItemLocation;

	bool operator==(const LevelItem rhs)
	{
		// compare
		if(ItemType == rhs.ItemType && ItemLocation == rhs.ItemLocation)
		{
			// equal
			return true;
		}

		// something didnt match
		return false;
	}

};

//////////////////////////////////////////////////////////////////////////
//
typedef vector<LevelItem>			LevelItemList;
typedef vector<string>				LevelWallData;

//////////////////////////////////////////////////////////////////////////
//
class SokobanActiveLevel
{
public:
	LevelWallData		m_WallData;
	LevelItemList		m_ItemList;
	LevelItem			m_Player;
	Vector2				m_LevelDimensions;

	int					m_TargetQuota;
	int					m_TargetsTagged;

	string				m_RenderTheme;

private:
	MoveList			m_MoveList;

public:
	SokobanActiveLevel(void);
	~SokobanActiveLevel(void);

	// reset all values to defaults
	void Reset(void);

	// extract a filtered LevelItemList from the current level dataset
	LevelItemList GetMatchingItems(char ItemType);
	LevelItemList GetItemsAtLocation(Vector2 SourceItemLocation);

	// update a LevelItem in the current level dataset
	void ChangeItem(LevelItem ItemToMatch, LevelItem NewItemValues);

	// Perform the operation in MoveEvent on the gameboard in Level
	void ExecuteMoveEvent(const MoveEvent Event);

	// Undo the operation in MoveEvent on the gameboard in Level
	void ReverseMoveEvent(const MoveEvent Event);

public:
	// MoveList Related
	// Get the number of moves the player has made this level
	int GetMoveCount(void) const
	{
		return m_MoveList.GetMoveCount();
	}

	// Remove a move event from the stack (UNDO)
	MoveEvent RemoveMoveEvent(void)
	{
		// remove and return (error checking already done in MoveEvent class)
		return m_MoveList.RemoveEvent();
	}


	// Replace all data with a new level and reset move list
	void Reset(SokobanActiveLevel NewLevel);

	// extract information from an encoded level
	void _ExtractLevelItems(EncodedLevel NewLevel);
};
