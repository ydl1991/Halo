#pragma once

namespace MathHelper
{
#include <math.h>
#include <Utils/Math/Vectors/Vector2D.h>

	// Sprite Rotation
	float SpriteRotation(const halo::Vector2D& dir)
	{
		// unit vector of my sprite facing direction
		halo::Vector2D north{ 0.f, -1.f };
		// calculate rotation
		float cosinTheta = north.Dot(dir);
		float angle = ((acosf(cosinTheta) * 180.f) / 3.141592653589f);
		if (dir.m_x < 0)
		{
			angle = 360 - angle;
		}
		return angle;
	}

	// Sqr Magnitude between 2 Vectors
	float SqrMagnitude(const halo::Vector2D& from, const halo::Vector2D& to)
	{
		// edge case if calculate magnitude at the same point
		if (from.m_x == to.m_x && from.m_y == to.m_y)
		{
			return 0.f;
		}

		// object space
		float xLength = from.m_x - to.m_x;
		float yLength = from.m_y - to.m_y;
		float squareSum = xLength * xLength + yLength * yLength;
		return squareSum;
	}

	// Normalize 2 Vectors
	halo::Vector2D Normalize(const halo::Vector2D& from, const halo::Vector2D& to)
	{
		// calculate x, y differences between 2 vector2D
		float xLength = to.m_x - from.m_x;
		float yLength = to.m_y - from.m_y;
		// calculate magnitude
		float sqrMagnitude = SqrMagnitude(from, to);
		if (sqrMagnitude == 0)
		{
			return halo::Vector2D{ 0,0 };
		}
		// normalize the vector and store the direction in m_motion
		float x = (xLength / sqrtf(sqrMagnitude));
		float y = (yLength / sqrtf(sqrMagnitude));
		return halo::Vector2D{ x, y };
	}
}