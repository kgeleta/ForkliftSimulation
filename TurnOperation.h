#pragma once
#include "Operation.h"

class TurnOperation : public Operation
{
private:
	const float step = 0.5f;
	float current_angle;
	float angle_step;
	float angle;
	float radius;
public:
	explicit TurnOperation(TurnDirection turn_direction, MoveDirection move_direction, float angle) : current_angle(0.0f)
	{
		if (turn_direction == TurnDirection::Left)
		{
			this->radius = 10.0f;
			this->angle_step = move_direction == MoveDirection::Forward ? step : -step;
			this->angle = move_direction == MoveDirection::Forward ? angle : -angle;
		}
		else
		{
			this->radius = -10.0f;
			this->angle_step = move_direction == MoveDirection::Forward ? -step : step;
			this->angle = move_direction == MoveDirection::Forward ? -angle : angle;

		}

		this->save_operation_in_memory = true;
	}
	
	bool is_finished(Forklift* forklift) override;
	void do_single_action_step(Forklift* forklift) override;
	void modify_matrix() override;
};
