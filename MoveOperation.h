#pragma once
#include "Operation.h"

class MoveOperation :
	public Operation
{
private:
	MoveDirection move_direction;
	float move_step;
	float start_position;
	float distance;
	bool initialized;
public:

	explicit MoveOperation(MoveDirection move_direction, float distance) : move_direction(move_direction), distance(distance)
	{
		this->move_step = distance >= 0 ? 0.1f : -0.1f;
		this->initialized = false;
	}

	bool is_finished(Forklift* forklift) override;
	void do_single_action_step(Forklift* forklift) override;
};
