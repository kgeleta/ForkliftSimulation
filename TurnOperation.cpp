#include "TurnOperation.h"

bool TurnOperation::is_finished(Forklift* forklift)
{
	return abs(this->current_angle - this->angle) <= abs(this->angle_step);
}

void TurnOperation::do_single_action_step(Forklift* forklift)
{
	if (!this->is_finished(forklift))
	{
		this->current_angle += this->angle_step;
	}
}

//void TurnOperation::modify_matrix()
//{
//	glTranslatef(0.0f, 0.0f, this->radius);
//	glRotatef(this->current_angle, 0, 1, 0);
//	glTranslatef(0.0f, 0.0f, -this->radius);
//}

void TurnOperation::modify_matrix()
{
	glTranslatef(0.0f, 0.0f, this->radius);
	if (!this->is_finished(nullptr))
	{
		glRotatef(this->current_angle, 0, 1, 0);
	}
	else
	{
		glRotatef(this->angle, 0, 1, 0);
	}
	glTranslatef(0.0f, 0.0f, -this->radius);
}