#pragma once
// \file Color.h 
// TODO: File Purpose 
// Created by Dali Yi

#include <stdint.h>

//! \namespace halo Contains all Halo Engine code
namespace halo
{
	// \struct Color 
	// TODO: struct Purpose 
	struct Color
	{
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;

		Color() = default;
		Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) : r{ red }, g{ green }, b{ blue }, a{ alpha } {}
		~Color() = default;
	};
}