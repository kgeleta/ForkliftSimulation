#include "PickUpPalletOperation.h"

bool PickUpPalletOperation::is_finished(Forklift* forklift)
{
	return forklift->is_draw_pallet();
}

void PickUpPalletOperation::do_single_action_step(Forklift* forklift)
{
	// TODO: remove pallet from the ground
	forklift->set_current_shelf_index(this->shelfIndex);
	forklift->set_draw_pallet(true);
}

void PickUpPalletOperation::modify_matrix()
{
}
