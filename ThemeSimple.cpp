#include ".\themesimple.h"

#include "GLee.h"
//#include <Windows.h>
//#include <gl/GL.h>
#include <gl/GLU.h>

ThemeSimple::ThemeSimple(void)
{
	m_fTileOffsetGap = 2.2f;
	m_sThemeName = "Simple";
}

ThemeSimple::~ThemeSimple(void)
{
}

// setup any theme related resources
void ThemeSimple::SetupTheme(void)
{
}

// un-setup any theme related resources
void ThemeSimple::DestroyTheme(void)
{
}

// Operations before the scene has been rendered
void ThemeSimple::PreRender(void)
{
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
}

// Operations after the scene has been rendered
void ThemeSimple::PostRender(void)
{
	DisplayAxis(30);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);

}

// Render the floor tile
void ThemeSimple::RenderTileFloor(float X, float Y)
{
	X = (X + 1.0f) * m_fTileOffsetGap;
	Y = (Y + 1.0f) * m_fTileOffsetGap;
	float Z = 0.0f;

	glPushMatrix();	
	glTranslatef(X, Z, Y);								//
	glColor3f(1.0f,1.0f,1.0f);							// white
	glBegin(GL_QUADS);									// 
	glVertex3f( 1.0f, 0.0f,-1.0f);						// Bottom Right
	glVertex3f(-1.0f, 0.0f,-1.0f);						// Bottom Left
	glVertex3f(-1.0f, 0.0f, 1.0f);						// Top Left
	glVertex3f( 1.0f, 0.0f, 1.0f);						// Top Right
	glEnd();											// 
	glPopMatrix();


}

// Render the wall tile
void ThemeSimple::RenderTileWall(float X, float Y)
{
	X = (X + 1.0f) * m_fTileOffsetGap;
	Y = (Y + 1.0f) * m_fTileOffsetGap;
	float Z = 0.0f;

	glPushMatrix();	
	glTranslatef(X, Z, Y);								//
	glColor3f(0.5f,0.5f,1.0f);							// blue
	glBegin(GL_QUADS);									// 
	glVertex3f( 1.0f, 0.0f,-1.0f);						// Bottom Right
	glVertex3f(-1.0f, 0.0f,-1.0f);						// Bottom Left
	glVertex3f(-1.0f, 0.0f, 1.0f);						// Top Left
	glVertex3f( 1.0f, 0.0f, 1.0f);						// Top Right
	glEnd();											// 
	glPopMatrix();


}

// Render the void tile
void ThemeSimple::RenderTileVoid(float X, float Y)
{
	X = (X + 1.0f) * m_fTileOffsetGap;
	Y = (Y + 1.0f) * m_fTileOffsetGap;
	float Z = 0.0f;

	glPushMatrix();	
	glTranslatef(X, Z, Y);								//
	glColor3f(0.2f,0.8f,0.0f);							// green
	glBegin(GL_QUADS);									// 
	glVertex3f( 1.0f, 0.0f,-1.0f);						// Bottom Right
	glVertex3f(-1.0f, 0.0f,-1.0f);						// Bottom Left
	glVertex3f(-1.0f, 0.0f, 1.0f);						// Top Left
	glVertex3f( 1.0f, 0.0f, 1.0f);						// Top Right
	glEnd();											// 
	glPopMatrix();


}

// Render the void tile
void ThemeSimple::RenderItemTarget(float X, float Y)
{
	X = (X + 1.0f) * m_fTileOffsetGap;
	Y = (Y + 1.0f) * m_fTileOffsetGap;
	float Z = 0.0002f;

	glPushMatrix();	
	glTranslatef(X, Z, Y);								//
	glColor3f(0.2f, 1.0f, 0.2f);						// light green
	glScalef(0.85f, 0.85f, 0.85f);

	glBegin(GL_QUADS);									// 
	glVertex3f( 1.0f, 0.0f,-1.0f);						// Bottom Right
	glVertex3f(-1.0f, 0.0f,-1.0f);						// Bottom Left
	glVertex3f(-1.0f, 0.0f, 1.0f);						// Top Left
	glVertex3f( 1.0f, 0.0f, 1.0f);						// Top Right
	glEnd();											// 
	glPopMatrix();


}

// Render the void tile
void ThemeSimple::RenderItemCrate(float X, float Y)
{
	X = (X + 1.0f) * m_fTileOffsetGap;
	Y = (Y + 1.0f) * m_fTileOffsetGap;
	float Z = 0.25f;

	glPushMatrix();	
	glTranslatef(X, Z, Y);								//
	glColor3f(1.0f,1.0f,0.0f);							// yellow
	glScalef(0.5f, 0.5f, 0.5f);							// half size

	glBegin(GL_QUADS);									// 
	glVertex3f( 1.0f, 0.0f,-1.0f);						// Bottom Right
	glVertex3f(-1.0f, 0.0f,-1.0f);						// Bottom Left
	glVertex3f(-1.0f, 0.0f, 1.0f);						// Top Left
	glVertex3f( 1.0f, 0.0f, 1.0f);						// Top Right
	glEnd();											// 
	glPopMatrix();

}

// Render the void tile
void ThemeSimple::RenderItemPlayer(float X, float Y)
{
	static GLUquadricObj* PlayerSphere = gluNewQuadric();

	X = (X + 1.0f) * m_fTileOffsetGap;
	Y = (Y + 1.0f) * m_fTileOffsetGap;
	float Z = 0.5f;

	glEnable(GL_LIGHTING);

	glPushMatrix();
	glTranslatef(X, Z, Y);								//
	glColor3f(0.5f, 0.5f, 0.5f);						// light grey
	
	// Draw a sphere using GLU quadric object.	Radius = 0.85		Slices = 8		Stacks = 8
	gluSphere(PlayerSphere, 0.85, 8, 8);

	glPopMatrix();

	glDisable(GL_LIGHTING);


}

// Render the surrounding scene
void ThemeSimple::RenderSurroundingScene(float X, float Y, float Z, float fLevelWidth)
{

}
