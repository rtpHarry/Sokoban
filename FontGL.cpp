#include ".\FontGL.h"
#include "NeHeGL.h"				// for g_window access

#include <iostream>
#include <fstream>
using namespace std;
#include "Vector2.h"

#include "TextureCache.h"

GLuint	FontGL::m_DisplayListBase = 0;				// Base Display List For The Font
GLuint	FontGL::m_TextureID = 0;					// Storage For Our Font Texture
bool	FontGL::m_bFontBuilt = false;
FontSettings FontGL::m_Metrics;

FontGL::FontGL(void)
{
}

FontGL::~FontGL(void)
{
}

// Setup the fonts
void FontGL::SetupFonts(void)
{
	if(m_bFontBuilt == false)
	{
		// load font image file
		_LoadFont(".\\data\\font-verdana.png");

		FontSettings Settings;
		Settings.NumberOfRows = 8;
		Settings.NumberOfColumns = 16;
		Settings.SpaceBetweenLetters = 18.0f;
		Settings.RenderWidth = 32.0f;
		Settings.RenderHeight = 32.0f;

		_BuildFontLists(Settings);
		m_Metrics = Settings;

		m_bFontBuilt = true;
	}
}

// Delete the display lists from the graphics card
void FontGL::DestroyFonts(void)
{
	if (m_bFontBuilt)
	{
		glDeleteLists(m_DisplayListBase,128);
		m_bFontBuilt = false;
	}

}

void FontGL::Print(int x, int y, char* TextString)
{
	Print(x, y, (const char*) TextString);
}

// Print the font, use glColor before to change appearance
void FontGL::Print(int x, int y, const char* TextString)
{
	// dont try to print if font hasnt been loaded!
	if (!m_bFontBuilt) return;

	// gl state checkers
	GLboolean bWasTextureOn = glIsEnabled(GL_TEXTURE_2D);
	GLboolean bWasDepthOff = glIsEnabled(GL_DEPTH);

	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);					// Select The Type Of Blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
	glDisable(GL_DEPTH_TEST);

	// setup the display mode
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, g_window->init.width, 0, g_window->init.height, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	// position the text (0,0 is bottom left in ortho mode!)
	glTranslated(x, y, 0);

	// offset display list because the first 32 characters of ASCII are not visible letters!
	glListBase(m_DisplayListBase-32);

	// call the corresponding display list for every letter in the string
	glCallLists(strlen(TextString), GL_BYTE, TextString);

	// restore the display mode
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	if (bWasTextureOn) glEnable(GL_TEXTURE_2D);
}


// Load a font file into memory
void FontGL::_LoadFont(char* FontFilename)
{
	/*
	// Generate the main image name to use.
	ilGenImages(1, &ImgId);
	// Bind this image name.
	ilBindImage(ImgId);
	// Loads the image specified by File into the ImgId image.
	ilLoadImage(FileName);

	// Make sure the window is in the same proportions as the image.
	//  Generate the appropriate width x height less than or equal to MAX_X x MAX_Y.
	//	Instead of just clipping Width x Height to MAX_X x MAX_Y, we scale to
	//	an appropriate size, so the image isn't stretched/squished.
	Width  = ilGetInteger(IL_IMAGE_WIDTH);
	Height = ilGetInteger(IL_IMAGE_HEIGHT);
	*/

	m_TextureID = TextureCache::Instance().LoadTexture(FontFilename);
}


// Load a bmp file into memory
/*AUX_RGBImageRec* FontGL::_LoadBMP(char* Filename)
{
	FILE *File=NULL;                                // File Handle
	if (!Filename)                                  // Make Sure A Filename Was Given
	{
		return NULL;                            // If Not Return NULL
	}
	File=fopen(Filename,"r");                       // Check To See If The File Exists
	if (File)                                       // Does The File Exist?
	{
		fclose(File);                           // Close The Handle
		return auxDIBImageLoad(Filename);       // Load The Bitmap And Return A Pointer
	}
	return NULL;                                    // If Load Failed Return NULL
}

// Load the font texture onto the graphics card
int FontGL::_LoadFontTexture(void)
{
	int Status=FALSE;                               // Status Indicator
	AUX_RGBImageRec* TextureImage;					// Create Storage Space For The Textures
//	memset(TextureImage,0,sizeof(void *));        // Set The Pointer To NULL

	if (TextureImage=_LoadBMP(".\\data\\font-verdana.bmp"))
	{
		Status=TRUE;                            // Set The Status To TRUE
		glGenTextures(1, &texture);				// Create One Texture

		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}

	if (TextureImage)							// If Texture Exists
	{
		if (TextureImage->data)			// If Texture Image Exists
		{
			free(TextureImage->data);	// Free The Texture Image Memory
		}
		free(TextureImage);				// Free The Image Structure
	}

	return Status;                                  // Return The Status
}*/

//#define FONT_SCALE_Y 0.0625f
//#define FONT_SCALE_X 0.1250f

//#define FONT_SCALE_Y 0.0f
//#define FONT_SCALE_X 0.0f

