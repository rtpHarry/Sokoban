#include <windows.h>
#include "GLee.h"
//#include <gl/GL.h>
#include <sstream>
using namespace std;

#include "TextureCache.h"

#include "Vector3.h"
#include "Timer.h"
#include "FontGL.h"
#include "NeHeGL.h"

#include ".\sokobanhud.h"

SokobanHUD::SokobanHUD(void)
{
}

SokobanHUD::~SokobanHUD(void)
{
}

// Setup the HUD sub system
void SokobanHUD::Setup(void)
{
	// setup HUD
	//////////////////////////////////////////////////////////////////////////
	m_LogoTexID = TextureCache::Instance().LoadTexture(".\\data\\logo.png");
	m_RTPSoftwareTexID = TextureCache::Instance().LoadTexture(".\\data\\rtpsoftware.png");
	m_HUDBgTexID = TextureCache::Instance().LoadTexture(".\\data\\hud-bg.png");
	m_LvlDoneBgTexID = TextureCache::Instance().LoadTexture(".\\data\\lvldone-bg.png");
}

// convenience function to render a texture in ortho mode
void SokobanHUD::Util_DrawTexture(int TextureID, float Alpha, float OffsetX, float OffsetY, float SizeX, float SizeY)
{
	Util_DrawTextureC(TextureID, Alpha, OffsetX, OffsetY, SizeX, SizeY, CVector3(1.0f, 1.0f, 1.0f));
}

// convenience function to render a texture in ortho mode
void SokobanHUD::Util_DrawTextureC(int TextureID, float Alpha, float OffsetX, float OffsetY, float SizeX, float SizeY, CVector3 Color)
{
	// handle lighting
	GLboolean bWasLightingOn = glIsEnabled(GL_LIGHTING);
	glDisable(GL_LIGHTING);

	//
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	//glDisable(GL_CULL_FACE);
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

	// handle lighting
	if (bWasLightingOn) { glEnable(GL_LIGHTING); }
}


// Draw the game logo
void SokobanHUD::DrawLogo(void)
{
	Util_DrawTexture(m_LogoTexID, 1, 500, 600, 512, 128);
}


// Draw the level information
void SokobanHUD::DrawLevelInfo(int MoveCount, int CratesQuota, int CratesTagged, int HighScore)
{
	// display textures
	//////////////////////////////////////////////////////////////////////////
	// draw hud background
	Util_DrawTexture(m_HUDBgTexID, 0.9f, 0, 0, (float)g_window->init.width, 64);

	// draw mini logo
	Util_DrawTexture(m_LogoTexID, 1, 370, 25, 256, 64);

	// draw rtp logo
	Util_DrawTexture(m_RTPSoftwareTexID, 1, 520, 17, 128, 32);

	// build stats strings
	//////////////////////////////////////////////////////////////////////////
	ostringstream NumberOfMoves;
	NumberOfMoves << "Your Score : " << MoveCount;

	ostringstream CrateStatus;
	CrateStatus << "Crates Left : " << CratesQuota - CratesTagged
		<< "/" << CratesQuota;

	ostringstream HighscoreThisLevel;
	HighscoreThisLevel << "Best Score : " << HighScore;

	// display stats strings
	//////////////////////////////////////////////////////////////////////////
	FontGL Font;

//	if(GameState == GAMESTATE_LEVELCOMPLETE)
//	{		glColor3ub(152, 11, 21);	}	// red
//	else
//	{		glColor3ub(15,26,93);  		}	// blue
	glColor3ub(15,26,93);
	Font.Print(4,24+2,CrateStatus.str().c_str());

	// highscore
	glColor3ub(15,26,93);
	Font.Print(680,24*1+2,HighscoreThisLevel.str().c_str());

	// your score
	glColor3ub(15,26,93);
	Font.Print(680,2, NumberOfMoves.str().c_str());

}

// Draw the fps
void SokobanHUD::DrawFPS(void)
{
	//stringstream ss(Timer.GetFPS());
	//	string fps = "FPS : ";
	//	fps.insert(fps.end(), Timer.GetFPS());
	//	fps += Timer.GetFPS()

	//ss >> fps;

	static char strFrameRate[50] = {0};			// We will store the string here for the window title
	CTimer Timer;

	// Copy the frames per second into a string to display in the window title bar
	sprintf_s(strFrameRate, "Current Frames Per Second: %d", int(Timer.GetFPS()));

	// Set the window title bar to our string
	SetWindowText(g_window->hWnd, strFrameRate);


	//	glColor3ub(15,26,93);
	//	FontGL Font;
	//	Font.Print(4,24*5+2, fps.c_str());

}

// Draw level complete
void SokobanHUD::DrawLevelComplete(void)
{
	// beep briefly
	//Beep(20000, 1);
	
	// draw the background
	Util_DrawTexture(m_LvlDoneBgTexID, 1, 300, 312, 512, 256);

	// just a normal level completion
	FontGL Font;
	glColor3ub(248, 218, 17); // yellow
	Font.Print(332, (g_window->init.width/2), "Congratulations");
	glColor3f(1.0f,1.0f,1.0f);
	Font.Print(332, (g_window->init.width/2)-32, "You Completed The Level!");
	Font.Print(332, (g_window->init.width/2)-128, "Press SPACE to continue!");

	return;
}


// Draw episode complete
void SokobanHUD::DrawEpisodeComplete(void)
{
	// draw the background
	Util_DrawTexture(m_LvlDoneBgTexID, 1, 300, 312, 512, 256);

	// display last level of episode message
	FontGL Font;
	glColor3ub(248, 218, 17); // yellow
	Font.Print(332, (g_window->init.width/2), "Congratulations");
	glColor3f(1.0f,1.0f,1.0f);
	Font.Print(332, (g_window->init.width/2)-32, "You Completed All The");
	Font.Print(332, (g_window->init.width/2)-64, "Levels In This Episode!");
	Font.Print(332, (g_window->init.width/2)-128, "Press SPACE to continue!");

	return;
}

// Draw game complete
void SokobanHUD::DrawGameComplete(void)
{
	// draw the background
	Util_DrawTexture(m_LvlDoneBgTexID, 1, 300, 312, 512, 256);

	// display last level of episode message
	glColor3f(1.0f,1.0f,1.0f);		

	FontGL Font;
	glColor3ub(248, 218, 17); // yellow
	Font.Print(332, (g_window->init.width/2), "Congratulations");
	glColor3f(1.0f,1.0f,1.0f);
	Font.Print(332, (g_window->init.width/2)-32, "You Have Completed");
	Font.Print(332, (g_window->init.width/2)-64, "!!THE ENTIRE GAME!!");
	Font.Print(332, (g_window->init.width/2)-128, "Press SPACE to continue!");

	return;
}