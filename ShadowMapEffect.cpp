#include "ShadowMapEffect.h"

#include "NeHeGL.h"		// for g_window




ShadowMapEffect::ShadowMapEffect(void)
: m_ShadowMapEnabled(false)
{
}

ShadowMapEffect::~ShadowMapEffect(void)
{
}

// setup the shadow map effect if the hardware supports it
void ShadowMapEffect::SetupEffect(void)
{
	m_ShadowMapEnabled = false;
	m_ShadowMapSize = 512;
	m_CameraPosition = g_camera->Position();
	m_LightPosition = CVector3(2.0f, 3.0f,-2.0f);

	//Check for necessary extensions
	if(!GLEE_ARB_depth_texture || !GLEE_ARB_shadow)
	{
		// printf("I require ARB_depth_texture and ARB_shadow extensionsn\n");
		return; // return with m_ShadowMapEnabled = false
	}

	//Load identity modelview
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Create the shadow map texture
	//////////////////////////////////////////////////////////////////////////
	glGenTextures(1, &m_ShadowMapTexture);
	glBindTexture(GL_TEXTURE_2D, m_ShadowMapTexture);
	glTexImage2D( GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_ShadowMapSize, m_ShadowMapSize, 0,
		GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);


	//Use the color as the ambient and diffuse material
	//////////////////////////////////////////////////////////////////////////
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	//White specular material color, shininess 16
	float white[] = {1.0f, 1.0f, 1.0f, 1.0f};
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialf(GL_FRONT, GL_SHININESS, 16.0f);


	//Calculate & save matrices
	//////////////////////////////////////////////////////////////////////////
	glPushMatrix();

	glLoadIdentity();
	gluPerspective(45.0f, (float)g_window->init.width/g_window->init.height, 1.0f, 100.0f);
	glGetFloatv(GL_MODELVIEW_MATRIX, m_CameraProjectionMatrix);

	glLoadIdentity();
	gluLookAt(m_CameraPosition.x, m_CameraPosition.y, m_CameraPosition.z,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);
	glGetFloatv(GL_MODELVIEW_MATRIX, m_CameraViewMatrix);

	glLoadIdentity();
	gluPerspective(45.0f, 1.0f, 2.0f, 8.0f);
	glGetFloatv(GL_MODELVIEW_MATRIX, m_LightProjectionMatrix);

	glLoadIdentity();
	gluLookAt( m_LightPosition.x, m_LightPosition.y, m_LightPosition.z,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);
	glGetFloatv(GL_MODELVIEW_MATRIX, m_LightViewMatrix);

	glPopMatrix();


	// enabled
	m_ShadowMapEnabled = true;
}

// TODO - refresh camera matrix on
//	- camera move
//  - fullscreen swap
//  - window resize

void ShadowMapEffect::RenderFirstPass(void)
{
	//First pass - from light's point of view
	//////////////////////////////////////////////////////////////////////////
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(m_LightProjectionMatrix);

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(m_LightViewMatrix);

	//Use viewport the same size as the shadow map
	glViewport(0, 0, m_ShadowMapSize, m_ShadowMapSize);

	//Draw back faces into the shadow map
	glCullFace(GL_FRONT);

	//Disable color writes, and use flat shading for speed
	glShadeModel(GL_FLAT);
	glColorMask(0, 0, 0, 0);
}

void ShadowMapEffect::RenderSecondPass(void)
{
	//Read the depth buffer into the shadow map texture
	glBindTexture(GL_TEXTURE_2D, m_ShadowMapTexture);
	glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, m_ShadowMapSize, m_ShadowMapSize);

	//restore states
	glCullFace(GL_BACK);
	glShadeModel(GL_SMOOTH);
	glColorMask(1, 1, 1, 1);


	//2nd pass - Draw from camera's point of view
	//////////////////////////////////////////////////////////////////////////
	glClear(GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(m_CameraProjectionMatrix);

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(m_CameraViewMatrix);

	glViewport(0, 0, g_window->init.width, g_window->init.height);

	// setup some colors
	// TODO find a better place to store these
	float darkwhite[] = {0.2f, 0.2, 0.2, 0.2f};
	float black[] = {0.0f, 0.0f, 0.0f, 1.0f};

	//Use dim light to represent shadowed areas
	glLightfv(GL_LIGHT1, GL_POSITION, CVector3(m_LightPosition));
	glLightfv(GL_LIGHT1, GL_AMBIENT, darkwhite);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, darkwhite);
	glLightfv(GL_LIGHT1, GL_SPECULAR, black);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);

}

void ShadowMapEffect::RenderThirdPass(void)
{
	// setup some colors
	// TODO find a better place to store these
	float white[] = {1.0f, 1.0f, 1.0f, 1.0f};
	float black[] = {0.0f, 0.0f, 0.0f, 1.0f};

	//3rd pass - Draw with bright light
	//////////////////////////////////////////////////////////////////////////
	glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT1, GL_SPECULAR, white);

	//Calculate texture matrix for projection
	//This matrix takes us from eye space to the light's clip space
	//It is postmultiplied by the inverse of the current view matrix when specifying texgen
	static Matrix4x4 biasMatrix(0.5f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f); //bias from [-1, 1] to [0, 1]
	Matrix4x4 m_TextureMatrix=biasMatrix*m_LightProjectionMatrix*m_LightViewMatrix;

	//Set up texture coordinate generation.
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTexGenfv(GL_S, GL_EYE_PLANE, m_TextureMatrix.GetRow(0));
	glEnable(GL_TEXTURE_GEN_S);

	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTexGenfv(GL_T, GL_EYE_PLANE, m_TextureMatrix.GetRow(1));
	glEnable(GL_TEXTURE_GEN_T);

	glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTexGenfv(GL_R, GL_EYE_PLANE, m_TextureMatrix.GetRow(2));
	glEnable(GL_TEXTURE_GEN_R);

	glTexGeni(GL_Q, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTexGenfv(GL_Q, GL_EYE_PLANE, m_TextureMatrix.GetRow(3));
	glEnable(GL_TEXTURE_GEN_Q);


	//Bind & enable shadow map texture
	//////////////////////////////////////////////////////////////////////////
	glBindTexture(GL_TEXTURE_2D, m_ShadowMapTexture);
	glEnable(GL_TEXTURE_2D);

	//Enable shadow comparison
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE);

	//Shadow comparison should be true (ie not in shadow) if r<=texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL);

	//Shadow comparison should generate an INTENSITY result
	glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE_ARB, GL_INTENSITY);

	//Set alpha test to discard false comparisons
	glAlphaFunc(GL_GEQUAL, 0.99f);
	glEnable(GL_ALPHA_TEST);
}

void ShadowMapEffect::RenderCleanUp(void)
{
	// Clean Up
	//////////////////////////////////////////////////////////////////////////
	//Disable textures and texgen
	glDisable(GL_TEXTURE_2D);

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_R);
	glDisable(GL_TEXTURE_GEN_Q);

	//Restore other states
	glDisable(GL_LIGHTING);
	glDisable(GL_ALPHA_TEST);
}
