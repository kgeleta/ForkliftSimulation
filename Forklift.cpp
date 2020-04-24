#include "Forklift.h"


#include "LowerMastOperation.h"
#include "RaiseMastOperation.h"

Forklift::Forklift(ModelHelper* _modelHelper)
{
	this->modelHelper = _modelHelper;
	
	// TODO: this should be passed in argument
	this->operations.push(new RaiseMastOperation(Operation::ShelfLevel::Level2));
	this->operations.push(new LowerMastOperation());
	this->operations.push(new RaiseMastOperation(Operation::ShelfLevel::Level1));
	this->operations.push(new LowerMastOperation());
	this->operations.push(new RaiseMastOperation(Operation::ShelfLevel::Level0));
	this->operations.push(new LowerMastOperation());
	this->operations.push(new RaiseMastOperation(Operation::ShelfLevel::Level2));

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

	glTranslatef(-3.8, 10.1, 1.1);
	modelHelper->draw_model("pallet");

	glPopMatrix();
}
