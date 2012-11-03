#pragma once

#include "shadowmapeffect.h"

#include "SokobanActiveLevel.h"
#include "ThemeSimple.h"		// flat untextured
#include "ThemeDefault.h"		// textured, skybox, lit

#include "ThemeDesert.h"
#include "ThemeEvilForest.h"


#include "Vector3.h"


class SokobanRenderer
{
public:
	SokobanRenderer(void);
	~SokobanRenderer(void);
	void RenderLevel(const SokobanActiveLevel LevelData);

	// TODO :: ThemeMgr
	//ThemeDefault m_Theme;
	//ThemeSimple m_Theme;
	//ThemeEvilForest m_Theme;
	ThemeDesert m_Theme;

	// Initialize the Render System
	void Setup(void);
private:
	// Actually render the level
	void _RenderLevel(const SokobanActiveLevel LevelData);
	// The amount to scale the level by in order to get it to fit in a 50 x 50 space
	CVector3 m_LevelScale;
	// Calculate the amount to scale the level to in order to fit it on screen
	float CalculateScaleFactor(float ClampAmount, const SokobanActiveLevel LevelData);

public:
	ShadowMapEffect ShadowMap;
};
