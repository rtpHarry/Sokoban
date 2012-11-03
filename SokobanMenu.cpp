#include <Windows.h>
#include <assert.h>
#include <sstream>

#include "NeHeGL.h"		// for g_window
#include "FontGL.h"

#include "TextureCache.h"
#include "SokobanSoundManager.h"
#include "SokobanLevelManager.h"

#include "SokobanMenu.h"


SokobanMenu::SokobanMenu(void)
{
	m_CurrentSelection = 0;
}

SokobanMenu::~SokobanMenu(void)
{
}

// Render the menu
void SokobanMenu::Render(void)
{
	switch(m_ActiveMenu)
	{
		case ACTIVEMENU_NEWGAME:
			Render_EpisodeSelect();
			break;
		case ACTIVEMENU_MAINMENU:
			Render_MainMenu();
			break;
		case ACTIVEMENU_INSTRUCTIONS:
			Render_Instructions();
			break;
		case ACTIVEMENU_ABOUT:
			Render_About();
			break;
	}
}

// Render the Main Menu
void SokobanMenu::Render_MainMenu(void)
{
	// draw menu bg
	Util_DrawTexture(m_MenuBgTexID, 0.9f, 300, 150, 512, 512);

	// draw main logo
	Util_DrawTexture(m_MenuGameLogoTexID, 1, 300, 600, 512, 128);

	// draw highlight
	// offset is (menuheight - (currentselection * selectionheight))
	Util_DrawTexture(m_MenuHighlightTexID, 1, 330, (512 - ((float)m_CurrentSelection * 96)), 64, 64);

	// draw new game option
	Util_DrawTexture(m_MenuNewGameTexID, 1, 380, 512, 384, 64);

	// draw instructions option
	Util_DrawTexture(m_MenuInstructTexID, 1, 380, 416, 384, 64);

	// draw about option
	Util_DrawTexture(m_MenuAboutTexID, 1, 380, 320, 384, 64);

	// draw exit game option
	Util_DrawTexture(m_MenuQuitTexID, 1, 380, 224, 384, 64);
}

// Render Instructions Sub-Menu
void SokobanMenu::Render_Instructions(void)
{
	// draw menu bg
	Util_DrawTexture(m_MenuBgTexID, 0.9f, 64, 32, 896, 640);

	// draw main logo
	Util_DrawTexture(m_MenuGameLogoTexID, 1, 300, 600, 512, 128);

	// draw text
	FontGL Font;
	int BaseHeight = 96;
	int LineHeight = (int)Font.GetMetrics().RenderHeight;
	int BaseMargin = 96;

/*
Arrows - Move Player
Backspace - Undo Move
Insert - Reset Level
F4 - Toggle Fullscreen
F8 - Take Screenshot
ESC - Show Main Menu

HOME/END - Next/Prev Level In This Episode
PGUP/PGDN - Next/Prev Episode In Game
WSAD - Move Camera
F11 - Toggle Mouse Camera Control
F12 - Write the current camera position to file


*/
	// draw instructions
	glColor3f(1.0f,1.0f,0.0f);
	Font.Print(BaseMargin, (LineHeight * 15) + BaseHeight, "The object of the game is simple;");
	glColor3f(1.0f,1.0f,1.0f);
	Font.Print(BaseMargin, (LineHeight * 14) + BaseHeight, "You have to have to push all the crates to");
	Font.Print(BaseMargin, (LineHeight * 13) + BaseHeight, "the destinations using a minimal number of");
	Font.Print(BaseMargin, (LineHeight * 12) + BaseHeight, "pushes.");

	// draw keys
	glColor3f(1.0f,1.0f,0.0f);
	Font.Print(BaseMargin, (LineHeight * 10) + BaseHeight, "Keys:");
	glColor3f(1.0f,1.0f,1.0f);
	Font.Print(BaseMargin, (LineHeight * 9) + BaseHeight, "Arrows - Move Player");
	Font.Print(BaseMargin, (LineHeight * 8) + BaseHeight, "Backspace - Undo Move   Insert - Reset Level");
	Font.Print(BaseMargin, (LineHeight * 7) + BaseHeight, "F4 - Toggle Fullscreen  F8 - Take Screenshot");
	Font.Print(BaseMargin, (LineHeight * 6) + BaseHeight, "F9 - Toggle Music       ESC - Show Main Menu");
	Font.Print(BaseMargin, (LineHeight * 5) + BaseHeight, "");
	Font.Print(BaseMargin, (LineHeight * 4) + BaseHeight, "HOME/END - Next/Prev Level In This Episode");
	Font.Print(BaseMargin, (LineHeight * 3) + BaseHeight, "PGUP/PGDN - Next/Prev Episode In Game");
	Font.Print(BaseMargin, (LineHeight * 2) + BaseHeight, "WSAD - Move Camera");
	Font.Print(BaseMargin, (LineHeight * 1) + BaseHeight, "F11 - Toggle Mouse Camera Control");
	Font.Print(BaseMargin, (LineHeight * 0) + BaseHeight, "F12 - Write the camera position to file");


}


