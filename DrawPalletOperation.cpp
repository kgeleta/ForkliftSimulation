#include "DrawPalletOperation.h"

bool DrawPalletOperation::is_finished(Forklift* forklift)
{
	return true;
}

void DrawPalletOperation::do_single_action_step(Forklift* forklift)
{
}

void DrawPalletOperation::modify_matrix()
{
	glPushMatrix();
	glTranslatef(-3.8, this->position_y + 10.1, 1.1);
	this->modelHelper->draw_model("pallet");
	glPopMatrix();
}
