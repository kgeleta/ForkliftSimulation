#include "Forklift.h"
#include <utility>

#include "DrawPalletOperation.h"

Forklift::Forklift(ModelHelper* _modelHelper, std::queue<Operation*> _operations)
{
	this->modelHelper = _modelHelper;
	this->operations = std::queue<Operation*>(std::move(_operations));

	this->current_operation = this->operations.front();
	this->operations.pop();
}

void Forklift::InvokeAction()
{
	this->time++;

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

		if (this->draw_pallet)
		{
			glTranslatef(-3.8, 10.1, 1.1);
			modelHelper->draw_model("pallet");


			// cube
			float color_r = 0.0f;
			float color_g = 0.0f;
			float color_b = 1.0f;

			glPushMatrix();
				glTranslatef(-0.2f, 1.2f, -1.0f);

				glEnable(GL_COLOR_MATERIAL);
				glBegin(GL_QUADS);

				glEnable(GL_DEPTH_TEST);
				glColor3f(color_r, color_g, color_b);
				glVertex3f(1.0f, 1.0f, -1.0f);
				glVertex3f(-1.0f, 1.0f, -1.0f);
				glVertex3f(-1.0f, 1.0f, 1.0f);
				glVertex3f(1.0f, 1.0f, 1.0f);

				glColor3f(color_r, color_g, color_b);
				glVertex3f(1.0f, -1.0f, 1.0f);
				glVertex3f(-1.0f, -1.0f, 1.0f);
				glVertex3f(-1.0f, -1.0f, -1.0f);
				glVertex3f(1.0f, -1.0f, -1.0f);

				glColor3f(color_r, color_g, color_b);
				glVertex3f(1.0f, 1.0f, 1.0f);
				glVertex3f(-1.0f, 1.0f, 1.0f);
				glVertex3f(-1.0f, -1.0f, 1.0f);
				glVertex3f(1.0f, -1.0f, 1.0f);

				glColor3f(color_r, color_g, color_b);
				glVertex3f(1.0f, -1.0f, -1.0f);
				glVertex3f(-1.0f, -1.0f, -1.0f);
				glVertex3f(-1.0f, 1.0f, -1.0f);
				glVertex3f(1.0f, 1.0f, -1.0f);

				glColor3f(color_r, color_g, color_b);
				glVertex3f(-1.0f, 1.0f, 1.0f);
				glVertex3f(-1.0f, 1.0f, -1.0f);
				glVertex3f(-1.0f, -1.0f, -1.0f);
				glVertex3f(-1.0f, -1.0f, 1.0f);

				glColor3f(color_r, color_g, color_b);
				glVertex3f(1.0f, 1.0f, -1.0f);
				glVertex3f(1.0f, 1.0f, 1.0f);
				glVertex3f(1.0f, -1.0f, 1.0f);
				glVertex3f(1.0f, -1.0f, -1.0f);
				glEnd();  // End of drawing color-cube
				glDisable(GL_COLOR_MATERIAL);
			glPopMatrix();
		}
	glPopMatrix();
}

void Forklift::add_current_pallet()
{
	this->memory.push_back(new DrawPalletOperation(this->modelHelper, this->mast_position() + this->forks_position()));
}