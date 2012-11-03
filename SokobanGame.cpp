#include "SokobanGame.h"

#include "FontGL.h"
#include "NeHeGL.h" // for g_window & g_camera
#include "SokobanSoundManager.h"

SokobanGame::SokobanGame(void)
{
}

SokobanGame::~SokobanGame(void)
{
}

// Initialize the system
void SokobanGame::Setup(void)
{
	// setup open gl
	//////////////////////////////////////////////////////////////////////////
	glClearColor(0.0f, 0.1f, 0.35f, 0.0f);					// Black Background

	glEnable(GL_DEPTH_TEST);								// Enable Depth Testing
	glClearDepth(1.0f);										// Depth Buffer Setup
	glDepthFunc(GL_LEQUAL);									// Type Of Depth Testing
	
	glShadeModel(GL_SMOOTH);								// Enables Smooth Color Shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);		// Really Nice Perspective Calculations
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	glEnable(GL_LIGHT0);									// Turn on a light with defaults set
	glEnable(GL_LIGHTING);									// Turn on lighting
	glEnable(GL_COLOR_MATERIAL);							// Allow color to affect shading

	glEnable(GL_TEXTURE_2D);								// Enable Texture Mapping
	glEnable(GL_NORMALIZE);									// enable normals
	glEnable(GL_CULL_FACE);									// Remove Back Face

	// setup level loaders
	//////////////////////////////////////////////////////////////////////////
	SokobanLevelManager &LevelManager = SokobanLevelManager::Instance();
	LevelManager.Setup();
	LevelData._ExtractLevelItems(LevelManager.GetCurrentLevel());

	// setup high scores
	//////////////////////////////////////////////////////////////////////////
	HighScores.LoadDefaultFile();

	// setup the HUD
	//////////////////////////////////////////////////////////////////////////
	HUD.Setup();

	// setup the camera
	//////////////////////////////////////////////////////////////////////////
	m_CurrentCamera = 5; // ticks round to 0 when called and sets to proper camera
	CycleCameraView(); 

	// setup default sounds
	//////////////////////////////////////////////////////////////////////////
	SokobanSoundManager &SoundMgr = SokobanSoundManager::Instance();

	SoundMgr.CacheSampleFromFile(GAME_EVENT_LEVELCOMPLETE, ".\\audio\\game\\complete-rtp.wav");
	SoundMgr.CacheSampleFromFile(GAME_EVENT_EPISODECOMPLETE, ".\\audio\\game\\complete-rtp.wav");
	SoundMgr.CacheSampleFromFile(GAME_EVENT_GAMECOMPLETE, ".\\audio\\game\\complete-rtp.wav");

	// filthy hack to play sound only once on completion
	bPlayedSoundOnce = false;

	// initalise render system
	//////////////////////////////////////////////////////////////////////////
	GameState = GAMESTATE_DEMOLOOP;
	LevelRenderer.Setup();
}

// Destructor
void SokobanGame::Destroy(void)
{
	// unload font
	//////////////////////////////////////////////////////////////////////////
	FontGL Font;
	Font.DestroyFonts();

	// save high score file
	//////////////////////////////////////////////////////////////////////////
	HighScores.SaveToDefaultFile();
}


// Process a key press (true if escape)
SokobanGameState SokobanGame::KeyPressed(char WhatKey)
{
	// make sure its not escape key
	if (WhatKey == VK_ESCAPE)
	{
		GameState = GAMESTATE_INMENU;
	}

	// else carry on with normal key processing
	if (GameState == GAMESTATE_LEVELCOMPLETE)
	{
		KeyPressed_LevelComplete(WhatKey);

		// BUGFIX: return after key press to avoid camera toggle when user presses space
		return GameState;
	}

	if (GameState == GAMESTATE_INGAME)
	{
		KeyPressed_InGame(WhatKey);
	}

	return GameState;
}

