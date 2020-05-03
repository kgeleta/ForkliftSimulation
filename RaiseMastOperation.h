#pragma once
#include "Operation.h"
#include <stdlib.h>

class RaiseMastOperation :
	public Operation
{
private:
	const float RAISING_STEP = 0.02f;
	float max_mast_height;
	float max_forks_height;
public:
	RaiseMastOperation(ShelfLevel shelf_level);
	bool is_finished(Forklift* forklift) override;
	void do_single_action_step(Forklift* forklift) override;
	void modify_matrix() override;
};

