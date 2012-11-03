#include "Vector2.h"

Vector2::Vector2(void)
{
	Set(0,0);
}

Vector2::Vector2(int x, int y)
{
	Set(x, y);
}

Vector2::~Vector2(void)
{
}

void Vector2::Set(int newX, int newY)
{
	x = newX;
	y = newY;
}

bool Vector2::operator==(const Vector2 rhs)
{
	// compare
	if(x == rhs.x && y == rhs.y)
	{
		// equal
		return true;
	}

	// something didnt match
	return false;
}



//////////////////////////////////////////////////////////////////////////
Vector2f::Vector2f(void)
{
	Set(0,0);
}

Vector2f::Vector2f(float x, float y)
{
	Set(x, y);
}

Vector2f::~Vector2f(void)
{
}

void Vector2f::Set(float newX, float newY)
{
	x = newX;
	y = newY;
}

bool Vector2f::operator==(const Vector2f rhs)
{
	// compare
	if(x == rhs.x && y == rhs.y)
	{
		// equal
		return true;
	}

	// something didnt match
	return false;
}