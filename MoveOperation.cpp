#include "MoveOperation.h"

void MoveOperation::do_single_action_step(Forklift* forklift)
{
	if (!this->is_finished(forklift))
	{
		this->current_position += this->move_step;
	}
}

void MoveOperation::modify_matrix()
{
	glTranslatef(this->current_position, 0, 0);
}

bool MoveOperation::is_finished(Forklift* forklift)
{
	return abs(current_position - this->distance) <= 0.01f;
}
