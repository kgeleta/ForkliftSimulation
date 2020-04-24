#pragma once
#include "Operation.h"

class LowerMastOperation :
	public Operation
{
private:
	const float LOWERING_STEP = 0.1f;
	const float MIN_MAST_HEIGHT = -4.5f;
	const float MIN_FORKS_HEIGHT = -4.5f;
public:
	LowerMastOperation() = default;
	bool is_finished(Forklift* forklift) override;
	void do_single_action_step(Forklift* forklift) override;
};