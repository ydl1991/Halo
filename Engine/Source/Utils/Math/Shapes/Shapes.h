#pragma once
// \file Shapes.h 
// TODO: File Purpose 
// Created by Dali Yi

//! \namespace halo Contains all Halo Engine code
namespace halo
{
	// \Strcut HaloRect 
	// A normal rect struct 
	struct Rect
	{
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //
		int x;
		int y;
		int w;
		int h;

		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		// Default Constructor 
		Rect() = default;
		Rect(int nx, int ny, int nw, int nh) : x{ nx }, y{ ny }, w{ nw }, h{ nh } {}

		// Default Destructor 
		~Rect() = default;
	};


	// \Strcut HaloFRect 
	// A rect struct with dimentions storedHaloFRect as float 
	struct FRect
	{
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //
		float x;
		float y;
		float w;
		float h;

		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		// Default Constructor 
		FRect() = default;
		FRect(float nx, float ny, float nw, float nh) : x{ nx }, y{ ny }, w{ nw }, h{ nh } {}

		// Default Destructor 
		~FRect() = default;
	};

	// \Strcut HaloPoint 
	// A point struct with dimentions as float 
	struct Point
	{
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //
		int x;
		int y;

		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		// Default Constructor 
		Point() = default;
		Point(int nx, int ny) : x{ nx }, y{ ny } {}

		// Default Destructor 
		~Point() = default;
	};



}