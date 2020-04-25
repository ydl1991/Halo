#pragma once
// \file Vector2D.h 
// TODO: File Purpose 
// Created by Dali Yi


//! \namespace halo Contains all Halo Engine code
namespace halo
{
	// \class Vector2D 
	// TODO: Class Purpose 
	class Vector2D
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //
		float m_x;
		float m_y;

		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		// Default Constructor 
		Vector2D(float x, float y);

		// Default Destructor 
		~Vector2D();

		// Functions
		Vector2D Normalize();
		float SqrMagnitude();
		float Dot(const Vector2D& vector);

		// Operator Overload
		Vector2D operator*(float scalar) { return Vector2D{ m_x * scalar, m_y * scalar }; }
		Vector2D operator+(const Vector2D& vector) { return Vector2D{ m_x + vector.m_x, m_y + vector.m_y }; }
		Vector2D operator-(const Vector2D& vector) { return Vector2D{ m_x - vector.m_x, m_y - vector.m_y }; }
	};

}