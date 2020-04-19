#include "ModelHelper.h"

void ModelHelper::add_model(model3DS* _model, char* file_name)
{
	struct model_in_memory* tmp;
	tmp = static_cast<struct model_in_memory*>(malloc(sizeof(struct model_in_memory)));
	tmp->filename = static_cast<char*>(malloc(strlen(file_name) + 1));
	strcpy(tmp->filename, file_name);
	tmp->model = _model;
	tmp->wsk = models;
	models = tmp;
}

model3DS* ModelHelper::get_model(char* file_name) const
{
	struct model_in_memory* sklad_tmp = models;
	while (sklad_tmp) {
		if (!_stricmp(sklad_tmp->filename, file_name)) return sklad_tmp->model;
		char file_name_full[_MAX_PATH];
		strcpy(file_name_full, file_name);
		strcat(file_name_full, ".3ds");
		if (!_stricmp(sklad_tmp->filename, file_name_full)) return sklad_tmp->model;

		sklad_tmp = sklad_tmp->wsk;
	}
	return NULL;
}

void ModelHelper::draw_model(char* file_name, int tex_num) const
{
	model3DS* model_tmp;
	if (model_tmp = get_model(file_name))
		if (tex_num == -1)
			model_tmp->draw();
		else
			model_tmp->draw(tex_num, false);

}

void ModelHelper::activate_special_model_rendering(char* file_name, int spec_id) const
{
	model3DS* model_tmp;
	if (model_tmp = get_model(file_name))
		model_tmp->setSpecialTransform(spec_id);
}

void ModelHelper::load_models()
{
	WIN32_FIND_DATA* fd;
	HANDLE fh;
	model3DS* model_tmp;
	char directory[_MAX_PATH];
	if (_getcwd(directory, _MAX_PATH) == NULL) return;
	strcat(directory, "\\data\\*.3ds");

	fd = (WIN32_FIND_DATA*)malloc(sizeof(WIN32_FIND_DATA));
	fh = FindFirstFile((LPCSTR)directory, fd);
	if (fh != INVALID_HANDLE_VALUE)
		do {
			if (fd->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {	// katalogi ignorujemy
				if (FindNextFile(fh, fd)) continue; else break;
			}
			// ladowanie obiektu i dodanie do kontenera
			char filename[_MAX_PATH];
			strcpy(filename, "data\\");
			strcat(filename, fd->cFileName);
			model_tmp = new model3DS(filename, 1, false);
			add_model(model_tmp, fd->cFileName);
			printf("[3DS] Model '%s' stored\n", fd->cFileName);
		} while (FindNextFile(fh, fd));
}