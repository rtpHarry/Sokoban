#pragma once

#include <vector>
using namespace std;

#include "Vector2.h"

enum EventType				// actions a player may take
{
	MOVE_EVENT_NOEVENT,			// empty event (for when last event popped off stack)
	MOVE_EVENT_STEP,				// normal player move
	MOVE_EVENT_BUMPCRATE,		// player walks into crate that wont move
	MOVE_EVENT_BUMPWALL,			// player walks into wall
	MOVE_EVENT_PUSHTOEMPTY,		// player push crate
	MOVE_EVENT_PUSHTOWALL,		// player push crate and next square is a wall  (for sound of crate hitting wall)
	MOVE_EVENT_PUSHTOCRATE,		// player push crate and next square is a crate (for sound of crate hitting crate)
	MOVE_EVENT_PUSHTOTARGET,		// player push crate onto target
	MOVE_EVENT_PUSHFROMTARGET,	// player push crate out of target
	MOVE_EVENT_PUSHBETWEENTARGETS // player pushed crate from one target straight onto another
};

typedef Vector2 EventLocation;		// location of the player when event STARTED

enum EventDirection			// directions a player may move
{
	DIR_NODIRECTION,
	DIR_NORTH,
	DIR_SOUTH,
	DIR_WEST,
	DIR_EAST
};

// an event is an action the player takes within the gameboard
class MoveEvent
{
public:
	MoveEvent(void)
	{
		Type = MOVE_EVENT_NOEVENT;
		Location.Set(0,0);
		Direction = DIR_NODIRECTION;
	}

	MoveEvent(EventType NewType) : Type(NewType) { };

	~MoveEvent(void){ }

	EventType		Type;
	EventLocation	Location;
	EventDirection	Direction;
};

// tracks non-cosmetic events ie
//		EVENT_STEP,				// normal player move
//		EVENT_PUSHTOEMPTY,		// player push crate
//		EVENT_PUSHTOWALL,		// player push crate and next move would be wall
//		EVENT_PUSHTOTARGET,		// player push crate onto target
//		EVENT_PUSHFROMTARGET,	// player push crate out of target
class MoveList
{
public:
	MoveList(void);
	~MoveList(void);
private:
	vector<MoveEvent> _Events;

public:
	// Add an event to the event stack
	void AddEvent(MoveEvent NewEvent);
	void AddEvent(EventType type, EventLocation loc, EventDirection dir);

	// Remove the last event added and return it for further use
	MoveEvent RemoveEvent(void);

	// Returns the number of moves stored in the MoveList
	int GetMoveCount(void) const {	return _Events.size();	}

	// Reset the data in MoveList
	void Reset(void);
};


// global utility functions for MoveEvent
// Get the grid location of offset OffsetAmt in direction Direction
EventLocation GetOffsetLocation(MoveEvent Event, int OffsetAmt);
EventLocation GetOffsetLocation(EventLocation SourceLocation, EventDirection Direction, int OffsetAmt);

