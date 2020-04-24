#pragma once
#include "Operation.h"

class MoveXOperation :
	public Operation
{
private:
	float move_step;
	float start_position;
	float distance;
public:
	bool is_finished(Forklift* forklift) override;
	void do_single_action_step(Forklift* forklift) override;
};
