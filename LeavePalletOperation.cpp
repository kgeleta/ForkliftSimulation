#include "LeavePalletOperation.h"

bool LeavePalletOperation::is_finished(Forklift* forklift)
{
	return !forklift->is_draw_pallet();
}

void LeavePalletOperation::do_single_action_step(Forklift* forklift)
{
	forklift->add_current_pallet_to_memory();
	forklift->set_draw_pallet_on_fork(false);
	forklift->next_shelf_index();
	forklift->set_draw_pallet_on_ground(true);
}

void LeavePalletOperation::modify_matrix()
{
}
