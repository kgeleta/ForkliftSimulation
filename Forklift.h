#pragma once
#include <queue>

#include "ModelHelper.h"
#include "Operation.h"

class Operation;

class Forklift
{
private:
	ModelHelper* modelHelper;
	std::queue<Operation*> operations;
	Operation* current_operation;
	float mastPosition = -4.5f;
	float forksPosition = -4.5f;
	float positionX = 0.0f;
	float positionY = 0.3f;
	float positionZ = 0.0f;

	int time = 0;

public:
	Forklift(ModelHelper* _modelHelper);
	void InvokeAction();
	
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
};