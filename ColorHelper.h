#pragma once
#include <map>
#include <ctime>

#include "Color.h"

class ColorHelper
{
private:
	static std::map<int, Color> color_memory;
	static bool initialized;
	static Color get_random_color();
public:
	static Color get_color_for_shelf(int shelfIndex);
};