// Render Instructions Sub-Menu
void SokobanMenu::Render_About(void)
{
	// draw menu bg
	Util_DrawTexture(m_MenuBgTexID, 0.9f, 64, 32, 896, 640);

	// draw main logo
	Util_DrawTexture(m_MenuGameLogoTexID, 1, 300, 600, 512, 128);

	// draw text
	FontGL Font;
	int BaseHeight = 96;
	int LineHeight = (int)Font.GetMetrics().RenderHeight;
	int BaseMargin = 96;

	// draw instructions
	glColor3f(1.0f,1.0f,0.0f);
	Font.Print(BaseMargin, (LineHeight * 15) + BaseHeight, "         an rtp|software production       ");
/*	glColor3f(1.0f,1.0f,1.0f);
	Font.Print(BaseMargin, (LineHeight * 14) + BaseHeight, "");
	Font.Print(BaseMargin, (LineHeight * 13) + BaseHeight, "");
	Font.Print(BaseMargin, (LineHeight * 12) + BaseHeight, "");*/

	// draw keys
	glColor3f(1.0f,1.0f,0.0f);
	Font.Print(BaseMargin, (LineHeight * 13) + BaseHeight, "development team members:");
	glColor3f(1.0f,1.0f,1.0f);
//	Font.Print(BaseMargin, (LineHeight * 9) + BaseHeight, "");
	Font.Print(BaseMargin, (LineHeight * 11) + BaseHeight, "     coding, 2d art");
	Font.Print(BaseMargin, (LineHeight * 10) + BaseHeight, "            - matthew harris");
//	Font.Print(BaseMargin, (LineHeight * 6) + BaseHeight, "");
	Font.Print(BaseMargin, (LineHeight * 8) + BaseHeight, "     3d modelling, model skinning");
	Font.Print(BaseMargin, (LineHeight * 7) + BaseHeight, "             - ben parker");
//	Font.Print(BaseMargin, (LineHeight * 3) + BaseHeight, "");
//	Font.Print(BaseMargin, (LineHeight * 2) + BaseHeight, "");
	Font.Print(BaseMargin, (LineHeight * 3) + BaseHeight, "     visit us at www.rtpsoftware.co.uk");
	Font.Print(BaseMargin, (LineHeight * 2) + BaseHeight, "                 www.runtings.com");

	Font.Print(BaseMargin, (LineHeight * 0) + BaseHeight, "             press any key to return");
}

