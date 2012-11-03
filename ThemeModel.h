#pragma once
//////////////////////////////////////////////////////////////////////////
// This is a base class for all themes that use 3dmodels
//////////////////////////////////////////////////////////////////////////
// Theme
//  - ThemeDefault
//  - ThemeSimple
//  - ThemeModel
//     - ThemeDesert
//     - ThemeEvilForest

#include "theme.h"

#include "Vector3.h"
#include "Model3D.h"

class ThemeModel 
	: public Theme
{
public:
	ThemeModel(void);
	virtual ~ThemeModel(void);

	// abstract interface
	virtual void SetupTheme(void);
	virtual void DestroyTheme(void);

	virtual void PreRender(void);										// operations before rendered scene
	virtual void PostRender(void);										// operations after rendered scene

	virtual void RenderTileFloor(float X, float Y);						// Render the floor tile
	virtual void RenderTileWall(float X, float Y);						// Render the wall tile
	virtual void RenderTileVoid(float X, float Y);						// Render the void tile

	virtual void RenderItemTarget(float X, float Y);					// Render the target item
	virtual void RenderItemCrate(float X, float Y);						// Render the crate item
	virtual void RenderItemPlayer(float X, float Y);					// Render the player item

																		// Render the scenery
	virtual void RenderSurroundingScene(float X, float Y, float Z, float fLevelWidth);		

protected:
	// models
	Model3D m_FloorModel;
	Model3D m_WallModel;
	Model3D m_VoidModel;
	Model3D m_PlayerModel;
	Model3D m_CrateModel;
	Model3D m_TargetModel;
	Model3D m_SkyboxModel;

	// display list ids
	GLuint m_didDefaultTile;

	// bools
	bool bUseDefaultFloor;
	bool bUseDefaultWall;
	bool bUseDefaultVoid;
	bool bUseDefaultPlayer;
	bool bUseDefaultCrate;
	bool bUseDefaultTarget;
	bool bUseDefaultSkyBox;

	// colors
	CVector3 m_vFloorColor;
	CVector3 m_vWallColor;
	CVector3 m_vVoidColor;
	CVector3 m_vPlayerColor;
	CVector3 m_vCrateColor;
	CVector3 m_vTargetColor;
	// skybox color not needed

};
