#pragma once
#include "Operation.h"
#include "ColorHelper.h"

class DrawPalletOperation : public Operation
{
private:
	ModelHelper* modelHelper;
	float position_y;
	int shelfIndex;
public:
	explicit DrawPalletOperation(ModelHelper* model_helper, float position_y, int shelfIndex)
		: modelHelper(model_helper), position_y(position_y), shelfIndex(shelfIndex) {}

	bool is_finished(Forklift* forklift) override;
	void do_single_action_step(Forklift* forklift) override;
	void modify_matrix() override;
};