// Allow the user to select a level
void SokobanMenu::Render_EpisodeSelect(void)
{
	// draw menu bg
	Util_DrawTexture(m_MenuBgTexID, 0.9f, 64, 32, 896, 640);

	// draw main logo
	Util_DrawTexture(m_MenuGameLogoTexID, 1, 300, 600, 512, 128);

	// draw text
	FontGL Font;
	int BaseHeight = 96;
	int LineHeight = ((int)Font.GetMetrics().RenderHeight * 3) ;
	int FontHeight = (int)Font.GetMetrics().RenderHeight;
	int BaseMargin = 160;

	// draw tagline
	glColor3f(1.0f,1.0f,0.0f);
	Font.Print(BaseMargin, (LineHeight * 15) + BaseHeight, "         an rtp|software production       ");


	// get the list of levels in this episode
	vector<EpisodeInfo> EpisodeInfoList = SokobanLevelManager::Instance().GetEpisodeInfo();

	// draw list
	int CurrentLine = 0;
	const int LinesAvailable = 5;
	vector<EpisodeInfo>::iterator ii = EpisodeInfoList.begin();
	
	// draw highlight
	// offset is (menuheight - (currentselection * selectionheight))
	Util_DrawTexture(m_MenuHighlightTexID, 1, 96, (LineHeight * (LinesAvailable - EpisodeSelect_SelectedItem)) + BaseHeight - 32, 64, 64);

	do {
		int ThisLinePosition = (LineHeight * (LinesAvailable - CurrentLine)) + BaseHeight;

		glColor3f(1.0f,1.0f,1.0f);
		Font.Print(BaseMargin, ThisLinePosition, (*ii).EpisodeName.c_str());

		// build total levels string
		ostringstream TotalNumberOfLevels;
		TotalNumberOfLevels << "Total Levels: " << (*ii).NumberOfLevels;

		glColor3f(0.25f, 0.2f, 0.1f);
		Font.Print(BaseMargin + 24, ThisLinePosition - FontHeight, TotalNumberOfLevels.str().c_str());

		CurrentLine++;
		ii++;
		
	} while((ii != EpisodeInfoList.end()) && (CurrentLine <= LinesAvailable));
}

// Render Yes/No confirmation dialog
void SokobanMenu::Render_Confirmation_Dialog(ConfirmationType ConfirmType)
{
/*	// draw the background
	Util_DrawTexture(m_LvlDoneBgTexID, 1, 300, 312, 512, 256);

	// just a normal level completion
	FontGL Font;
	glColor3ub(248, 218, 17); // yellow
	Font.Print(332, (g_window->init.width/2), "Are you sure?");
	glColor3f(1.0f,1.0f,1.0f);
	Font.Print(332, (g_window->init.width/2)-32, "Are you sure you want to exit Sokoban?");
	Font.Print(332, (g_window->init.width/2)-128, "Yes");
	Font.Print(332, (g_window->init.width/2)-128, "No");*/
}

SokobanMenuState SokobanMenu::KeyPressed(char WhatKey)
{
	SokobanMenuState ReturnState;

	switch(m_ActiveMenu)
	{
	    case ACTIVEMENU_MAINMENU:
			ReturnState = KeyPressed_MainMenu(WhatKey);
	        break;
		case ACTIVEMENU_NEWGAME:
			ReturnState = KeyPressed_NewGame(WhatKey);
			break;
		case ACTIVEMENU_INSTRUCTIONS:
			ReturnState = KeyPressed_Instructions(WhatKey);
			break;
		case ACTIVEMENU_ABOUT:
			ReturnState = KeyPressed_About(WhatKey);
			break;
		default:
			ReturnState = MENUSTATE_NOSELECTIONMADE;
			assert(0 && "SokobanMenu::KeyPressed() : did not evaluate any active menu");
			break;
	}

	return ReturnState;
}


