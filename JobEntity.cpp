#include "JobEntity.h"

#include "LeavePalletOperation.h"
#include "LowerMastOperation.h"
#include "MoveOperation.h"
#include "PickUpPalletOperation.h"
#include "RaiseMastOperation.h"
#include "TurnOperation.h"

std::vector<Operation*> JobEntity::GenerateOperations()
{
	// TODO: implement this method!
	// this should generate list of operation that need
	// to be done in order to move pallet to the correct shelf
	// below is only the hardcoded example

	std::vector<Operation*> operations;
	operations.push_back(new MoveOperation(Operation::MoveDirection::Forward, 10));
	operations.push_back(new TurnOperation(Operation::TurnDirection::Left, Operation::MoveDirection::Forward, 90));
	operations.push_back(new MoveOperation(Operation::MoveDirection::Backward, 15));
	operations.push_back(new TurnOperation(Operation::TurnDirection::Right, Operation::MoveDirection::Forward, 90));
	operations.push_back(new MoveOperation(Operation::MoveDirection::Backward, 20));
	operations.push_back(new TurnOperation(Operation::TurnDirection::Left, Operation::MoveDirection::Backward, 90));
	operations.push_back(new MoveOperation(Operation::MoveDirection::Forward, 10));

	operations.push_back(new RaiseMastOperation(Operation::ShelfLevel::Level2));
	operations.push_back(new MoveOperation(Operation::MoveDirection::Forward, 5));
	operations.push_back(new LeavePalletOperation());
	operations.push_back(new MoveOperation(Operation::MoveDirection::Backward, 5));
	operations.push_back(new LowerMastOperation());

	operations.push_back(new PickUpPalletOperation());
	operations.push_back(new RaiseMastOperation(Operation::ShelfLevel::Level0));
	operations.push_back(new MoveOperation(Operation::MoveDirection::Forward, 5));
	operations.push_back(new LeavePalletOperation());
	operations.push_back(new MoveOperation(Operation::MoveDirection::Backward, 5));
	operations.push_back(new LowerMastOperation());

	operations.push_back(new PickUpPalletOperation());
	operations.push_back(new RaiseMastOperation(Operation::ShelfLevel::Level1));
	operations.push_back(new MoveOperation(Operation::MoveDirection::Forward, 5));
	operations.push_back(new LeavePalletOperation());
	operations.push_back(new MoveOperation(Operation::MoveDirection::Backward, 5));
	operations.push_back(new LowerMastOperation());

	return operations;
}
