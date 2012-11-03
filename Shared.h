#pragma once

struct SharedArtResources
{
	GLuint SharedGameLogoID;
	GLuint SharedRTPLogoID;
	GLuint SharedDialogBgID;
};

enum MenuEvent
{
	MENU_EVENT_SCROLLUP,			// scroll up the list
	MENU_EVENT_SCROLLDOWN,			// scroll down the list
	MENU_EVENT_SELECTMENU,			// select an item (press enter on it)
	MENU_EVENT_PREVIOUSMENU,		// go back from a menu
	MENU_EVENT_OPENMENU,			// open the menu from the game
	MENU_EVENT_CLOSEMENU,			// go back from top menu, back into game
};

enum GameEvent
{
	GAME_EVENT_LEVELCOMPLETE,	// level completed
	GAME_EVENT_EPISODECOMPLETE,	// episode completed
	GAME_EVENT_GAMECOMPLETE,		// all levels completed
};
