#include "TextureCache.h"

#include <il/il.h>
#include <il/ilut.h>


TextureCache::TextureCache(void)
{
}

TextureCache::~TextureCache(void)
{
}

// Add a new sample into the cache
// Note: Check return value, if its AL_NONE then sample has not been cached
TextureID TextureCache::LoadTexture(string FileName)
{
	// check for file in loaded sounds list
	vector<TextureCacheObject>::iterator ii;
	for(ii=m_TextureCache.begin(); ii!=m_TextureCache.end(); ii++)
	{
		// check if sample matches
		if ( ii->FileName == FileName )
		{
			// found: +1 to its references, return its OpenALSoundID
			ii->References++;

			return ii->OpenGLTextureID;
		}
	}

	// not found:
	TextureCacheObject NewTexture;

	// load sample in OpenGL
	NewTexture.OpenGLTextureID = ilutGLLoadImage((ILstring)FileName.c_str()); 

	// updates its references
	NewTexture.References = 1;

	// set the filename
	NewTexture.FileName = FileName;

	// add it to the cache list
	m_TextureCache.push_back(NewTexture);

	// return its TextureID
	return NewTexture.OpenGLTextureID;
}

// Unload a texture from the system
unsigned int TextureCache::FreeTexture(TextureID TexID)
{
	// check for file in loaded textures cache
	vector<TextureCacheObject>::iterator ii;
	for(ii=m_TextureCache.begin(); ii!=m_TextureCache.end(); ii++)
	{
		// check if texture ID matches
		if ( ii->OpenGLTextureID == TexID )
		{
			// found: -1 to its references
			if(--ii->References)
			{
				// still has references (in use) so just return number of references
				return ii->OpenGLTextureID;
			}
			// no more references left so unload from graphics card
			else
			{
				// remove from graphics card
				glDeleteTextures(1, &ii->OpenGLTextureID);

				// remove from cache list
				m_TextureCache.erase(ii);

				return false;
			}
		}
	}

	// not found

	return false;
}