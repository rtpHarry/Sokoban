#pragma once

#include <Windows.h>
#include "GLee.h"
//#include <gl\gl.h>

#include <string>
#include <vector>
using namespace std;

#include "Singleton.h"

// clean name for a reference to a sound
typedef GLuint TextureID;

// simple structure to hold together information about a texture
struct TextureCacheObject
{
	TextureID OpenGLTextureID;
	string FileName;
	unsigned int References;
};

class TextureCache : public Singleton<TextureCache>
{
public:
	TextureCache(void);
	~TextureCache(void);

	// Load a new texture into the system
	TextureID LoadTexture(string FileName);

	// Unload a texture from the system
	unsigned int FreeTexture(TextureID TexID);
	
private:
	vector<TextureCacheObject> m_TextureCache;

	// Load a sample from a file
//	TextureID _LoadSampleFromFile(string FileName);
};
