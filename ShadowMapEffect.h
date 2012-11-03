#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include "GLee.h"
#include <gl/GLU.h>
//#include <gl\gl.h>
//#include <gl/GLee.h> // gl extension loader [gl.h is included with this]

// need to know window dimensions
// need to know camera positions

#include "Matrix4x4.h"
#include "Vector3.h"

class ShadowMapEffect
{
public:
	ShadowMapEffect(void);
	~ShadowMapEffect(void);

	// is the shadow map effect being used
	bool m_ShadowMapEnabled;

	// TODO add a hook to keep it in sync with real camera
	CVector3 m_CameraPosition;
	CVector3 m_LightPosition;

	//Size of shadow map
	// TODO make this a const
	int m_ShadowMapSize;

	//Textures
	GLuint m_ShadowMapTexture;

	//Matrices
	Matrix4x4 m_LightProjectionMatrix, m_LightViewMatrix;
	Matrix4x4 m_CameraProjectionMatrix, m_CameraViewMatrix;
public:
	// setup the shadow map effect if the hardware supports it
	void SetupEffect(void);
public:
	void RenderFirstPass(void);
public:
	void RenderSecondPass(void);
public:
	void RenderThirdPass(void);
public:
	void RenderCleanUp(void);
};