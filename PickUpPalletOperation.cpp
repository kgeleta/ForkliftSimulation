#include "PickUpPalletOperation.h"

bool PickUpPalletOperation::is_finished(Forklift* forklift)
{
	return forklift->is_draw_pallet();
}

void PickUpPalletOperation::do_single_action_step(Forklift* forklift)
{
	forklift->set_draw_pallet_on_ground(false);
	forklift->set_draw_pallet_on_fork(true);
}

void PickUpPalletOperation::modify_matrix()
{
}
