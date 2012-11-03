#include ".\thememodel.h"

#include "GLee.h"
//#include <Windows.h>
//#include <gl/GL.h>
#include <gl/GLU.h>

#include "SokobanSoundManager.h"

#include "NeHeGL.h"		// for g_window


ThemeModel::ThemeModel(void)
{
	m_fTileOffsetGap = 2.2f;
	m_sThemeName = "Model";

	bUseDefaultFloor = false;
	bUseDefaultWall = false;
	bUseDefaultVoid = false;
	bUseDefaultPlayer = false;
	bUseDefaultCrate = false;
	bUseDefaultTarget = false;
	bUseDefaultSkyBox = false;

	m_vFloorColor = CVector3(255,255,255);
	m_vWallColor = CVector3(0.5f,0.5f,1.0f);
	m_vVoidColor = CVector3(0.2f,0.8f,0.0f);
	m_vPlayerColor = CVector3(0.5f, 0.5f, 0.5f);
	m_vCrateColor = CVector3(1.0f,1.0f,0.0f);
	m_vTargetColor = CVector3(0.2f, 1.0f, 0.2f);

}

ThemeModel::~ThemeModel(void)
{
}

// setup any theme related resources
void ThemeModel::SetupTheme(void)
{
	// load models
	// if (cant load model) then use default
	if(!m_FloorModel.LoadModel("floor.3ds",	(char *)GetFullAssetDirectory().c_str())) { bUseDefaultFloor = true; }
	if(!m_WallModel.LoadModel("wall.3ds", (char *)GetFullAssetDirectory().c_str())) { bUseDefaultWall = true; }
	if(!m_VoidModel.LoadModel("void.3ds", (char *)GetFullAssetDirectory().c_str())) { bUseDefaultVoid = true; }
	if(!m_PlayerModel.LoadModel("player.3ds", (char *)GetFullAssetDirectory().c_str())) { bUseDefaultPlayer = true; }
	if(!m_CrateModel.LoadModel("crate.3ds", (char *)GetFullAssetDirectory().c_str())) { bUseDefaultCrate = true; }
	if(!m_TargetModel.LoadModel("target.3ds", (char *)GetFullAssetDirectory().c_str())) { bUseDefaultTarget = true; }
	if(!m_SkyboxModel.LoadModel("skysphere.3ds", (char *)GetFullAssetDirectory().c_str())) { bUseDefaultSkyBox = true; }

	// setup default quad
	m_didDefaultTile = glGenLists(1);	
	glNewList(m_didDefaultTile, GL_COMPILE);

	glBegin(GL_QUADS);									// 
		glVertex3f( 1.0f, 0.0f,-1.0f);						// Bottom Right
		glVertex3f(-1.0f, 0.0f,-1.0f);						// Bottom Left
		glVertex3f(-1.0f, 0.0f, 1.0f);						// Top Left
		glVertex3f( 1.0f, 0.0f, 1.0f);						// Top Right
	glEnd();											// 

	glEndList();


	// setup default sounds
	SokobanSoundManager &SoundMgr = SokobanSoundManager::Instance();

	SoundMgr.CacheSampleFromFile(EventType(MOVE_EVENT_STEP), ".\\audio\\move\\footstep.wav");
	SoundMgr.CacheSampleFromFile(EventType(MOVE_EVENT_BUMPCRATE), ".\\audio\\move\\bump.wav");
	SoundMgr.CacheSampleFromFile(EventType(MOVE_EVENT_BUMPWALL), ".\\audio\\move\\bump.wav");
	SoundMgr.CacheSampleFromFile(EventType(MOVE_EVENT_PUSHTOEMPTY), ".\\audio\\move\\pushscrape-rtp.wav");
	SoundMgr.CacheSampleFromFile(EventType(MOVE_EVENT_PUSHTOWALL), ".\\audio\\move\\pushscrape-rtp.wav");
	SoundMgr.CacheSampleFromFile(EventType(MOVE_EVENT_PUSHTOCRATE), ".\\audio\\move\\pushscrape-rtp.wav");
	SoundMgr.CacheSampleFromFile(EventType(MOVE_EVENT_PUSHTOTARGET), ".\\audio\\move\\pushscrape-rtp.wav");
	SoundMgr.CacheSampleFromFile(EventType(MOVE_EVENT_PUSHFROMTARGET), ".\\audio\\move\\pushscrape-rtp.wav");
	SoundMgr.CacheSampleFromFile(EventType(MOVE_EVENT_PUSHBETWEENTARGETS), ".\\audio\\move\\pushscrape-rtp.wav");

}

