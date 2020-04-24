#include "RaiseMastOperation.h"

RaiseMastOperation::RaiseMastOperation(ShelfLevel shelf_level)
{
	switch (shelf_level)
	{
	case ShelfLevel::Level0:
		max_mast_height = -4.5f;
		max_forks_height = -1.9f;
		break;
	case ShelfLevel::Level1:
		max_mast_height = -3.3f;
		max_forks_height = 0.0f;
		break;
	case ShelfLevel::Level2:
		max_mast_height = 0.0f;
		max_forks_height = 0.0f;
		break;
	}
}

bool RaiseMastOperation::is_finished(Forklift* forklift)
{
	return abs(forklift->forks_position() - this->max_forks_height) <= this->RAISING_STEP && abs(
		forklift->mast_position() - this->max_mast_height) <= this->RAISING_STEP;
}

void RaiseMastOperation::do_single_action_step(Forklift* forklift)
{
	if (forklift->forks_position() <= this->max_forks_height)
	{
		forklift->set_forks_position(forklift->forks_position() + this->RAISING_STEP);
	}
	else if (forklift->mast_position() <= this->max_mast_height)
	{
		forklift->set_mast_position(forklift->mast_position() + this->RAISING_STEP);
	}
}
