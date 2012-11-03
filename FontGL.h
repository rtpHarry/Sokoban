#pragma once

#include <windows.h>		// Header File For Windows
#include <stdio.h>			// Header File For Standard Input/Output

#include "GLee.h"
//#include <gl\gl.h>			// Header File For The OpenGL32 Library
//#include "libraries\bmp\bmp.h"  // replacement for glaux.h

//////////////////////////////////////////////////////////////////////////
// USAGE INSTRUCTIONS
//////////////////////////////////////////////////////////////////////////
// The font loads its resources once, using static variables, so that you
// can just create a Font class in whatever function you want and start
// writing text to the screen. The flipside to this is that you have to
// manually start it up and shut it down!
//
// I called it FontGL so that you can use the variable name Font in your 
// code
//
// To start it, make an instance and call SetupFonts, like so;
//   FontGL Font;
//   Font.SetupFonts();
//
// Then use DestroyFonts(); to get rid of it at the end like this;
//   FontGL Font;
//   Font.DestroyFonts();
//
//
// If you need to move the location of the font texture its defined in
//  int _LoadFontTexture(void);
//
//////////////////////////////////////////////////////////////////////////

struct FontSettings
{
	GLuint NumberOfRows;			// 8.0f
	GLuint NumberOfColumns;			// 16.0f
	GLfloat SpaceBetweenLetters;	// 22.0f
	GLfloat RenderWidth;			// 32
	GLfloat RenderHeight;			// 32
};

class FontGL
{
public:
	FontGL(void);
	~FontGL(void);

	// Print the font, use glColor before to change appearance
	void Print(int x, int y, char* textstring);	
	void Print(int x, int y, const char* textstring);

	// Setup the fonts
	void SetupFonts(void);

	// Delete the display lists from the graphics card
	void DestroyFonts(void);

private:
	static GLuint m_DisplayListBase;
	static bool m_bFontBuilt;
	static GLuint m_TextureID;
	static FontSettings m_Metrics;
	
	// Load a font file into memory
	void _LoadFont(char* FontFilename);

	// Build the display lists for each letter of the fonts
	void _BuildFontLists(FontSettings Settings);
public:
	// Get information about the font
	FontSettings GetMetrics(void);
};
