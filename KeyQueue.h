#pragma once

#include <queue>
using namespace std;


enum KeyEventType
{
	KEYTYPE_KEYDOWN,
	KEYTYPE_KEYUP,
	KEYTYPE_KEYREPEAT
};

struct KeyEvent
{
	char			KeyCode;
	KeyEventType	KeyType;
};

class KeyQueue
{
public:
	KeyQueue(void);
public:
	~KeyQueue(void);
public:
	// Add a newly pressed key to the queue
	void AddKeyToQueue(char NewKey);

private:
	// Internal data container
	queue<KeyEvent> _WaitingKeys;
};
