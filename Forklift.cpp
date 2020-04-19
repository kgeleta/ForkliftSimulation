#include "Forklift.h"

Forklift::Forklift(ModelHelper* _modelHelper)
{
	this->modelHelper = _modelHelper;
}

void Forklift::InvokeAction() const
{
	glPushMatrix();
	glTranslatef(0, 0.3, 0);

	glRotatef(-90, 0, 1, 0);

	modelHelper->draw_model("forklift2");

	glTranslatef(0, this->mastPosition, 0);
	modelHelper->draw_model("topPart");

	glTranslatef(0, this->forksPosition, 0);
	modelHelper->draw_model("fork");

	glTranslatef(-3.8, 10.1, 1.1);
	modelHelper->draw_model("pallet");

	glPopMatrix();
}
