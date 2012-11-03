#pragma once
#include "Theme.h"
#include "model3d.h"

class ThemeSimple 
	: public Theme
{
public:
	ThemeSimple(void);
	virtual ~ThemeSimple(void);

	virtual void SetupTheme(void);
	virtual void DestroyTheme(void);

	virtual void PreRender(void);											// operations before rendered scene
	virtual void PostRender(void);											// operations after rendered scene

	virtual void RenderTileFloor(float X, float Y);							// Render the floor tile
	virtual void RenderTileWall(float X, float Y);							// Render the wall tile
	virtual void RenderTileVoid(float X, float Y);							// Render the void tile

	virtual void RenderItemTarget(float X, float Y);						// Render the target item
	virtual void RenderItemCrate(float X, float Y);							// Render the crate item
	virtual void RenderItemPlayer(float X, float Y);						// Render the player item

																			// Render the scenery
	virtual void RenderSurroundingScene(float X, float Y, float Z, float fLevelWidth);	

private:
};
