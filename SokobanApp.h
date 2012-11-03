#pragma once

#include "SokobanGame.h"
#include "SokobanMenu.h"
#include "SokobanSoundManager.h"

#include "Shared.h"

enum SokobanAppState
{
	APPSTATE_DEMOLOOP,
	APPSTATE_GAMEPLAYING,
	APPSTATE_INGAMEMENU
};

class SokobanApp
{
public:
	SokobanApp(void);
	~SokobanApp(void);

	void Setup(void);
	void Destroy(void);
	void Render(void);
	void KeyPressed(char KeyEvent);

private:
	SokobanGame GameManager;
	SokobanMenu MenuManager;

	SokobanAppState AppState;

	// timer
	CTimer Timer;

	// Take a screenshot and save it to file
	void TakeScreenshot(void);

	// Key pressed while app is in the menu
	void KeyPressed_Menu(char WhatKey);

	// Process a key that was pressed in game
	void KeyPressed_Game(char WhatKey);

};
