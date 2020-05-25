#include "Idle.h"

void Idle::do_single_action_step(Forklift* forklift)
{
	if (!this->is_finished(forklift))
	{
		this->timePassed += 1;
	}
}

void Idle::modify_matrix()
{
}

bool Idle::is_finished(Forklift* forklift)
{
	return timePassed >= waitTime;
}