// Camera.h: interface for the CCamera class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CAMERA_H__E4571EB4_1D90_4482_B860_117BD1F17214__INCLUDED_)
#define AFX_CAMERA_H__E4571EB4_1D90_4482_B860_117BD1F17214__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "Vector3.h"

//////////////////////////////////////////////////////////////////////////
// Maths
// math utility functions
CVector3 Cross(CVector3 vVector1, CVector3 vVector2);
float Magnitude(CVector3 vNormal);
CVector3 Normalize(CVector3 vVector);

//////////////////////////////////////////////////////////////////////////

struct CameraOrientation
{
	CVector3 m_Position;
	CVector3 m_View;
};

#define kSpeed 0.02

// CCamera
///////////
// A camera class for easier control of movement within an openGL world
////////////////////////
class CCamera  
{

public:
	// access functions for member variables
	CVector3 Position() {	return m_vPosition;		}
	CVector3 View()		{	return m_vView;			}
	CVector3 UpVector() {	return m_vUpVector;		}
	CVector3 Strafe()	{	return m_vStrafe;		}

	// default contructor / destructor
	CCamera();
	virtual ~CCamera();

	// put a camera in a specific position
	void PositionCamera	(float positionX, float positionY, float positionZ, float viewX, float viewY, float viewZ, float upVectorX, float upVectorY, float upVectorZ);

	// This type of viewing is used in most first person games.  
	//////////////
	// call from key check function
	void SetViewByMouse();

	// this performs an axis-angle rotation around the camera's position
	//////////////
	// usage : positive number = left
	//		   negative number = right
	void RotateView(float angle, float x, float y, float z);

	// rotate around a point, an object or third person camera model
	void RotateAroundPoint(CVector3 vCenter, float angle, float x, float y, float z);

	// This strafes the camera left or right depending on the speed (+/-) 
	void StrafeCamera(float speed);

	// This checks for keyboard movement
	// not in use :: currently handled by update() function in main app
	void CheckForMovement();

	// This uses gluLookAt() to tell OpenGL where to look
	void Look();

	// This updates the camera's view and other data (Should be called each frame)
	void Update();

	// move camera forwards or backwards
	/////////////
	// usage : positive number = forwards
	//         negative number = backwards
	void MoveCamera (float speed);

private:
	// camera's location and orientation
	CVector3 m_vPosition;
	CVector3 m_vView;
	CVector3 m_vUpVector;
	CVector3 m_vStrafe;

	bool m_bMouseControlOn;

public:
	// Toggle if the mouse controls the camera
	void ToggleMouseControl(void);

	// dumps the camera position to a file
	void DEBUG_WritePositionToFile(void);
};

#endif // !defined(AFX_CAMERA_H__E4571EB4_1D90_4482_B860_117BD1F17214__INCLUDED_)
