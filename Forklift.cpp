#include "Forklift.h"
#include <utility>

#include "DrawPalletOperation.h"

Forklift::Forklift(ModelHelper* _modelHelper, std::queue<Operation*> _operations, std::vector<int> _shelfIndexes)
{
	this->modelHelper = _modelHelper;
	this->operations = std::queue<Operation*>(std::move(_operations));
	this->shelf_indexes = _shelfIndexes;
	this->current_operation = this->operations.front();
	this->operations.pop();
}

void Forklift::InvokeAction()
{
	this->time++;

	if (this->draw_pallet_on_ground && this->currentShelfIndex < this->shelf_indexes.size())
	{
		glPushMatrix();
			glTranslatef(PALLET_ON_GROUND_X, PALLET_ON_GROUND_Y, PALLET_ON_GROUND_Z);
			glRotatef(90.0f, 0, 1, 0);
			modelHelper->draw_model("pallet");
			glTranslatef(-0.2f, 1.2f, -1.0f);
			Color c = ColorHelper::get_color_for_shelf(this->shelf_indexes.at(this->currentShelfIndex));
			modelHelper->draw_cube(c);
		glPopMatrix();
	}

	if(this->current_operation != nullptr && this->current_operation->is_finished(this))
	{
		// reset timer
		this->time = 0;
		
		if (this->current_operation->is_save_operation_in_memory())
		{
			// save current operation in memory
			this->memory.push_back(this->current_operation);
			this->current_operation = nullptr;
		}
		
		if (!this->operations.empty())
		{
			// take next operation from queue
			this->current_operation = this->operations.front();
			this->operations.pop();
		}		
	}
	
	if(this->current_operation != nullptr && this->time % 1 == 0 && !this->current_operation->is_finished(this))
	{
		this->current_operation->do_single_action_step(this);
	}
	
	glPushMatrix();
		for (Operation* operation : this->memory)
		{
			operation->modify_matrix();
		}

		if (this->current_operation != nullptr && !this->current_operation->is_finished(this))
		{
			this->current_operation->modify_matrix();
		}

		modelHelper->draw_model("forklift2");

		glTranslatef(0, this->mastPosition, 0);
		modelHelper->draw_model("topPart");

		glTranslatef(0, this->forksPosition, 0);
		modelHelper->draw_model("fork");

		if (this->draw_pallet_on_fork)
		{
			glTranslatef(-3.8, 10.1, 1.1);
			modelHelper->draw_model("pallet");

			// cube
			glPushMatrix();
				glTranslatef(-0.2f, 1.2f, -1.0f);
				Color c = ColorHelper::get_color_for_shelf(this->shelf_indexes.at(this->currentShelfIndex));
				modelHelper->draw_cube(c);
			glPopMatrix();
		}
	glPopMatrix();
}

void Forklift::add_current_pallet_to_memory()
{
	this->memory.push_back(new DrawPalletOperation(this->modelHelper, this->mast_position() + this->forks_position(), this->shelf_indexes.at(this->currentShelfIndex)));
}