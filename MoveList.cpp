#include ".\movelist.h"

//////////////////////////////////////////////////////////////////////////
// global functions for a MoveEvent
//////////////////////////////////////////////////////////////////////////
// Get the grid location of offset OffsetAmt in direction Direction
EventLocation GetOffsetLocation(MoveEvent Event, int OffsetAmt)
{
	return GetOffsetLocation(Event.Location, Event.Direction, OffsetAmt);
}

// Get the grid location of offset OffsetAmt in direction Direction
EventLocation GetOffsetLocation(EventLocation SourceLocation, EventDirection Direction, int OffsetAmt)
{
	EventLocation OffsetValue;
	EventLocation ReturnLocation;

	// first work out amount to adjust
	switch(Direction)
	{
	case DIR_NORTH:
		OffsetValue.x = -OffsetAmt;
		OffsetValue.y = 0;
		break;
	case DIR_SOUTH:
		OffsetValue.x = +OffsetAmt;
		OffsetValue.y = 0;
		break;
	case DIR_EAST:
		OffsetValue.x = 0;
		OffsetValue.y = +OffsetAmt;
		break;
	case DIR_WEST:
		OffsetValue.x = 0;
		OffsetValue.y = -OffsetAmt;
		break;
	}

	// work out grid location
	ReturnLocation.x = SourceLocation.x + OffsetValue.x;
	ReturnLocation.y = SourceLocation.y + OffsetValue.y;

	// pass back
	return ReturnLocation;
}
//////////////////////////////////////////////////////////////////////////
// end of global functions for MoveEvent
//////////////////////////////////////////////////////////////////////////

// start of movelist class
//////////////////////////////////////////////////////////////////////////
MoveList::MoveList(void)
{
}

MoveList::~MoveList(void)
{
}

// Add an event to the event stack
void MoveList::AddEvent(MoveEvent NewEvent)
{
	// only add if trackable event
	switch(NewEvent.Type)
	{
		case MOVE_EVENT_STEP:
		case MOVE_EVENT_PUSHTOEMPTY:
		case MOVE_EVENT_PUSHTOWALL:
		case MOVE_EVENT_PUSHTOTARGET:
		case MOVE_EVENT_PUSHFROMTARGET:
		case MOVE_EVENT_PUSHBETWEENTARGETS:

			// trackable event
			_Events.push_back(NewEvent);
			break;


		default:
			// player did not actually move
			return;
	}

}

void MoveList::AddEvent(EventType type, EventLocation loc, EventDirection dir)
{
	MoveEvent NewEvent;

	NewEvent.Type = type;
	NewEvent.Location = loc;
	NewEvent.Direction = dir;

	AddEvent(NewEvent);
}

// Remove the last event added and return it for further use
MoveEvent MoveList::RemoveEvent(void)
{
	MoveEvent ReturnEvent;

	// catch if no events to remove!
	if(_Events.empty())
	{
		// MoveEvent is initialized by default to an empty event so return it
		return ReturnEvent;
	}


	// grab last event
	ReturnEvent = _Events.back();

	// delete last event added to stack
	_Events.pop_back();

	// return grabbed event
	return ReturnEvent;
}

// Reset the data in MoveList
void MoveList::Reset(void)
{
	_Events.clear();
}
