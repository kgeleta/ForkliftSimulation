#pragma once
#include "Operation.h"

class Idle :
	public Operation
{
private:
	float waitTime;
	float timePassed;
public:
	explicit Idle(float waitTime)
	{
		this->waitTime = waitTime > 0 ? waitTime : 0;
		this->timePassed = 0;
	}

	bool is_finished(Forklift* forklift) override;
	void do_single_action_step(Forklift* forklift) override;
	void modify_matrix() override;
};