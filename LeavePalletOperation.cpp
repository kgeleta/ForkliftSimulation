#include "LeavePalletOperation.h"

bool LeavePalletOperation::is_finished(Forklift* forklift)
{
	return !forklift->is_draw_pallet();
}

void LeavePalletOperation::do_single_action_step(Forklift* forklift)
{
	forklift->add_current_pallet();
	forklift->set_draw_pallet(false);
}

void LeavePalletOperation::modify_matrix()
{
}