// Key pressed while active menu is Main Menu
SokobanMenuState SokobanMenu::KeyPressed_MainMenu(char WhatKey)
{
	if (WhatKey == VK_ESCAPE)
	{
		SokobanSoundManager::Instance().PlaySample(MENU_EVENT_CLOSEMENU);
		return MENUSTATE_ESCAPEPRESSED;
	}

	if (WhatKey == VK_RETURN)
	{
		// check what menu item is currently selected
		switch(m_CurrentSelection)
		{
		case 0:
			SokobanSoundManager::Instance().PlaySample(MENU_EVENT_SELECTMENU);
			m_ActiveMenu = ACTIVEMENU_NEWGAME;
			return MENUSTATE_NOSELECTIONMADE;
			break;
		case 1: 
			SokobanSoundManager::Instance().PlaySample(MENU_EVENT_SELECTMENU);
			m_ActiveMenu = ACTIVEMENU_INSTRUCTIONS;
			return MENUSTATE_NOSELECTIONMADE;
			break;
		case 2: 
			SokobanSoundManager::Instance().PlaySample(MENU_EVENT_SELECTMENU);
			m_ActiveMenu = ACTIVEMENU_ABOUT;
			return MENUSTATE_NOSELECTIONMADE;
			break;
		case 3:
			// TODO : when yes/no confirm added remove this so box can make its own sound
			SokobanSoundManager::Instance().PlaySample(MENU_EVENT_SELECTMENU);
			return MENUSTATE_QUIT;
			break;
		}

		assert(true);	// should never get here
	}

	// handle up key
	if ((WhatKey == VK_UP) || (WhatKey == VK_LEFT))
	{
		SokobanSoundManager::Instance().PlaySample(MENU_EVENT_SCROLLUP);

		m_CurrentSelection--;

		if (m_CurrentSelection < 0)	{ m_CurrentSelection = 3; }  // clamp
	}

	// handle down key
	if ((WhatKey == VK_DOWN) || (WhatKey == VK_RIGHT))
	{
		SokobanSoundManager::Instance().PlaySample(MENU_EVENT_SCROLLDOWN);

		m_CurrentSelection++;

		if (m_CurrentSelection > 3) { m_CurrentSelection = 0; }	// clamp
	}

	return MENUSTATE_NOSELECTIONMADE;
}


// Key pressed while active menu is Instructions
SokobanMenuState SokobanMenu::KeyPressed_Instructions(char WhatKey)
{
//
//	if (WhatKey == VK_ESCAPE)
//	{	  
//		m_ActiveMenu = ACTIVEMENU_MAINMENU;
//	}

	// anykey
	m_ActiveMenu = ACTIVEMENU_MAINMENU;

	return MENUSTATE_NOSELECTIONMADE;
}


// Key pressed while active menu is Instructions
SokobanMenuState SokobanMenu::KeyPressed_About(char WhatKey)
{
	// anykey
	m_ActiveMenu = ACTIVEMENU_MAINMENU;

	return MENUSTATE_NOSELECTIONMADE;
}


// Key pressed in level selection menu
SokobanMenuState SokobanMenu::KeyPressed_NewGame(char WhatKey)
{
	if (WhatKey == VK_UP)
	{
		if (EpisodeSelect_SelectedItem > 0) {
			SokobanSoundManager::Instance().PlaySample(MENU_EVENT_SCROLLUP);
			EpisodeSelect_SelectedItem--;
		}
		return MENUSTATE_NOSELECTIONMADE;
	}
	if (WhatKey == VK_DOWN)
	{
		if (EpisodeSelect_SelectedItem < (SokobanLevelManager::Instance().GetActiveEpisodeTotal())) {
			SokobanSoundManager::Instance().PlaySample(MENU_EVENT_SCROLLDOWN);
			EpisodeSelect_SelectedItem++;
		}
		
		return MENUSTATE_NOSELECTIONMADE;
	}

	if (WhatKey == VK_ESCAPE)
	{
		SokobanSoundManager::Instance().PlaySample(MENU_EVENT_CLOSEMENU);
		m_ActiveMenu = ACTIVEMENU_MAINMENU;
		return MENUSTATE_NOSELECTIONMADE;
	}

	if (WhatKey == VK_RETURN)
	{
		SokobanSoundManager::Instance().PlaySample(MENU_EVENT_SELECTMENU);
		SokobanLevelManager::Instance().SetActiveEpisode(EpisodeSelect_SelectedItem);
		m_ActiveMenu = ACTIVEMENU_MAINMENU;
		return MENUSTATE_NEWGAME;
	}

	return MENUSTATE_NOSELECTIONMADE;
}


