#pragma once
#include "model3DS.h"
#include <direct.h>

class ModelHelper
{
public:
	struct model_in_memory {
		char* filename;
		model3DS* model;
		struct model_in_memory* wsk;
	};

	struct model_in_memory* models = NULL;

	void add_model(model3DS* _model, char* file_name);

	model3DS* get_model(char* file_name) const;

	void draw_model(char* file_name, int tex_num = -1) const;

	void activate_special_model_rendering(char* file_name, int spec_id = 0) const;

	void load_models();
};