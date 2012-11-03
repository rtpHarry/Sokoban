#include ".\sokobanrenderer.h"

#include <windows.h>
#include "GLee.h"
//#include <gl/GL.h>
#include <GL/glu.h>

SokobanRenderer::SokobanRenderer(void)
{
}

SokobanRenderer::~SokobanRenderer(void)
{
	m_Theme.DestroyTheme();
}

// Initialize the Render System
void SokobanRenderer::Setup(void)
{
	// TODO :: Theme Setup
	m_Theme.SetupTheme();

	ShadowMap.SetupEffect();
}


void SokobanRenderer::RenderLevel(const SokobanActiveLevel LevelData)
{
	// Pre Render 
	//////////////////////////////////////////////////////////////////////////
	m_Theme.PreRender();


	// Render
	//////////////////////////////////////////////////////////////////////////
	glPushMatrix();
/*		ShadowMap.RenderFirstPass();
		_RenderLevel(LevelData);
		ShadowMap.RenderSecondPass();
		_RenderLevel(LevelData);
		ShadowMap.RenderThirdPass();
		_RenderLevel(LevelData);
		ShadowMap.RenderCleanUp();*/
		_RenderLevel(LevelData);
	glPopMatrix();

	// Surrounding Scenery
	//////////////////////////////////////////////////////////////////////////
	// TODO base location of surround on level not origin
	m_Theme.RenderSurroundingScene(0,0,0,0);

	// Post Render
	//////////////////////////////////////////////////////////////////////////
	m_Theme.PostRender();


}




// Actually render the level
void SokobanRenderer::_RenderLevel(const SokobanActiveLevel LevelData)
{
	// calculate level scale
	float ScaleFactor = CalculateScaleFactor(30.0f, LevelData);

	glScalef(ScaleFactor, ScaleFactor, ScaleFactor);

	// draw the architecture
	//////////////////////////////////////////////////////////////////////////
	for (int outer = 0; outer < LevelData.m_WallData.size(); outer++)
	{
		// loop through current line
		for (int inner = 0; inner < LevelData.m_WallData[outer].length(); inner++)
		{
			switch(LevelData.m_WallData[outer][inner])
			{
			case SYMBOL_WALL:
				m_Theme.RenderTileWall((float)outer, (float)inner);
				break;
			case SYMBOL_FLOOR:
				m_Theme.RenderTileFloor((float)outer, (float)inner);
				break;
			case SYMBOL_VOID:
				m_Theme.RenderTileVoid((float)outer, (float)inner);
				break;
			}
		}
	}

	// draw the items
	//////////////////////////////////////////////////////////////////////////
	for (int indx = 0; indx < LevelData.m_ItemList.size(); indx++)
	{
		int x = LevelData.m_ItemList[indx].ItemLocation.x;
		int y = LevelData.m_ItemList[indx].ItemLocation.y;

		switch(LevelData.m_ItemList[indx].ItemType)
		{
		case SYMBOL_CRATE:
			m_Theme.RenderItemCrate((float)x, (float)y);
			break;

		case SYMBOL_TARGET:
			m_Theme.RenderItemTarget((float)x, (float)y);
			break;
		}

	}

	// draw the player
	//////////////////////////////////////////////////////////////////////////
	int x = LevelData.m_Player.ItemLocation.x;
	int y = LevelData.m_Player.ItemLocation.y;

	m_Theme.RenderItemPlayer((float)x, (float)y);

}

// Calculate the amount to scale the level to in order to fit it on screen
float SokobanRenderer::CalculateScaleFactor(float ClampAmount, const SokobanActiveLevel LevelData)
{
	// calculate the true level dimensions
	float Width = LevelData.m_LevelDimensions.x + (LevelData.m_LevelDimensions.x * m_Theme.GetTileOffsetGap());
	float Height = LevelData.m_LevelDimensions.y + (LevelData.m_LevelDimensions.y * m_Theme.GetTileOffsetGap());

	// decide which axis is the controlling scale factor
	float ScaleFactor = ((Width > Height) ? Width : Height);

	// calculate the scale factor
	return (1 / (ScaleFactor / ClampAmount));
}