// Load the resources that the menu needs to display
void SokobanMenu::Setup(void)
{
	// dirty hack because i didnt abstract the menu class enough:
	EpisodeSelect_SelectedItem = 0;

	// setup menu resources
	//////////////////////////////////////////////////////////////////////////
	m_MenuGameLogoTexID = TextureCache::Instance().LoadTexture(".\\data\\logo.png");
	m_RTPSoftwareLogoTexID = TextureCache::Instance().LoadTexture(".\\data\\rtpsoftware.png");
	m_DialogBoxBgTexID = TextureCache::Instance().LoadTexture(".\\data\\lvldone-bg.png");
	m_MenuBgTexID = TextureCache::Instance().LoadTexture(".\\data\\menu-bg.png");
	m_MenuHighlightTexID = TextureCache::Instance().LoadTexture(".\\data\\menu-highlight.png");
	m_MenuNewGameTexID = TextureCache::Instance().LoadTexture(".\\data\\menu-newgame.png");
	m_MenuInstructTexID = TextureCache::Instance().LoadTexture(".\\data\\menu-instructions.png");
	m_MenuAboutTexID = TextureCache::Instance().LoadTexture(".\\data\\menu-about.png");
	m_MenuQuitTexID = TextureCache::Instance().LoadTexture(".\\data\\menu-quit.png");

	//
	m_ActiveMenu = ACTIVEMENU_MAINMENU; // main menu
	m_CurrentSelection = 0; // new game

	// setup sound
	SokobanSoundManager &SoundMgr = SokobanSoundManager::Instance();

	SoundMgr.CacheSampleFromFile(MENU_EVENT_SCROLLUP, ".\\audio\\menu\\menu_scroll.wav");
	SoundMgr.CacheSampleFromFile(MENU_EVENT_SCROLLDOWN, ".\\audio\\menu\\menu_scroll.wav");
	//SoundMgr.CacheSampleFromFile(MENU_EVENT_SELECTMENU, ".\\audio\\menu\\.wav");
	//SoundMgr.CacheSampleFromFile(MENU_EVENT_PREVIOUSMENU, ".\\audio\\menu\\.wav");
	//SoundMgr.CacheSampleFromFile(MENU_EVENT_OPENMENU, ".\\audio\\menu\\.wav");
	//SoundMgr.CacheSampleFromFile(MENU_EVENT_CLOSEMENU, ".\\audio\\menu\\.wav");

}

// convenience function to render a texture in ortho mode
void SokobanMenu::Util_DrawTexture(int TextureID, float Alpha, float OffsetX, float OffsetY, float SizeX, float SizeY)
{
	Util_DrawTextureC(TextureID, Alpha, OffsetX, OffsetY, SizeX, SizeY, CVector3(1.0f, 1.0f, 1.0f));
}

// convenience function to render a texture in ortho mode
void SokobanMenu::Util_DrawTextureC(int TextureID, float Alpha, float OffsetX, float OffsetY, float SizeX, float SizeY, CVector3 Color)
{
	// handle lighting
	GLboolean bWasLightingOn = glIsEnabled(GL_LIGHTING);
	glDisable(GL_LIGHTING);

	//
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D, TextureID);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0,g_window->init.width,0,g_window->init.height,-1,1);	// Set Up An Ortho Screen
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();	
	glLoadIdentity();

	glTranslatef(OffsetX,OffsetY,0);								// Position The Text (0,0 - Bottom Left)

	glColor4f(Color.x, Color.y, Color.z, Alpha);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f);	glVertex2f(0, SizeY);
		glTexCoord2f(0.0f, 0.0f);	glVertex2f(0, 0);
		glTexCoord2f(1.0f, 0.0f);	glVertex2f(SizeX, 0);
		glTexCoord2f(1.0f, 1.0f);	glVertex2f(SizeX, SizeY);
	glEnd();	

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPopMatrix();										// Restore The Old Projection Matrix

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	if (bWasLightingOn) { glEnable(GL_LIGHTING); }
}