#pragma once
#include "Operation.h"
class PickUpPalletOperation :
	public Operation
{
public:
	PickUpPalletOperation() = default;
	bool is_finished(Forklift* forklift) override;
	void do_single_action_step(Forklift* forklift) override;
};