#include ".\theme.h"

#include "GLee.h"
//#include <Windows.h>
//#include <gl/GL.h>

Theme::Theme(void)
{
	// set initial directory for theme resources
	m_sBaseDirectory = ".\\themes\\";
}

Theme::~Theme(void)
{
}

//////////////////////////////////////////////////////////////////////////
// Concrete functions
//////////////////////////////////////////////////////////////////////////

// Draw an Axis
void Theme::DisplayAxis(float length)
{
	GLboolean bWasLightingOn = glIsEnabled(GL_LIGHTING);
	GLboolean bWasTexturesOn = glIsEnabled(GL_TEXTURE_2D);
        
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	// Red Axis from Origin to Positive X
	glPushMatrix();
		glPushAttrib(GL_COLOR);
		glColor3f(0.8f,0.0f,0.0f);
		glLineWidth(8);
		glBegin(GL_LINES);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(length, 0.0, 0.0);
		glEnd();
	glPopMatrix();

	// Green Axis from Origin to Positive Y
	glPushMatrix();
		glPushAttrib(GL_COLOR);
		glColor3f(0.0f,0.8f,0.0f);
		glLineWidth(8);
		glBegin(GL_LINES);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(0.0, length, 0.0);
		glEnd();
	glPopMatrix();

	// Blue Axis from Origin to Positive Z
	glPushMatrix();
		glPushAttrib(GL_COLOR);
		glColor3f(0.0f,0.0f,0.8f); // light red axis in positive y
		glLineWidth(8);
		glBegin(GL_LINES);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(0.0, 0.0, length);
		glEnd();
	glPopMatrix();

	if (bWasLightingOn) glEnable(GL_LIGHTING);
	if (bWasTexturesOn) glEnable(GL_TEXTURE_2D);
}


//////////////////////////////////////////////////////////////////////////
// Abstract Functions
//////////////////////////////////////////////////////////////////////////

// setup any theme related resources
void Theme::SetupTheme(void)
{

}

// un-setup any theme related resources
void Theme::DestroyTheme(void)
{

}

// Operations before the scene has been rendered
void Theme::PreRender(void)
{

}

// Operations after the scene has been rendered
void Theme::PostRender(void)
{

}

// Render the floor tile
void Theme::RenderTileFloor(float X, float Y)
{
}

// Render the wall tile
void Theme::RenderTileWall(float X, float Y)
{
}

// Render the void tile
void Theme::RenderTileVoid(float X, float Y)
{
}

// Render the void tile
void Theme::RenderItemTarget(float X, float Y)
{
}

// Render the void tile
void Theme::RenderItemCrate(float X, float Y)
{
}

// Render the void tile
void Theme::RenderItemPlayer(float X, float Y)
{
}

// Render the surrounding scene
void Theme::RenderSurroundingScene(float X, float Y, float Z, float fLevelWidth)
{
}
