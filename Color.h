#pragma once

struct Color
{
	float red;
	float green;
	float blue;

	Color(float red, float green, float blue)
		: red(red),
		  green(green),
		  blue(blue)
	{
	}

	Color() : red(1.0f),
		green(1.0f),
		blue(1.0f){}
};
