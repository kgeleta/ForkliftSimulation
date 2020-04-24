#pragma once
#include "Forklift.h"

class Forklift;

class Operation
{
public:
	enum class ShelfLevel { Level0, Level1, Level2 };
	virtual ~Operation() = default;

	virtual bool is_finished(Forklift* forklift) = 0;
	virtual void do_single_action_step(Forklift* forklift) = 0;
};