// un-setup any theme related resources
void ThemeModel::DestroyTheme(void)
{
	m_FloorModel.FreeDisplayList();
	m_WallModel.FreeDisplayList();
	m_VoidModel.FreeDisplayList();
	m_PlayerModel.FreeDisplayList();
	m_CrateModel.FreeDisplayList();
	m_TargetModel.FreeDisplayList();
	m_SkyboxModel.FreeDisplayList();

	glDeleteLists(m_didDefaultTile, 1);

}

// Operations before the scene has been rendered
void ThemeModel::PreRender(void)
{
}

// Operations after the scene has been rendered
void ThemeModel::PostRender(void)
{
	// display axis
//	DisplayAxis(30);

}

// Render the floor tile
void ThemeModel::RenderTileFloor(float X, float Y)
{
	X = X * m_fTileOffsetGap;
	Y = Y * m_fTileOffsetGap;

	if (bUseDefaultFloor)
	{
		// handle texture and lighting
		GLboolean bWasLightingOn = glIsEnabled(GL_LIGHTING);
		GLboolean bWasTextureOn = glIsEnabled(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);

		glPushMatrix();
		glTranslatef(X, 0, Y);
		glColor3ub(m_vFloorColor.x, m_vFloorColor.y, m_vFloorColor.z);
		glCallList(m_didDefaultTile);
		glPopMatrix();

		if (bWasLightingOn) { glEnable(GL_LIGHTING); }
		if (bWasTextureOn) { glEnable(GL_TEXTURE_2D); }
	}
	else
	{
		glPushMatrix();
		glTranslatef(X, 0, Y);
		m_FloorModel.RenderModel();
		glPopMatrix();
	}
}

// Render the wall tile
void ThemeModel::RenderTileWall(float X, float Y)
{
	X = X * m_fTileOffsetGap;
	Y = Y * m_fTileOffsetGap;

	if (bUseDefaultWall)
	{
		// handle texture and lighting
		GLboolean bWasLightingOn = glIsEnabled(GL_LIGHTING);
		GLboolean bWasTextureOn = glIsEnabled(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);

		glPushMatrix();
		glTranslatef(X, 0, Y);
		glColor3f(m_vWallColor.x, m_vWallColor.y, m_vWallColor.z);
		glCallList(m_didDefaultTile);
		glPopMatrix();

		if (bWasLightingOn) { glEnable(GL_LIGHTING); }
		if (bWasTextureOn) { glEnable(GL_TEXTURE_2D); }
	}
	else
	{
		glPushMatrix();
		glTranslatef(X, 0, Y);
		m_WallModel.RenderModel();
		glPopMatrix();
	}
}

// Render the void tile
void ThemeModel::RenderTileVoid(float X, float Y)
{
	X = X * m_fTileOffsetGap;
	Y = Y * m_fTileOffsetGap;

	if (bUseDefaultVoid)
	{
		// handle texture and lighting
		GLboolean bWasLightingOn = glIsEnabled(GL_LIGHTING);
		GLboolean bWasTextureOn = glIsEnabled(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);

		glPushMatrix();
		glTranslatef(X, 0, Y);
		glColor3f(m_vVoidColor.x, m_vVoidColor.y, m_vVoidColor.z);
		glCallList(m_didDefaultTile);
		glPopMatrix();

		if (bWasLightingOn) { glEnable(GL_LIGHTING); }
		if (bWasTextureOn) { glEnable(GL_TEXTURE_2D); }
	}
	else
	{
		glPushMatrix();
		glTranslatef(X, 0, Y);
		m_VoidModel.RenderModel();
		glPopMatrix();
	}
}

