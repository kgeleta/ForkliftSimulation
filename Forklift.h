#pragma once
#include <queue>
#include "ModelHelper.h"
#include "Operation.h"
#include "Point3D.h"

class Operation;
class Point3D;

class Forklift
{
private:
	std::vector<Point3D> palletsPositions;
	ModelHelper* modelHelper;
	std::queue<Operation*> operations;
	Operation* current_operation;
	float mastPosition = -4.5f;
	float forksPosition = -4.5f;
	float positionX = 0.0f;
	float positionY = 0.3f;
	float positionZ = 0.0f;
	bool draw_pallet = true;
	int time = 0;

public:
	Forklift(ModelHelper* _modelHelper);
	void InvokeAction();

	void add_current_pallet();

	void draw_all_pallets();
	
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
		return draw_pallet;
	}

	void set_draw_pallet(bool draw_pallet)
	{
		this->draw_pallet = draw_pallet;
	}
};