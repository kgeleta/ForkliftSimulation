#pragma once
#include <vector>

#include "Operation.h"

class JobEntity
{
private:
	int shelf_index;
	int shelf_level;
	int pallet_position;
public:
	JobEntity(int shelf_index, int shelf_level, int pallet_position)
		: shelf_index(shelf_index),
		  shelf_level(shelf_level),
		  pallet_position(pallet_position)
	{
	}

	std::vector<Operation*> GenerateOperations();
};
