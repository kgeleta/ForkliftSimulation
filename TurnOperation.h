#pragma once
#include "Operation.h"

class TurnOperation : public Operation
{
private:
	float current_angle;
	float angle_step;
	float angle;
	float radius;
public:
	explicit TurnOperation(TurnDirection turn_direction, MoveDirection move_direction, float angle)
	{
		if (turn_direction == TurnDirection::Left)
		{
			this->radius = 10.0f;
			this->angle_step = move_direction == MoveDirection::Forward ? 0.5f : -0.5f;
			this->angle = move_direction == MoveDirection::Forward ? angle : -angle;
		}
		else
		{
			this->radius = -10.0f;
			this->angle_step = move_direction == MoveDirection::Forward ? -0.5f : 0.5f;
			this->angle = move_direction == MoveDirection::Forward ? -angle : angle;

		}
		
		this->save_operation_in_memory = true;
	}
	
	bool is_finished(Forklift* forklift) override;
	void do_single_action_step(Forklift* forklift) override;
	void modify_matrix() override;
};
