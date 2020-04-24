#include "LowerMastOperation.h"

bool LowerMastOperation::is_finished(Forklift* forklift)
{
	return abs(forklift->forks_position() - this->MIN_FORKS_HEIGHT) <= this->LOWERING_STEP && abs(
		forklift->mast_position() - this->MIN_MAST_HEIGHT) <= this->LOWERING_STEP;
}

void LowerMastOperation::do_single_action_step(Forklift* forklift)
{
	if (forklift->mast_position() >= this->MIN_MAST_HEIGHT)
	{
		forklift->set_mast_position(forklift->mast_position() - this->LOWERING_STEP);
	}
	else if (forklift->forks_position() >= this->MIN_FORKS_HEIGHT)
	{
		forklift->set_forks_position(forklift->forks_position() - this->LOWERING_STEP);
	}
}