#include ".\themeevilforest.h"

ThemeEvilForest::ThemeEvilForest(void)
{
}

ThemeEvilForest::~ThemeEvilForest(void)
{
}

//////////////////////////////////////////////////////////////////////////
// Abstract Functions
//////////////////////////////////////////////////////////////////////////

// setup any theme related resources
void ThemeEvilForest::SetupTheme(void)
{
	// Desert Theme Specific Settings
	m_sThemeName = "Evil Forest";

	// still let the base class do default setup
	ThemeModel::SetupTheme();

	// color modifiers
	//m_vFloorColor = CVector3(255, 1, 1);

}

// dont need to override anything below here from default model class

/*
// un-setup any theme related resources
void ThemeEvilForest::DestroyTheme(void)
{

}
*/

/*
// Operations before the scene has been rendered
void ThemeEvilForest::PreRender(void)
{

}

// Operations after the scene has been rendered
void ThemeEvilForest::PostRender(void)
{

}

// Render the floor tile
void ThemeEvilForest::RenderTileFloor(float X, float Y)
{
}

// Render the wall tile
void ThemeEvilForest::RenderTileWall(float X, float Y)
{
}

// Render the void tile
void ThemeEvilForest::RenderTileVoid(float X, float Y)
{
}

// Render the void tile
void ThemeEvilForest::RenderItemTarget(float X, float Y)
{
}

// Render the void tile
void ThemeEvilForest::RenderItemCrate(float X, float Y)
{
}

// Render the void tile
void ThemeEvilForest::RenderItemPlayer(float X, float Y)
{
}

// Render the surrounding scene
void ThemeEvilForest::RenderSurroundingScene(float X, float Y, float Z, float fLevelWidth)
{
}
*/
