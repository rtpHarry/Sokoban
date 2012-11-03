#pragma once

#include "Vector4.h"

class Matrix4x4
{
public:
	Matrix4x4()
	{	LoadIdentity();	}
	Matrix4x4(	float e0, float e1, float e2, float e3,
		float e4, float e5, float e6, float e7,
		float e8, float e9, float e10, float e11,
		float e12, float e13, float e14, float e15);
	Matrix4x4(const Matrix4x4 & rhs);

	~Matrix4x4(void) { }; // empty

	// for default constructor
	void LoadIdentity(void);

	CVector4 GetRow(int position) const;

	// multiply a matrix by a matrix
	Matrix4x4 operator*(const Matrix4x4 & rhs) const;

	//cast to pointer to a (float *) for glGetFloatv etc
	operator float* () const {return (float*) this;}
	operator const float* () const {return (const float*) this;}

	//member variables
	float entries[16];
};
