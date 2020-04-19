#include "Forklift.h"

Forklift::Forklift(ModelHelper* _modelHelper)
{
	this->modelHelper = _modelHelper;
}

void Forklift::InvokeAction()
{
	glPushMatrix();
	glTranslatef(0, 0.3, 0);

	glRotatef(-90, 0, 1, 0);

	modelHelper->rysujModel("forklift2");

	glTranslatef(0, this->mastPosition, 0);
	modelHelper->rysujModel("topPart");

	glTranslatef(0, this->forksPosition, 0);
	modelHelper->rysujModel("fork");

	glTranslatef(-3.8, 10.1, 1.1);
	modelHelper->rysujModel("pallet");

	glPopMatrix();
}