#pragma once

// forward decl
struct CVector3;

class SokobanHUD
{
public:
	SokobanHUD(void);
	~SokobanHUD(void);

private:
	// texture ids
	GLuint m_LogoTexID;			// sokoban logo
	GLuint m_RTPSoftwareTexID;	// rtp|software logo
	GLuint m_HUDBgTexID;		// hud bg
	GLuint m_LvlDoneBgTexID;	// level complete bg

public:
	// Setup the HUD sub system
	void Setup(void);

	// Draw the game logo
	void DrawLogo(void);

	// Draw the level information
	void DrawLevelInfo(int MoveCount, int CratesQuota, int CratesTagged, int HighScore);

	// Draw the fps
	void DrawFPS(void);

	// Draw level complete
	void DrawLevelComplete(void);
	void DrawEpisodeComplete(void);
	void DrawGameComplete(void);

private:
	// convenience function to render a texture in ortho mode
	void Util_DrawTexture(int TextureID, float Alpha, float OffsetX, float OffsetY, float SizeX, float SizeY);
	void Util_DrawTextureC(int TextureID, float Alpha, float OffsetX, float OffsetY, float SizeX, float SizeY, CVector3 Color);

};
