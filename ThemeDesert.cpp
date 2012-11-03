#include ".\themedesert.h"
#include "SokobanSoundManager.h"

ThemeDesert::ThemeDesert(void)
{
}

ThemeDesert::~ThemeDesert(void)
{
}


//////////////////////////////////////////////////////////////////////////
// Abstract Functions
//////////////////////////////////////////////////////////////////////////

// setup any theme related resources
void ThemeDesert::SetupTheme(void)
{
	// Desert Theme Specific Settings
	m_sThemeName = "Desert";

	// still let the base class do default setup
	ThemeModel::SetupTheme();

	//
	m_vFloorColor = CVector3(183, 140, 105);

	
	// setup sounds
	//////////////////////////////////////////////////////////////////////////
//	SokobanSoundManager &SoundCache = SokobanSoundManager::Instance();

/*	string SoundStepFileName = GetFullAssetDirectory();
	SoundStepFileName += "audio\\move_forward.au";*/

//	SoundCache.LoadSampleFromFile(MOVEEVENT_STEP, ".\\audio\\sample.wav");


}

// dont need to override anything below here from default model class

/*
// un-setup any theme related resources
void ThemeDesert::DestroyTheme(void)
{

}
*/

/*
// Operations before the scene has been rendered
void ThemeDesert::PreRender(void)
{

}

// Operations after the scene has been rendered
void ThemeDesert::PostRender(void)
{

}

// Render the floor tile
void ThemeDesert::RenderTileFloor(float X, float Y)
{
}

// Render the wall tile
void ThemeDesert::RenderTileWall(float X, float Y)
{
}

// Render the void tile
void ThemeDesert::RenderTileVoid(float X, float Y)
{
}

// Render the void tile
void ThemeDesert::RenderItemTarget(float X, float Y)
{
}

// Render the void tile
void ThemeDesert::RenderItemCrate(float X, float Y)
{
}

// Render the void tile
void ThemeDesert::RenderItemPlayer(float X, float Y)
{
}

// Render the surrounding scene
void ThemeDesert::RenderSurroundingScene(float X, float Y, float Z, float fLevelWidth)
{
}
*/
