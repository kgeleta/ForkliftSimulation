#pragma once
#include "Operation.h"

class DrawPalletOperation : public Operation
{
private:
	ModelHelper* modelHelper;
	float position_y;
public:
	explicit DrawPalletOperation(ModelHelper* model_helper, float position_y)
		: modelHelper(model_helper), position_y(position_y) {}

	bool is_finished(Forklift* forklift) override;
	void do_single_action_step(Forklift* forklift) override;
	void modify_matrix() override;
};