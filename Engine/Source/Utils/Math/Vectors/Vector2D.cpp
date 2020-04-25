#include "Vector2D.h"

#include <math.h>

using halo::Vector2D;

Vector2D::Vector2D(float x, float y)
	: m_x{ x }
	, m_y{ y }
{
	
}

Vector2D::~Vector2D()
{
	
}

//----------------------------------//
//		Normalize This Vector
//----------------------------------//
Vector2D halo::Vector2D::Normalize()
{
	// calculate magnitude
	float sqrMagnitude = SqrMagnitude();
	// normalize the vector and store the direction in m_motion
	float x = (m_x / sqrtf(sqrMagnitude));
	float y = (m_y / sqrtf(sqrMagnitude));
	return halo::Vector2D{ x, y };
}

//----------------------------------//
//		Get Magnitude
//----------------------------------//
float halo::Vector2D::SqrMagnitude()
{
	float squareSum = m_x * m_x + m_y * m_y;
	return squareSum;
}

//----------------------------------//
//			Dot Product
//----------------------------------//
float halo::Vector2D::Dot(const Vector2D& vector)
{
	return m_x * vector.m_x + m_y * vector.m_y;
}

