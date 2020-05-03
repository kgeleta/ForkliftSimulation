#pragma once
#include "Operation.h"
class LeavePalletOperation :
	public Operation
{
public:
	bool is_finished(Forklift* forklift) override;
	void do_single_action_step(Forklift* forklift) override;
	void modify_matrix() override;
};

