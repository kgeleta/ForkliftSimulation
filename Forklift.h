#pragma once
#include <queue>
#include "ModelHelper.h"
#include "Operation.h"
#include "Configuration.h"

#include "Point3D.h"

class Operation;
class Point3D;

class Forklift
{
private:
	ModelHelper* modelHelper;
	std::queue<Operation*> operations;
	std::vector<Operation*> memory;
	std::vector<int> shelf_indexes;
	Operation* current_operation;
	float mastPosition = -4.5f;
	float forksPosition = -4.5f;
	float positionX = 0.0f;
	float positionY = 0.3f;
	float positionZ = 0.0f;
	bool draw_pallet_on_fork = false;
	bool draw_pallet_on_ground = true;
	int time = 0;
	int currentShelfIndex = 1;

public:
	Forklift(ModelHelper* _modelHelper, std::queue<Operation*> _operations, std::vector<int> _shelfIndexes);
	void InvokeAction();

	void add_current_pallet_to_memory();

	float mast_position() const
	{
		return mastPosition;
	}

	void set_mast_position(float mast_position)
	{
		mastPosition = mast_position;
	}

	float forks_position() const
	{
		return forksPosition;
	}

	void set_forks_position(float forks_position)
	{
		forksPosition = forks_position;
	}

	float position_x() const
	{
		return positionX;
	}

	void set_position_x(float position_x)
	{
		positionX = position_x;
	}

	float position_y() const
	{
		return positionY;
	}

	void set_position_y(float position_y)
	{
		positionY = position_y;
	}

	float position_z() const
	{
		return positionZ;
	}

	void set_position_z(float position_z)
	{
		positionZ = position_z;
	}


	bool is_draw_pallet() const
	{
		return draw_pallet_on_fork;
	}

	void set_draw_pallet_on_fork(bool draw_pallet)
	{
		this->draw_pallet_on_fork = draw_pallet;
	}

	// int get_current_shelf_index() const
	// {
	// 	return currentShelfIndex;
	// }
	//
	// void set_current_shelf_index(int current_shelf_index)
	// {
	// 	currentShelfIndex = current_shelf_index;
	// }

	void next_shelf_index()
	{
		currentShelfIndex++;
	}
	

	bool is_draw_pallet_on_ground() const
	{
		return draw_pallet_on_ground;
	}

	void set_draw_pallet_on_ground(bool draw_pallet_on_ground)
	{
		this->draw_pallet_on_ground = draw_pallet_on_ground;
	}
};