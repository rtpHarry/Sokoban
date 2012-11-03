#pragma once

class Vector2
{
public:
	int x;
	int y;

public:
	Vector2(void);
	Vector2(int x, int y);
	~Vector2(void);

	void Set(int newX, int newY);
	bool operator==(const Vector2 rhs);

};




//////////////////////////////////////////////////////////////////////////
class Vector2f
{
public:
	float x;
	float y;

public:
	Vector2f(void);
	Vector2f(float x, float y);
	~Vector2f(void);

	void Set(float newX, float newY);
	bool operator==(const Vector2f rhs);

};