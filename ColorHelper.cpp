#include "ColorHelper.h"

std::map<int, Color> ColorHelper::color_memory;
bool ColorHelper::initialized = false;

Color ColorHelper::get_color_for_shelf(int shelfIndex)
{
	if (color_memory.count(shelfIndex))
	{
		return color_memory[shelfIndex];
	}

	color_memory[shelfIndex] = get_random_color();
	return color_memory[shelfIndex];
}


Color ColorHelper::get_random_color()
{
	if (!initialized)
	{
		srand(static_cast <unsigned> (time(0)));
		initialized = true;
	}
	
	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	
	return {r, g, b};
}
