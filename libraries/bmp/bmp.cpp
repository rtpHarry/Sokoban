//--------------------------------------------------------------
#include <windows.h>		// Header File For Windows - has structures for BMP format
#include <stdio.h>	    	// Header File For Standard Input/Output
#include <stdlib.h>
#include "BMP.h"

/*------------------------------------------------------------------
 BMP Loader - a quick and dirty substitute for GLaux 
 if you only use GLaux to load BMP files will load any format of a 
 windows DIB BMP format graphics file Only works on a windows box   
 Caution! memory for the data is allocated using 'new'.  
 In the NeHe tutorials the memory is reclaimed using 'free'.   
 For the small tutorials its not a big deal but not a good practice in 
 larger projects (heap trashing not good). J.M. Doyle : 12 Jan 2003
------------------------------------------------------------------*/

AUX_RGBImageRec *auxDIBImageLoad(const char *FileName)
{ 
	 return new AUX_RGBImageRec(FileName);
}


void AUX_RGBImageRec::convertBGRtoRGB()
{
	const DWORD BitmapLength = sizeX * sizeY * 3;
	byte Temp;  // not quick but it works  
	for(DWORD i=0; i< BitmapLength; i += 3) 
	{
	    Temp = data[i];
	    data[i] = data[i+2];
	    data[i+2] = Temp;
	    }
	}

AUX_RGBImageRec::AUX_RGBImageRec(const char *FileName): data(NULL), NoErrors(false)
{ 
 loadFile(FileName);
}

AUX_RGBImageRec::~AUX_RGBImageRec()
{
  if (data != NULL) delete data;
  data = NULL;
}

bool AUX_RGBImageRec::loadFile(const char* Filename)
{
	BITMAPINFO BMInfo;								// need the current OpenGL device contexts in order to make use of windows DIB utilities  
	const HDC gldc = wglGetCurrentDC();   			// a handle for the current OpenGL Device Contexts
					  								// assume there are errors until file is loaded successfully into memory  
	NoErrors = false;  								// release old data since this object could be used to load multiple Textures  
	if(data != NULL) delete data;					// windows needs this info to determine what header info we are looking for  
	BMInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);  // Get windows to determine color bit depth in the file for us  
	BMInfo.bmiHeader.biBitCount = 0;				// Get windows to open and load the BMP file and handle the messy decompression if the file is compressed  
													// assume perfect world and no errors in reading file, Ha Ha  
	HANDLE DIBHandle = LoadImage(0,Filename, IMAGE_BITMAP, 0, 0,LR_DEFAULTCOLOR | LR_CREATEDIBSECTION | LR_LOADFROMFILE);  // use windows to get header info of bitmap - assume no errors in header format 

	GetDIBits(gldc, (HBITMAP)DIBHandle, 0,0, NULL, &BMInfo, DIB_RGB_COLORS);
	sizeX = BMInfo.bmiHeader.biWidth;
	sizeY = BMInfo.bmiHeader.biHeight;				// change color depth to 24 bits (3 bytes (BGR) / pixel)  
	BMInfo.bmiHeader.biBitCount = 24;				// don't want the data compressed  
	BMInfo.bmiHeader.biCompression = BI_RGB;  
	const DWORD BitmapLength = sizeX * sizeY * 3;	// 3 bytes (BGR) per pixel (24bp)  
													// allocate enough memory to hold the pixel data in client memory  
	data = new byte[BitmapLength];					// Get windows to do the dirty work of converting the BMP into the format needed by OpenGL  
													// if file is already 24 bit color then this is a waste of time but makes for short code  
													// Get the actual Texel data from the BMP object  
	
	if (GetDIBits(gldc, (HBITMAP)DIBHandle, 0, sizeY, data, &BMInfo, DIB_RGB_COLORS)) 
	{
		NoErrors = true;
		convertBGRtoRGB();							// NOTE: BMP is in BGR format but OpenGL needs RGB unless you use GL_BGR_EXT
	}

	DeleteObject(DIBHandle);						// don't need the BMP Object anymore  
	return NoErrors;
}        
