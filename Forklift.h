#ifndef FORKLIFT_H
#define FORKLIFT_H

#include "ModelHelper.h"
class ModelHelper;

class Forklift
{
private:
	ModelHelper* modelHelper;
	float mastPosition = -4.5f;
	float forksPosition = -4.5f;
	float positionX = 0.0f;
	float positionY = 0.0f;
	float positionZ = 0.0f;

public:
	Forklift(ModelHelper* _modelHelper);
	void InvokeAction();
};

#endif