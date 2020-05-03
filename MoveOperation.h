#pragma once
#include "Operation.h"

class MoveOperation :
	public Operation
{
private:
	float move_step;
	float current_position;
	float distance;
public:

	explicit MoveOperation(MoveDirection move_direction, float distance) : current_position(0.0f)
	{
		this->move_step = move_direction == MoveDirection::Forward ? -0.1f : 0.1f;
		this->distance = move_direction == MoveDirection::Forward ? -distance : distance;
		this->save_operation_in_memory = true;
	}

	bool is_finished(Forklift* forklift) override;
	void do_single_action_step(Forklift* forklift) override;
	void modify_matrix() override;
};
