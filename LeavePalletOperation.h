#pragma once
#include "Operation.h"
class LeavePalletOperation :
	public Operation
{

private:
	int shelfIndex;
public:

	explicit LeavePalletOperation(int shelf_index)
		: shelfIndex(shelf_index)
	{
	}

	bool is_finished(Forklift* forklift) override;
	void do_single_action_step(Forklift* forklift) override;
	void modify_matrix() override;
};

