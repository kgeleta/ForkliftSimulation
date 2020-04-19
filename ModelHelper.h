#ifndef MODELHELPER_H
#define MODELHELPER_H

#include "model3DS.h"
#include <direct.h>

class ModelHelper
{
public:
	struct model_w_skladzie {
		char* filename;
		model3DS* model;
		struct model_w_skladzie* wsk;
	};

	struct model_w_skladzie* sklad_modeli = NULL;

	void dodajModel(model3DS* _model, char* file_name);

	model3DS* pobierzModel(char* file_name);

	void rysujModel(char* file_name, int tex_num = -1);

	void aktywujSpecjalneRenderowanieModelu(char* file_name, int spec_id = 0);

	void ladujModele();
};
#endif