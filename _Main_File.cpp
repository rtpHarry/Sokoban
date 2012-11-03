#define WIN32_LEAN_AND_MEAN
#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations

#include "GLee.h"
//#include <gl\GLee.h> // gl extension loader [gl.h is included with this]
//#include <gl\gl.h>												// OpenGL library
//#include <gl\glu.h>												// OpenGL utility library

#include <il\il.h>												// DevIL Image Library
#include <il\ilu.h>
#include <il\ilut.h>

#include <al\alut.h>											// OpenAL wrapper/utility library

#include "NeHeGL.h"												// Header File For NeHeGL

#ifdef _MSC_VER
	#pragma comment( lib, "opengl32.lib" )							// Search For OpenGL32.lib While Linking
	#pragma comment( lib, "glu32.lib" )								// Search For GLu32.lib While Linking
	//#pragma comment( lib, "glaux.lib" )								// Search For GLu32.lib While Linking
	#pragma comment( lib, "winmm.lib" )								// Search For WinMM Library While Linking
	#pragma comment( lib, "devil.lib" )								// DevIL Image Library
	#pragma comment( lib, "ilut.lib" )								// DevIL Image Library
	#pragma comment( lib, "ilu.lib" )								// DevIL Image Library
	#pragma comment( lib, "openal32.lib" )							// OpenAL library
	#pragma comment( lib, "alut.lib" )								// OpenAL wrapper/utility library
#endif

#ifdef  _DEBUG
#define IL_DEBUG
#endif //_DEBUG

#ifndef		CDS_FULLSCREEN										// CDS_FULLSCREEN Is Not Defined By Some
#define		CDS_FULLSCREEN 4									// Compilers. By Defining It This Way,
#endif															// We Can Avoid Errors

GL_Window*	g_window;
Keys*		g_keys;
CCamera*	g_camera;

char	appTitle[] = "Sokoban by rtp|software";	//stores the window title
int		screenInfo[3] = {1024,768,32};		//stores resolution and color bits (w,h,bpp)

// User Defined Variables
//#include "FontGL.h"
#include "SokobanApp.h"

SokobanApp Sokoban;

BOOL Initialize (GL_Window* window, Keys* keys, CCamera* camera)	// Any OpenGL Initialization Goes Here
{
	g_window	= window;
	g_keys		= keys;
	g_camera	= camera;

	// setup the sokoban application
	//////////////////////////////////////////////////////////////////////////
	Sokoban.Setup();
	//////////////////////////////////////////////////////////////////////////


	return TRUE;												// Return TRUE (Initialization Successful)
}

void Deinitialize (void)										// Any User DeInitialization Goes Here
{
	// shut down the sokoban application
	//////////////////////////////////////////////////////////////////////////
	Sokoban.Destroy();
}

//handles keyboard processing
void ProcessKeys(void)
{
	// debug keys
	//////////////////////////////////////////////////////////////////////////
	if (g_keys->keyDown[VK_F4])		{	ToggleFullscreen (g_window);			}
	if (g_keys->keyDown[VK_F11])	{	g_camera->ToggleMouseControl();	g_keys->keyDown[VK_F11] = FALSE;	}
	if (g_keys->keyDown[VK_F12])	{	g_camera->DEBUG_WritePositionToFile(); g_keys->keyDown[VK_F12] = FALSE;	}

	// pass all pressed keys into the 
	for(int index = 0; index <= 256; index++)
	{
		if(g_keys->keyDown[index])
		{
			Sokoban.KeyPressed((char) index);

			g_keys->keyDown[index] = false;
		}
	}

}

void Update(void)									// Perform Motion Updates Here
{
	// Color fading background
	//////////////////////////////////////////////////////////////////////////
/*
		static float color = 0.0f;
		static float color2 = 0.3f;
	
		color += 0.0005f;
		color2 += 0.00005f;
	
		if (color > 0.5f) {color = 0.0f; color2 = 0.3f; }
		//if (color2 > 0.7f) color = 0.3f;
	
		glClearColor(0.0f, color, color2, 0.0f);
*/	
	//////////////////////////////////////////////////////////////////////////
	

	ProcessKeys();

	// update sound
	//////////////////////////////////////////////////////////////////////////
	SokobanSoundManager::Instance().Update();

	g_camera->Update();
}

void DrawScene(void)											// Draw Our Scene
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear Screen And Depth Buffer
	glLoadIdentity();											// Reset The Modelview Matrix

	g_camera->Look();

	//////////////////////////////////////////////////////////////////////////
	
	Sokoban.Render();
	
	//////////////////////////////////////////////////////////////////////////
	

	glFlush();													// Flush The GL Rendering Pipeline
}
