#pragma once

class CVector4
{
public:
	//constructors
	CVector4(void)	:	x(0.0f), y(0.0f), z(0.0f), w(0.0f)
	{}

	CVector4(float newX, float newY, float newZ, float newW)	
		:	x(newX), y(newY), z(newZ), w(newW)
	{}

	~CVector4(void) { };	// empty

	//convert v3d to v4d
	/*CVector4(const CVector3 & rhs):	x(rhs.x), y(rhs.y), z(rhs.z), w(1.0f)
	{}*/

	//cast to pointer to float for glVertex4fv etc
	operator float* () const {return (float*) this;}
	operator const float* () const {return (const float*) this;}


	//member variables
	float x;
	float y;
	float z;
	float w;
};
