#include "ThemeDefault.h"

//#include <Windows.h>
//#include <gl/GL.h>
#include "GLee.h"
#include <gl/GLU.h>

#include <IL/il.h>
#include <IL/ilut.h>

#include "NeHeGL.h"					// for g_window

ThemeDefault::ThemeDefault(void)
{
	m_fTileOffsetGap = 2.2f;
	m_sThemeName = "Default";
}

ThemeDefault::~ThemeDefault(void)
{
}

// setup any theme related resources
void ThemeDefault::SetupTheme(void)
{
	// crate
	m_CrateModel.LoadModel("crate1.3ds", (char *)GetFullAssetDirectory().c_str());

	// wall
	m_WallModel.LoadModel("5x5wall.3ds", (char *)GetFullAssetDirectory().c_str());

	// floor
	m_FloorModel.LoadModel("floor1.3ds", (char *)GetFullAssetDirectory().c_str());

	// sky box
	m_SkyboxModel.LoadModel("skysphere.3ds", (char *)GetFullAssetDirectory().c_str());
}

// un-setup any theme related resources
void ThemeDefault::DestroyTheme(void)
{
	// crate
//	glDeleteTextures(1, &m_CrateTextureID);
}

// Operations before the scene has been rendered
void ThemeDefault::PreRender(void)
{
	//glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
}

// Operations after the scene has been rendered
void ThemeDefault::PostRender(void)
{
	// DisplayAxis();

	//glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);

}

// Render the floor tile
void ThemeDefault::RenderTileFloor(float X, float Y)
{
	X = (X + 1.0f) * m_fTileOffsetGap;
	Y = (Y + 1.0f) * m_fTileOffsetGap;
	float Z = 0.0f;

	//glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);

	glPushMatrix();	
	glTranslatef(X, Z, Y);								//
	glColor3f(1.0f,1.0f,1.0f);							// white

	//m_FloorModel.RenderModel();

	glBegin(GL_QUADS);									// 
	glVertex3f( 1.0f, 0.0f,-1.0f);						// Bottom Right
	glVertex3f(-1.0f, 0.0f,-1.0f);						// Bottom Left
	glVertex3f(-1.0f, 0.0f, 1.0f);						// Top Left
	glVertex3f( 1.0f, 0.0f, 1.0f);						// Top Right
	glEnd();											// 
	glPopMatrix();


}

// Render the wall tile
void ThemeDefault::RenderTileWall(float X, float Y)
{
	X = (X + 1.0f) * m_fTileOffsetGap;
	Y = (Y + 1.0f) * m_fTileOffsetGap;
	float Z = 0.0f;

	glEnable(GL_LIGHTING);
	//glEnable(GL_TEXTURE_2D);

	glPushMatrix();	
	glTranslatef(X, Z, Y);								//
	/*glColor3f(0.5f,0.5f,1.0f);							// blue
	glBegin(GL_QUADS);									// 
	glVertex3f( 1.0f, 0.0f,-1.0f);						// Bottom Right
	glVertex3f(-1.0f, 0.0f,-1.0f);						// Bottom Left
	glVertex3f(-1.0f, 0.0f, 1.0f);						// Top Left
	glVertex3f( 1.0f, 0.0f, 1.0f);						// Top Right*/
	//glEnd();											// 

	//glScalef(m_fTileOffsetGap / 2.0f, 1.0f, m_fTileOffsetGap / 2.0f);
	m_WallModel.RenderModel();
	
	glPopMatrix();

	//glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);

}

// Render the void tile
void ThemeDefault::RenderTileVoid(float X, float Y)
{
	X = (X + 1.0f) * m_fTileOffsetGap;
	Y = (Y + 1.0f) * m_fTileOffsetGap;
	float Z = 0.0f;

	glEnable(GL_LIGHTING);

	glPushMatrix();	
	glTranslatef(X, Z, Y);								//
	glColor3f(0.2f, 0.8f, 0.0f);

	glBegin(GL_QUADS);									// 
	glVertex3f( 1.0f, 0.0f,-1.0f);						// Bottom Right
	glVertex3f(-1.0f, 0.0f,-1.0f);						// Bottom Left
	glVertex3f(-1.0f, 0.0f, 1.0f);						// Top Left
	glVertex3f( 1.0f, 0.0f, 1.0f);						// Top Right
	glEnd();											// 
	glPopMatrix();

	glDisable(GL_LIGHTING);

}

// Render the void tile
void ThemeDefault::RenderItemTarget(float X, float Y)
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

// Render the crate tile
void ThemeDefault::RenderItemCrate(float X, float Y)
{
	X = (X + 1.0f) * m_fTileOffsetGap;
	Y = (Y + 1.0f) * m_fTileOffsetGap;

	//Z = 0.75f;
	float Z=0.0f;

	glEnable(GL_LIGHTING);

	glPushMatrix();	
	glTranslatef(X, Z, Y);								//

    m_CrateModel.RenderModel();

	glPopMatrix();

	glDisable(GL_LIGHTING);

	return;

/*	glColor3f(1.0f,1.0f,0.0f);							// yellow

	glScalef(0.75f, 0.75f, 0.75f);							// half size

	glEnable(GL_TEXTURE_2D);
	glColor3ub(255, 255, 255);
	glBindTexture(GL_TEXTURE_2D, m_CrateTextureID);

	glBegin(GL_QUADS);
	// Front Face
	glNormal3f( 0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
	// Back Face
	glNormal3f( 0.0f, 0.0f,-1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
	// Top Face
	glNormal3f( 0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
	// Bottom Face
	glNormal3f( 0.0f,-1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
	// Right face
	glNormal3f( 1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
	// Left Face
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	glEnd();

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);*/

}

// Render the void tile
void ThemeDefault::RenderItemPlayer(float X, float Y)
{
	static GLUquadricObj* PlayerSphere = gluNewQuadric();

	X = (X + 1.0f) * m_fTileOffsetGap;
	Y = (Y + 1.0f) * m_fTileOffsetGap;
	float Z = 0.5f;

	glEnable(GL_LIGHTING);

	glPushMatrix();
	
	// draw body
	glTranslatef(X, Z, Y);								//
	glColor3f(0.5f, 0.5f, 0.5f);						// light grey
	gluSphere(PlayerSphere, 0.85, 8, 8);

	// draw head
	glTranslatef(0.0f,1.0f,0.0f);
	glColor3f(0.9f, 0.9f, 0.9f);						// white
	gluSphere(PlayerSphere, 0.50, 8, 8);

	glPopMatrix();

	glDisable(GL_LIGHTING);
}

// Render the surrounding scene
void ThemeDefault::RenderSurroundingScene(float X, float Y, float Z, float fLevelWidth)
{
	glPushMatrix();
//	glTranslatef(X+20, Y, Z+20);

	CVector3 Pos;
	Pos = g_camera->Position();

	glTranslatef(Pos.x, Pos.y, Pos.z);
	glScalef(5.0f, 5.0f, 5.0f);

	m_SkyboxModel.RenderModel();

	glPopMatrix();
}
