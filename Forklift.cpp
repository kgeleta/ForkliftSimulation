#include "Forklift.h"
#include "LeavePalletOperation.h"
#include "LowerMastOperation.h"
#include "PickUpPalletOperation.h"
#include "RaiseMastOperation.h"

Forklift::Forklift(ModelHelper* _modelHelper)
{
	this->modelHelper = _modelHelper;
	
	// TODO: this should be passed in argument
	this->operations.push(new RaiseMastOperation(Operation::ShelfLevel::Level2));
	this->operations.push(new LeavePalletOperation());
	this->operations.push(new LowerMastOperation());
	this->operations.push(new PickUpPalletOperation());
	this->operations.push(new RaiseMastOperation(Operation::ShelfLevel::Level0));
	this->operations.push(new LeavePalletOperation());
	this->operations.push(new LowerMastOperation());
	this->operations.push(new PickUpPalletOperation());
	this->operations.push(new RaiseMastOperation(Operation::ShelfLevel::Level1));
	this->operations.push(new LeavePalletOperation());
	this->operations.push(new LowerMastOperation());
	this->operations.push(new PickUpPalletOperation());

	this->current_operation = this->operations.front();
	this->operations.pop();
}

void Forklift::InvokeAction()
{
	this->time++;

	if(this->current_operation->is_finished(this) && !this->operations.empty())
	{
		this->current_operation = this->operations.front();
		this->operations.pop();
	}
	
	if(this->time % 5 == 0 && !this->current_operation->is_finished(this))
	{
		this->current_operation->do_single_action_step(this);
	}
	
	glPushMatrix();
	glTranslatef(this->positionX, this->positionY, this->positionZ);

	glRotatef(-90, 0, 1, 0);

	modelHelper->draw_model("forklift2");

	glTranslatef(0, this->mastPosition, 0);
	modelHelper->draw_model("topPart");

	glTranslatef(0, this->forksPosition, 0);
	modelHelper->draw_model("fork");

	if (this->draw_pallet)
	{
		glTranslatef(-3.8, 10.1, 1.1);
		modelHelper->draw_model("pallet");
	}

	glPopMatrix();
}

void Forklift::add_current_pallet()
{
	// TODO: calculate the values we add to x and z position based on current rotation
	float x = this->position_x() - 1.1f;
	float y = this->position_y() + this->mast_position() + this->forks_position() + 10.1f;
	float z = this->position_z() - 3.8f;
	
	this->palletsPositions.push_back(Point3D(x, y, z));
}

void Forklift::draw_all_pallets()
{
	for (Point3D pallet_position : palletsPositions)
	{
		glPushMatrix();
			glTranslatef(pallet_position.get_x(), pallet_position.get_y(), pallet_position.get_z());
			glRotatef(-90, 0, 1, 0);
			modelHelper->draw_model("pallet");
		glPopMatrix();
	}
}
