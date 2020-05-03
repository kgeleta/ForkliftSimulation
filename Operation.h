#pragma once
#include "Forklift.h"

class Forklift;

class Operation
{
protected:
	bool save_operation_in_memory = false;
public:
	enum class ShelfLevel { Level0, Level1, Level2 };
	enum class MoveDirection { Forward, Backward };
	enum class TurnDirection {Right, Left };
	virtual ~Operation() = default;

	virtual bool is_finished(Forklift* forklift) = 0;
	// single action step should not modify the matrix
	virtual void do_single_action_step(Forklift* forklift) = 0;
	// action can modify the matrix
	virtual void modify_matrix() = 0;

	bool is_save_operation_in_memory() const
	{
		return this->save_operation_in_memory;
	}
};
