#include "MoveOperation.h"

void MoveOperation::do_single_action_step(Forklift* forklift)
{
	float current_position = 0.0f;
	
	switch (this->move_direction)
	{
	case MoveDirection::X:
		current_position = forklift->position_x();
		forklift->set_position_x(current_position + this->move_step);
		break;
	case MoveDirection::Y:
		current_position = forklift->position_y();
		forklift->set_position_y(current_position + this->move_step);
		break;
	case MoveDirection::Z:
		current_position = forklift->position_z();
		forklift->set_position_z(current_position + this->move_step);
		break;
	}

	if (!this->initialized)
	{
		this->start_position = current_position;
		this->initialized = true;
	}
}

bool MoveOperation::is_finished(Forklift* forklift)
{
	float current_position = 0.0f;

	switch (this->move_direction)
	{
	case MoveDirection::X:
		current_position = forklift->position_x();
		break;
	case MoveDirection::Y:
		current_position = forklift->position_y();
		break;
	case MoveDirection::Z:
		current_position = forklift->position_z();
		break;
	}
	
	return this->initialized && abs(current_position - this->start_position) >= abs(this->distance);
}
