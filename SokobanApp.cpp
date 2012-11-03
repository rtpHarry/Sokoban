#include <windows.h>
#include "GLee.h"
//#include <gl/gl.h>
#include <il/il.h>
#include <il/ilut.h>

#include <assert.h>

#include ".\sokobanapp.h"

#include "FontGL.h"
#include "NeHeGL.h"		// for g_window

SokobanApp::SokobanApp(void)
{
}

SokobanApp::~SokobanApp(void)
{
}

void SokobanApp::Setup(void)
{
	// set initial appstate
	AppState = APPSTATE_DEMOLOOP;

	// setup initial camera position
	//////////////////////////////////////////////////////////////////////////
	g_camera->PositionCamera(-13.4413f, 13.869f, 10.1687f, -6.06266f, 9.67945f, 10.1082f, 0.0f, 1.0f, 0.0f);

	// setup image library
	//////////////////////////////////////////////////////////////////////////
	// Check if the shared lib's version matches the executable's version.
	if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION ||
		ilGetInteger(ILU_VERSION_NUM) < ILU_VERSION ||
		ilGetInteger(ILUT_VERSION_NUM) < ILUT_VERSION)
	{
		MessageBox (HWND_DESKTOP, "Your copy of DevIL Image Library is too old! Get a new one at www.imagelib.org", "Error", MB_OK | MB_ICONEXCLAMATION);	
	}

	// Needed to initialize DevIL.
	ilInit();
	ilutInit();
	// GL cannot use palettes anyway, so convert early.
	ilEnable(IL_CONV_PAL);
	// Gets rid of dithering on some nVidia-based cards.
	ilutEnable(ILUT_OPENGL_CONV);
	// Lets ILUT know to use its OpenGL functions.
	ilutRenderer(ILUT_OPENGL);

	// setup audio subsystem
	//////////////////////////////////////////////////////////////////////////
	SokobanSoundManager &SoundCache = SokobanSoundManager::Instance();
	SoundCache.Setup();

	// setup font
	//////////////////////////////////////////////////////////////////////////
	FontGL Font;
	Font.SetupFonts();

	// setup the menu
	//////////////////////////////////////////////////////////////////////////
	MenuManager.Setup();

	// setup the game
	//////////////////////////////////////////////////////////////////////////
	GameManager.Setup();

}

void SokobanApp::Destroy(void)
{
	// shut down the game
	GameManager.Destroy();

	// destroy audio subsystem
	//////////////////////////////////////////////////////////////////////////


	// un-setup font
	//////////////////////////////////////////////////////////////////////////
	FontGL Font;
	Font.DestroyFonts();

}

void SokobanApp::Render(void)
{
	// update timer
	Timer.Tick();

	switch(AppState)
	{
	case APPSTATE_DEMOLOOP:
	case APPSTATE_INGAMEMENU:
		GameManager.Render();		// also render to maintain level visible thru back
		MenuManager.Render();
		break;

	case APPSTATE_GAMEPLAYING:
		GameManager.Render();
		break;
	}


}

void SokobanApp::KeyPressed(char WhatKey)
{
	switch(AppState)
	{
	    case APPSTATE_DEMOLOOP:
		case APPSTATE_INGAMEMENU:
			KeyPressed_Menu(WhatKey);
			break;

		case APPSTATE_GAMEPLAYING:
			KeyPressed_Game(WhatKey);
			break;

	}

	// some keys always want processing
	switch(WhatKey)
	{
	case VK_F8:
		TakeScreenshot();
		break;
	}

}

// Key pressed while app is in the menu
void SokobanApp::KeyPressed_Menu(char WhatKey)
{
	SokobanMenuState ReturnedState;
	ReturnedState = MenuManager.KeyPressed(WhatKey);

	switch(ReturnedState)
	{
	    case MENUSTATE_NEWGAME:
			// start a new game
			GameManager.StartNewGame();
			AppState = APPSTATE_GAMEPLAYING;
	        break;
//		case MENUSTATE_INSTRUCTIONS:
//			// TODO add instructions page
//			break;
//		case MENUSTATE_ABOUT:
//			// TODO add about page
//			break;
		case MENUSTATE_QUIT:
			// terminate game
			TerminateApplication (g_window);
			break;
		case MENUSTATE_ESCAPEPRESSED:
			// return to game, if playing one
			if (AppState == APPSTATE_INGAMEMENU)
			{
				GameManager.ReturnToGame();
				AppState = APPSTATE_GAMEPLAYING;
			}
			break;
	}
}

// Process a key that was pressed in game
void SokobanApp::KeyPressed_Game(char WhatKey)
{
	SokobanGameState ReturnedState;
	ReturnedState = GameManager.KeyPressed(WhatKey);

	switch(ReturnedState)
	{
		case GAMESTATE_DEMOLOOP:
			AppState = APPSTATE_DEMOLOOP;
			break;
		case GAMESTATE_INGAME:
			AppState = APPSTATE_GAMEPLAYING;
			break;
		case GAMESTATE_INMENU:
			AppState = APPSTATE_INGAMEMENU;
			break;
		case GAMESTATE_LEVELCOMPLETE:			// doesnt really care about LEVELCOMPLETE
			AppState = APPSTATE_GAMEPLAYING;
			break;
	}

}

// Take a screenshot and save it to file
void SokobanApp::TakeScreenshot(void)
{
	ILuint ImgId;

	// Generate the main image name to use.
	ilGenImages(1, &ImgId);
	// Bind this image name.
	ilBindImage(ImgId);
	// Take screenshot
	ilutGLScreenie();
	// delete image
	ilDeleteImages(1, &ImgId);

}