// Process a key when the gamestate is in GAMESTATE_LEVELCOMPLETE
void SokobanGame::KeyPressed_LevelComplete(char WhatKey)
{
	// Get a levelmanager
	SokobanLevelManager &LevelManager = SokobanLevelManager::Instance();

	if (WhatKey == VK_SPACE)
	{
		// reset sound toggle
		bPlayedSoundOnce = false;

		// last level in the game?
		if (LevelManager.IsLastLevelInGame())
		{
			// TODO return to main menu / highscores
			GameState = GAMESTATE_DEMOLOOP;
			return;
		}

		// last level in episode?
		if (LevelManager.IsLastLevelInEpisode())
		{
			LevelData._ExtractLevelItems(LevelManager.GetNextEpisode());
			GameState = GAMESTATE_INGAME;
			return;
		}

		// default : just a normal level completion
		LevelData._ExtractLevelItems(LevelManager.GetNextLevel());
		GameState = GAMESTATE_INGAME;

		return;
	}

	// dont process any other keys
	return;
}


// Process a key pressed while gamestate is in GAMESTATE_INGAME
void SokobanGame::KeyPressed_InGame(char WhatKey)
{
	SokobanLevelManager &LevelManager = SokobanLevelManager::Instance();

	switch(WhatKey)
	{
	case VK_DOWN:
		{
			MoveEvent NewMove = NewMoveEvent(LevelData, DIR_NORTH);
			LevelData.ExecuteMoveEvent(NewMove);
			
			SokobanSoundManager::Instance().PlaySample(NewMove);

			break;
		}

	case VK_UP:
		{
			MoveEvent NewMove = NewMoveEvent(LevelData, DIR_SOUTH);
			LevelData.ExecuteMoveEvent(NewMove);

			SokobanSoundManager::Instance().PlaySample(NewMove);

			break;
		}

	case VK_LEFT:
		{
			MoveEvent NewMove = NewMoveEvent(LevelData, DIR_WEST);
			LevelData.ExecuteMoveEvent(NewMove);

			SokobanSoundManager::Instance().PlaySample(NewMove);

			break;
		}

	case VK_RIGHT:
		{
			MoveEvent NewMove = NewMoveEvent(LevelData, DIR_EAST);
			LevelData.ExecuteMoveEvent(NewMove);

			SokobanSoundManager::Instance().PlaySample(NewMove);

			break;
		}

	case VK_HOME:
		LevelData._ExtractLevelItems(LevelManager.GetNextLevel());
		break;

	case VK_END:
		LevelData._ExtractLevelItems(LevelManager.GetPrevLevel());
		break;

 	case VK_PRIOR:
		LevelData._ExtractLevelItems(LevelManager.GetNextEpisode());
		break;

	case VK_NEXT:
		LevelData._ExtractLevelItems(LevelManager.GetPrevEpisode());
		break;

	case VK_INSERT:
		LevelData._ExtractLevelItems(LevelManager.GetCurrentLevel());
		break;

	case VK_BACK:
		LevelData.ReverseMoveEvent(LevelData.RemoveMoveEvent());
		break;

	case VK_SPACE:
		CycleCameraView();
		break;

	case 'W':
	case 'w':
		g_camera->MoveCamera((float) kSpeed);
		break;

	case 'S':
	case 's':
		g_camera->MoveCamera((float) -kSpeed);
		break;

	case 'A':
	case 'a':
		g_camera->StrafeCamera((float) -kSpeed * 4);
		break;

	case 'D':
	case 'd':
		g_camera->StrafeCamera((float) kSpeed * 4);
		break;


	}
}

// Start a new game
int SokobanGame::StartNewGame(void)
{
	LevelData._ExtractLevelItems(SokobanLevelManager::Instance().GetNewGameLevel());
	GameState = GAMESTATE_INGAME;

	// filthy hack to get sound to play only once on complete
	bPlayedSoundOnce = false;

	return 0;
}


