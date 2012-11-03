#pragma once

#include "SokobanRenderer.h"
#include "SokobanLevelManager.h"
#include "SokobanHighScore.h"
#include "SokobanHUD.h"

#include "Vector3.h"
#include "timer.h"
#include "camera.h"

enum SokobanGameState
{
	GAMESTATE_DEMOLOOP,			// a game hasnt been started yet or has been quit
	GAMESTATE_INGAME,			// a game is being played
	GAMESTATE_LEVELCOMPLETE,	// a level has been completed
	GAMESTATE_INMENU,			// a game is being played but the user has pressed esc to the menu
//	GAMESTATE_INMENUHELP		// TODO a user has pressed the help key
};

class SokobanGame
{
public:
	SokobanGame(void);
	~SokobanGame(void);

private:
	SokobanHighscore HighScores;			// List of highscores

	SokobanRenderer LevelRenderer;			// opengl level rendering
	
	SokobanActiveLevel LevelData;			// the current level data
	//SokobanLevelManager LevelManager;		// level file io

	SokobanHUD HUD;							// Heads Up Display

	// current game state
	SokobanGameState GameState;

	// The array of camera views
	CameraOrientation m_CameraViews[3];
	int m_CurrentCamera;

	// filthy hack to get sound played only once on completion
	bool bPlayedSoundOnce;


public:
	// Initialize the system
	void Setup(void);
	// Destructor
	void Destroy(void);
	// Process a key press
	SokobanGameState KeyPressed(char WhatKey);
	// Render the current gamestate
	void Render(void);
	// When the player tries to move a new MoveEvent is fired which decides what to do
	MoveEvent NewMoveEvent(SokobanActiveLevel Level, EventDirection Dir);


private:
	// Perform any rendering before the game level is rendered
	void PreRender(void);

	// Perform any rendering after the game level is rendered
	void PostRender(void);

	// Process a key pressed while gamestate is in GAMESTATE_INGAME
	void KeyPressed_InGame(char WhatKey);

	// Process a key when the gamestate is in GAMESTATE_LEVELCOMPLETE
	void KeyPressed_LevelComplete(char WhatKey);


	// gamelogic related
	// check if an item is found at in a LevelItemList
	bool IsItemInItemList(LevelItemList Items, int ItemType);

	// gamelogic related
	// Decide which move event is occuring
	EventType ClassifyMoveEventType(const MoveEvent Event, SokobanActiveLevel Level);

   
public:
	// Start a new game
	int StartNewGame(void);
	// Return to the game from the menu
	void ReturnToGame(void);
	// Cycle between the different camera views
	void CycleCameraView(void);
};

