#pragma once
/////////////////////////////////////////////////////////////////////////////////
// This is the interface class that provides the framework for the actual themes
/////////////////////////////////////////////////////////////////////////////////
// Note: Themes using a 3d model should be derived off ThemeModel

#include <string>
using namespace std;

class Theme
{
public:
	Theme(void);
	virtual ~Theme(void);

	// abstract interface
	//////////////////////////////////////////////////////////////////////////
	virtual void SetupTheme(void) = 0;
	virtual void DestroyTheme(void) = 0;

	virtual void PreRender(void) = 0;										// operations before rendered scene
	virtual void PostRender(void) = 0;										// operations after rendered scene

	virtual void RenderTileFloor(float X, float Y) = 0;						// Render the floor tile
	virtual void RenderTileWall(float X, float Y) = 0;						// Render the wall tile
	virtual void RenderTileVoid(float X, float Y) = 0;						// Render the void tile

	virtual void RenderItemTarget(float X, float Y) = 0;					// Render the target item
	virtual void RenderItemCrate(float X, float Y) = 0;						// Render the crate item
	virtual void RenderItemPlayer(float X, float Y) = 0;					// Render the player item

	virtual void RenderSurroundingScene(float X, float Y, float Z, float fLevelWidth) = 0;	// Render the scenery

protected:
	// accessor functions
	//////////////////////////////////////////////////////////////////////////
	float	m_fTileOffsetGap;
	string	m_sThemeName;
	string  m_sBaseDirectory;

	// Get the directory that all theme assets are stored in
	string GetBaseDirectory(void) const
	{
		return m_sBaseDirectory;
	}

	// Get the full path to the themes assets
	string GetFullAssetDirectory(void) const
	{
		return GetBaseDirectory() + GetThemeName();
	}

	// Get the name of this theme
	string GetThemeName(void) const
	{
		return m_sThemeName;
	}

public:
	// Get the amount of space between each tile
	float GetTileOffsetGap(void) const
	{
		return m_fTileOffsetGap;
	}

protected:
	// Set the amount of space to leave between each tile
	void  SetTileOffsetGap(float fOffset)
	{
		m_fTileOffsetGap = fOffset;
	}

	// Utility functions
	//////////////////////////////////////////////////////////////////////////
protected:	
	// Draw an Axis
	void DisplayAxis(float length);
};