// Render the level
void SokobanGame::Render(void)
{
	//
	switch(GameState)
	{
	    case GAMESTATE_INGAME:
		case GAMESTATE_INMENU:
			PreRender();
			LevelRenderer.RenderLevel(LevelData);
			PostRender();
			break;

		case GAMESTATE_LEVELCOMPLETE:
			PreRender();
			LevelRenderer.RenderLevel(LevelData);
			PostRender();

			// this is run in PostRender() now
			// HUD.DrawLevelComplete(LevelManager.IsLastLevelInEpisode(), LevelManager.IsLastLevelInGame());
			break;
	}

}


// Perform any rendering before the game level is rendered
void SokobanGame::PreRender(void)
{
	// calculate level position
	//
	// ((number of tiles - 1) * level gap) + number of tiles)
	// LevelData.m_LevelDimensions.x;

	// TODO calculate scale factor
	// for widest dimension of a level
	//   width is number of tiles + amount of gap space [(number of tiles - 1) * tile gap]
	//LevelRenderer.m_Theme.GetTileOffsetGap();
}

// Perform any rendering after the game level is rendered
void SokobanGame::PostRender(void)
{
	// get level manager instance
	SokobanLevelManager &LevelManager = SokobanLevelManager::Instance();

	HUD.DrawFPS();

	switch(GameState)
	{
	case GAMESTATE_INMENU:
		break;

	case GAMESTATE_INGAME:
		// draw hud
		HUD.DrawLevelInfo(
			LevelData.GetMoveCount(),
			LevelData.m_TargetQuota,
			LevelData.m_TargetsTagged,
			HighScores.GetCurrentHighscore(LevelManager.GetLevelIDString()));
		// check if the level has been completed
		if (LevelData.m_TargetQuota == LevelData.m_TargetsTagged)
		{
			// change game state
			GameState = GAMESTATE_LEVELCOMPLETE;

			// check for high score
			HighScores.AddHighscore(LevelManager.GetLevelIDString(), LevelData.GetMoveCount());
		}
		break;

	case GAMESTATE_LEVELCOMPLETE:
		if(LevelManager.IsLastLevelInGame())
		{
			HUD.DrawGameComplete();

			// play sound ONCE!
			if (!bPlayedSoundOnce)
				SokobanSoundManager::Instance().PlaySample(GAME_EVENT_GAMECOMPLETE);

		}
		else if(LevelManager.IsLastLevelInEpisode())
		{
			HUD.DrawEpisodeComplete();

			// play sound ONCE!
			if (!bPlayedSoundOnce)
				SokobanSoundManager::Instance().PlaySample(GAME_EVENT_EPISODECOMPLETE);
		}
		else
		{
			HUD.DrawLevelComplete();

			// play sound ONCE!
			if (!bPlayedSoundOnce)
				SokobanSoundManager::Instance().PlaySample(GAME_EVENT_LEVELCOMPLETE);
		}

		// filthy hack to make sure sound played only once
		bPlayedSoundOnce = true;

		break;
	}
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// Game Logic
//////////////////////////////////////////////////////////////////////////

// When the player tries to move a new MoveEvent is fired that figures out what happened
MoveEvent SokobanGame::NewMoveEvent(SokobanActiveLevel Level, EventDirection Dir)
{
	MoveEvent ThisMove;

	ThisMove.Location = Level.m_Player.ItemLocation;
	ThisMove.Direction = Dir;
	ThisMove.Type = ClassifyMoveEventType(ThisMove, Level);

	return ThisMove;
}

// Decide which move event is occuring
EventType SokobanGame::ClassifyMoveEventType(const MoveEvent Event, SokobanActiveLevel Level)
{
	// get all (safe) locations
	EventLocation Location0, Location1, Location2;
	Location0 = Event.Location;
	Location1 = GetOffsetLocation(Event, 1);

	// get a list of items at each (safe) location
	LevelItemList List1, List2;
	List1 = Level.GetItemsAtLocation(Location1);

	// decide on move type
	//////////////////////////////////////////////////////////////////////////

	// we walked into a wall
	//  check if [player+1] is wall then EVENT_BUMPWALL
	if(IsItemInItemList(List1, SYMBOL_WALL))	return MOVE_EVENT_BUMPWALL;

	// *** We can now be sure that we arent checking an edge wall so..
	// get the rest of the locations and items
	Location2 = GetOffsetLocation(Event, 2);
	List2 = Level.GetItemsAtLocation(Location2);

	// we are pushing a crate
	//  check if [player+1] is crate then enter crate subcheck
	if(IsItemInItemList(List1, SYMBOL_CRATE))
	{
		// if crate being pushed is on a target
		//  check if [player+1] is target then enter crate-on-target subcheck
		if(IsItemInItemList(List1, SYMBOL_TARGET))
		{
			// check if [player+2] is wall OR crate EVENT_BUMPCRATE
			if(IsItemInItemList(List2, SYMBOL_WALL) || IsItemInItemList(List2, SYMBOL_CRATE))
				return MOVE_EVENT_BUMPCRATE;

			// check if [player+2] is target AND empty then EVENT_PUSHBETWEENTARGETS
			if(IsItemInItemList(List2, SYMBOL_TARGET) && IsItemInItemList(List2, SYMBOL_FLOOR))
				return MOVE_EVENT_PUSHBETWEENTARGETS;

			// check if [player+2] is empty then EVENT_PUSHFROMTARGET
			if(IsItemInItemList(List2, SYMBOL_FLOOR))	return MOVE_EVENT_PUSHFROMTARGET;
		}

		// if crate is not on a target
		//  check if [player+2] is wall OR crate then EVENT_BUMPCRATE
		if(IsItemInItemList(List2, SYMBOL_WALL) || IsItemInItemList(List2, SYMBOL_CRATE))
			return MOVE_EVENT_BUMPCRATE;

		//  check if [player+2] is empty then enter crate-to-empty subcheck
		if(!IsItemInItemList(List2, SYMBOL_CRATE))
		{
			//  check if [player+2] is target then EVENT_PUSHTOTARGET
			if(IsItemInItemList(List2, SYMBOL_TARGET))	return MOVE_EVENT_PUSHTOTARGET;

			//  check if [player+2] is empty then EVENT_PUSHTOEMPTY
			if(IsItemInItemList(List2, SYMBOL_FLOOR))	return MOVE_EVENT_PUSHTOEMPTY;
		}
	} // end of pushing a crate

	// we walked into empty space
	//  check if [player+1] is empty then EVENT_STEP
	if(IsItemInItemList(List1, SYMBOL_FLOOR))	return MOVE_EVENT_STEP;

	return MOVE_EVENT_NOEVENT;
}

// utility function to test if an item can be found in an itemlist
bool SokobanGame::IsItemInItemList(LevelItemList Items, int ItemType)
{
	// loop all items in list
	for (unsigned int indx = 0; indx < Items.size(); indx++)
	{
		// compare current item type to query item type
		if (Items[indx].ItemType == ItemType)
		{
			// return at first instance of object
			return true;
		}

	}

	// query item type not found in list
	return false;
}



// Return to the game from the menu
void SokobanGame::ReturnToGame(void)
{
	GameState = GAMESTATE_INGAME;
}

// Cycle between the different camera views
void SokobanGame::CycleCameraView(void)
{
	m_CurrentCamera++;

	if (m_CurrentCamera > 2)
	{
		m_CurrentCamera = 0;
	}

	switch(m_CurrentCamera)
	{
	    case 0:
			// front on
			g_camera->PositionCamera(-10.7881f, 17.5287f, 10.1314f, -4.63461f, 11.6867f, 10.2102f, 0.0f, 1.0f, 0.0f);
	        break;
		case 1:
			// diagonal
			g_camera->PositionCamera(-6.93121f, 11.8041f, 23.4819f, -1.54504f, 6.91266f, 19.1156f, 0.0f, 1.0f, 0.0f);
			break;
		case 2:
			// overhead
			g_camera->PositionCamera(-2.22679f, 24.7401f, 9.30774f, 1.04169f, 16.9095f, 9.31688f, 0.0f, 1.0f, 0.0f);
			break;
	}



}