// Render the void tile
void ThemeModel::RenderItemTarget(float X, float Y)
{
	X = X * m_fTileOffsetGap;
	Y = Y * m_fTileOffsetGap;

	if (bUseDefaultTarget)
	{
		// handle texture and lighting
		GLboolean bWasLightingOn = glIsEnabled(GL_LIGHTING);
		GLboolean bWasTextureOn = glIsEnabled(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);

		glPushMatrix();
		glTranslatef(X, 0.0002f, Y);
		glColor3f(m_vTargetColor.x, m_vTargetColor.y, m_vTargetColor.z);
		glScalef(0.85f, 0.85f, 0.85f);
		glCallList(m_didDefaultTile);
		glPopMatrix();

		if (bWasLightingOn) { glEnable(GL_LIGHTING); }
		if (bWasTextureOn) { glEnable(GL_TEXTURE_2D); }
	}
	else
	{
		glPushMatrix();
		glTranslatef(X, 0, Y);
		m_TargetModel.RenderModel();
		glPopMatrix();
	}
}

// Render the void tile
void ThemeModel::RenderItemCrate(float X, float Y)
{
	X = X * m_fTileOffsetGap;
	Y = Y * m_fTileOffsetGap;

	if (bUseDefaultCrate)
	{
		// handle texture and lighting
		GLboolean bWasLightingOn = glIsEnabled(GL_LIGHTING);
		GLboolean bWasTextureOn = glIsEnabled(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);

		glPushMatrix();
		glTranslatef(X, 0.75f, Y);
		glColor3f(m_vCrateColor.x, m_vCrateColor.y, m_vCrateColor.z);
		glScalef(0.75f, 0.75f, 0.75f);
		glCallList(m_didDefaultTile);
		glPopMatrix();

		if (bWasLightingOn) { glEnable(GL_LIGHTING); }
		if (bWasTextureOn) { glEnable(GL_TEXTURE_2D); }
	}
	else
	{
		glPushMatrix();
		glTranslatef(X, 0, Y);
		m_CrateModel.RenderModel();
		glPopMatrix();
	}
}

// Render the void tile
void ThemeModel::RenderItemPlayer(float X, float Y)
{
	static GLUquadricObj* PlayerSphere = gluNewQuadric();
	
	X = X * m_fTileOffsetGap;
	Y = Y * m_fTileOffsetGap;
	float Z = 0.5f;

	if (bUseDefaultPlayer)
	{
		// handle texture and lighting
		GLboolean bWasTextureOn = glIsEnabled(GL_TEXTURE_2D);
		glDisable(GL_TEXTURE_2D);

		glPushMatrix();

		// draw body
		glTranslatef(X, Z, Y);								//
		glColor3f(m_vPlayerColor.x, m_vPlayerColor.y, m_vPlayerColor.z);
		gluSphere(PlayerSphere, 0.85, 8, 8);

		// draw head
		glTranslatef(0.0f,1.0f,0.0f);
		glColor3f(0.9f, 0.9f, 0.9f);						// white
		gluSphere(PlayerSphere, 0.50, 8, 8);

		glPopMatrix();

		if (bWasTextureOn) { glEnable(GL_TEXTURE_2D); }

	}
	else
	{
		glPushMatrix();
		glTranslatef(X, Z, Y);
		m_PlayerModel.RenderModel();
		glPopMatrix();
	}


	
}

// Render the surrounding scene
void ThemeModel::RenderSurroundingScene(float X, float Y, float Z, float fLevelWidth)
{
	// there is no default skybox
	if (bUseDefaultSkyBox)	{ return;	}


	// ok to display model one
	glPushMatrix();

	CVector3 Pos;
	Pos = g_camera->Position();

	glTranslatef(Pos.x, Pos.y, Pos.z);
	glTranslatef(0, -40.0f, 0);
	glScalef(2.0f, 2.0f, 2.0f);

	m_SkyboxModel.RenderModel();

	glPopMatrix();	
}
