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
	glTranslatef(-0.2f, 1.0f, -1.0f);
	modelHelper->draw_cube(Color(0.0f, 0.0f, 1.0f));
	glPopMatrix();
}