// Build the display lists for each letter of the fonts
void FontGL::_BuildFontLists(FontSettings Settings)
{
	// reserve space for display lists
	m_DisplayListBase = glGenLists(128);

	// select font texture
	glBindTexture(GL_TEXTURE_2D, m_TextureID);

	///
	//////////////////////////////////////////////////////////////////////////
//	ofstream examplefile (".\\fontgl.txt");
	Vector2f Tex1, Tex2, Tex3, Tex4;

	float CellWidth = 1.0f / Settings.NumberOfColumns;
	float CellHeight = 1.0f / Settings.NumberOfRows;
	int Loop = 0;

//	examplefile << "CellWidth : " << CellWidth << endl
//		<< "CellHeight : " << CellHeight << endl << endl;

	// build character set
	for (GLuint LoopRows = Settings.NumberOfRows-1; LoopRows > 0; LoopRows--)
	{
		for(GLuint LoopCols = 0; LoopCols < Settings.NumberOfColumns; LoopCols++)
		{
			float TopLeftCol = CellWidth * LoopCols;
			float TopLeftRow = CellHeight * LoopRows;

			// start the next list
			glNewList(m_DisplayListBase + Loop, GL_COMPILE);

			// draw the character
			glBegin(GL_QUADS);
            
			Tex1.Set(TopLeftCol, TopLeftRow);
			glTexCoord2f(Tex1.x,Tex1.y);
			glVertex2f(0.0f, 0.0f);										// (Bottom Left)

			Tex2.Set(TopLeftCol + CellWidth, TopLeftRow);
			glTexCoord2f(Tex2.x,Tex2.y);
			glVertex2f(Settings.RenderWidth, 0.0f);						// (Bottom Right)

			Tex3.Set(TopLeftCol + CellWidth, TopLeftRow + CellHeight);
			glTexCoord2f(Tex3.x,Tex3.y);
			glVertex2f(Settings.RenderWidth, Settings.RenderHeight);	// (Top Right)

			Tex4.Set(TopLeftCol, TopLeftRow + CellHeight);
			glTexCoord2f(Tex4.x,Tex4.y);
			glVertex2f(0.0f,Settings.RenderHeight);						// (Top Left)

			glEnd();

			//////////////////////////////////////////////////////////////////////////
//			if (examplefile.is_open())
//			{
//			examplefile << ":loop: " << loop << " :Cx: " << cx << " :Cy: " << cy << "\t\t"
//			<< " :tex1: " << Tex1.x << "," << Tex1.y << "\t\t"
//			<< " :tex2: " << Tex2.x << "," << Tex2.y << "\t\t"
//			<< " :tex3: " << Tex3.x << "," << Tex3.y << "\t\t"
//			<< " :tex4: " << Tex4.x << "," << Tex4.y << endl;
//			}
			//////////////////////////////////////////////////////////////////////////

			// insert space between letters
			glTranslated(Settings.SpaceBetweenLetters, 0, 0);

			glEndList();

			Loop++;
		}
		
	}

	//////////////////////////////////////////////////////////////////////////
//	examplefile.close();
}

/*
	// build character set
	for (GLuint loop = 0; loop < TotalChars; loop++)
	{
		// calculate texture coord offset
		cx = float(loop % Settings.NumberOfColumns) / Settings.NumberOfColumns;	// X Position Of Current Character
		cy = float(loop / Settings.NumberOfColumns) / Settings.NumberOfRows;	// Y Position Of Current Character

		// start the next list
		glNewList(base+loop,GL_COMPILE);

		// draw the character
		glBegin(GL_QUADS);

		Tex1.Set(cx,1-cy);
		glTexCoord2f(Tex1.x,Tex1.y);
		glVertex2f(0.0f, 0.0f);											// (Bottom Left)

		Tex2.Set(cx+FONT_SCALE_Y,1-cy);
		glTexCoord2f(Tex2.x,Tex2.y);
		glVertex2f(Settings.RenderWidth, 0.0f);						// (Bottom Right)

		Tex3.Set(cx+FONT_SCALE_Y,1-cy-(FONT_SCALE_X));
		glTexCoord2f(Tex3.x,Tex3.y);
		glVertex2f(Settings.RenderWidth, Settings.RenderHeight);	// (Top Right)

		Tex4.Set(cx,1-cy-(FONT_SCALE_X));
		glTexCoord2f(Tex4.x,Tex4.y);
		glVertex2f(0.0f,Settings.RenderHeight);						// (Top Left)

		glEnd();

		//////////////////////////////////////////////////////////////////////////
		if (examplefile.is_open())
		{
			examplefile << ":loop: " << loop << " :Cx: " << cx << " :Cy: " << cy << "\t\t"
				<< " :tex1: " << Tex1.x << "," << Tex1.y << "\t\t"
				<< " :tex2: " << Tex2.x << "," << Tex2.y << "\t\t"
				<< " :tex3: " << Tex3.x << "," << Tex3.y << "\t\t"
				<< " :tex4: " << Tex4.x << "," << Tex4.y << endl;

				

		}


		// insert space between letters
		glTranslated(Settings.SpaceBetweenLetters, 0, 0);

		glEndList();
	}

	//////////////////////////////////////////////////////////////////////////
	examplefile.close();
}
*/

/*
glTexCoord2f(cx,1-cy);
glVertex2f(0.0f, 0.0f);											// (Bottom Left)

glTexCoord2f(cx+FONT_SCALE_Y,1-cy);
glVertex2f(Settings.RenderWidth, 0.0f);						// (Bottom Right)

glTexCoord2f(cx+FONT_SCALE_Y,1-cy-(FONT_SCALE_X));
glVertex2f(Settings.RenderWidth, Settings.RenderHeight);	// (Top Right)

glTexCoord2f(cx,1-cy-(FONT_SCALE_X));
glVertex2f(0.0f,Settings.RenderHeight);						// (Top Left)
*/

// Get information about the font
FontSettings FontGL::GetMetrics(void)
{
	return m_Metrics;
}
