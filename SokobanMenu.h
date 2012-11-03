#pragma once

//#include "SokobanApp.h"		// for appstate
#include "Vector3.h"

enum SokobanMenuState
{
	MENUSTATE_NOSELECTIONMADE,
	MENUSTATE_ESCAPEPRESSED,
	MENUSTATE_NEWGAME,
	MENUSTATE_QUIT
};

enum ActiveMenu
{
	ACTIVEMENU_MAINMENU,
	ACTIVEMENU_NEWGAME,
	ACTIVEMENU_INSTRUCTIONS,
	ACTIVEMENU_ABOUT,
	ACTIVEMENU_QUIT
};

enum ConfirmationType
{
	CONFIRMATIONTYPE_QUITGAME,
	CONFIRMATIONTYPE_NEWGAMEWHILEPLAYING
};

class SokobanMenu
{
public:
	SokobanMenu(void);
	~SokobanMenu(void);

private:
	// texture ids
	GLuint m_MenuGameLogoTexID;			// sokoban logo (shared resource)
	GLuint m_RTPSoftwareLogoTexID;		// rtpSoftware logo (shared resource)
	GLuint m_MenuBgTexID;				// menu background
	GLuint m_MenuHighlightTexID;		// menu selector
	GLuint m_MenuNewGameTexID;			// menu item - new game
	GLuint m_MenuInstructTexID;			// menu item - instructions
	GLuint m_MenuAboutTexID;			// menu item - about
	GLuint m_MenuQuitTexID;				// menu item - quit
	GLuint m_DialogBoxBgTexID;			// dialog background (shared resource)

	int m_CurrentSelection;				// currently selected menu item
	int m_ActiveMenu;					// currently active menu

	int EpisodeSelect_SelectedItem;

public:
	// Load the resources that the menu needs to display
	void Setup(void);

	// Render the menu
	void Render(void);

	// Handle key presses when it has focus
	SokobanMenuState KeyPressed(char WhatKey);

private:
	// convenience function to render a texture in ortho mode
	void Util_DrawTexture(int TextureID, float Alpha, float OffsetX, float OffsetY, float SizeX, float SizeY);
	void Util_DrawTextureC(int TextureID, float Alpha, float OffsetX, float OffsetY, float SizeX, float SizeY, CVector3 Color);

public:
	// Render the Main Menu
	void Render_MainMenu(void);
	// Render Instructions Sub-Menu
	void Render_Instructions(void);
	// Render About Sub-Menu
	void Render_About(void);
	// Render Yes/No confirmation dialog
	void Render_Confirmation_Dialog(ConfirmationType ConfirmType);
	// Allow the user to select a level
	void Render_EpisodeSelect(void);
	// Key pressed while active menu is Main Menu
	SokobanMenuState KeyPressed_MainMenu(char WhatKey);
	// Key pressed while active menu is Instructions
	SokobanMenuState KeyPressed_Instructions(char WhatKey);
	// Key pressed while active menu is About
	SokobanMenuState KeyPressed_About(char WhatKey);
	// Key in New Game menu (level select)
	SokobanMenuState KeyPressed_NewGame(char WhatKey);
};
