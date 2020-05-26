#include "JobEntity.h"

#include "LeavePalletOperation.h"
#include "LowerMastOperation.h"
#include "MoveOperation.h"
#include "PickUpPalletOperation.h"
#include "RaiseMastOperation.h"
#include "TurnOperation.h"
#include "Configuration.h"
#include "Idle.h"

std::vector<Operation*> JobEntity::GenerateOperations()
{
	// TODO: implement this method!
	// this should generate list of operation that need
	// to be done in order to move pallet to the correct shelf
	// below is only the hardcoded example
	
	// Definitions
	std::vector<Operation*> operations;
	// Path to shelf
	float pathLen = ((shelf_index - 1) * SPACE_BETWEEN_SHELVES) - 10;
	// Adjust to pallet position
	float adjustToPalletPosition = (pallet_position - 1) * 5;

	std::cout << shelf_index << " " << shelf_level << " " << pallet_position << " " << pathLen << " " << adjustToPalletPosition << "\n";

	// Set start position
	if (shelf_index == -1 && shelf_level == -1 && pallet_position == -1) {
		operations.push_back(new MoveOperation(Operation::MoveDirection::Forward, 20));
		operations.push_back(new TurnOperation(Operation::TurnDirection::Right, Operation::MoveDirection::Backward, 90));
		operations.push_back(new MoveOperation(Operation::MoveDirection::Forward, 20));
	}
	else
	{
		// New pallet
		operations.push_back(new MoveOperation(Operation::MoveDirection::Forward, 5));
		operations.push_back(new Idle(20));
		operations.push_back(new PickUpPalletOperation());
		operations.push_back(new Idle(50));
		operations.push_back(new MoveOperation(Operation::MoveDirection::Backward, 5));
		operations.push_back(new TurnOperation(Operation::TurnDirection::Right, Operation::MoveDirection::Backward, 90));
		
		// If shelf index bigger than 1, move path
		if (shelf_index != 1) {
			operations.push_back(new TurnOperation(Operation::TurnDirection::Left, Operation::MoveDirection::Forward, 90));

			// Path to shelf
			operations.push_back(new MoveOperation(Operation::MoveDirection::Forward, pathLen));

			// init leve pallet procedure
			operations.push_back(new TurnOperation(Operation::TurnDirection::Right, Operation::MoveDirection::Forward, 90));
		}
		else {
			operations.push_back(new MoveOperation(Operation::MoveDirection::Forward, 15));
		}

		// Adjust to pallet position
		operations.push_back(new MoveOperation(Operation::MoveDirection::Forward, adjustToPalletPosition));

		operations.push_back(new TurnOperation(Operation::TurnDirection::Left, Operation::MoveDirection::Forward, 90));

		// Put pallet on shelf
		switch (shelf_level) {
		case 0:
			operations.push_back(new RaiseMastOperation(Operation::ShelfLevel::Level0));
			break;
		case 1:
			operations.push_back(new RaiseMastOperation(Operation::ShelfLevel::Level1));
			break;
		case 2:
			operations.push_back(new RaiseMastOperation(Operation::ShelfLevel::Level2));
			break;
		}
		operations.push_back(new MoveOperation(Operation::MoveDirection::Forward, 5));
		operations.push_back(new LeavePalletOperation());
		operations.push_back(new Idle(50));
		operations.push_back(new MoveOperation(Operation::MoveDirection::Backward, 5));
		operations.push_back(new LowerMastOperation());

		//Go back to start position
		operations.push_back(new TurnOperation(Operation::TurnDirection::Right, Operation::MoveDirection::Backward, 90));
		// Adjust to pallet position
		operations.push_back(new MoveOperation(Operation::MoveDirection::Forward, adjustToPalletPosition));
		operations.push_back(new MoveOperation(Operation::MoveDirection::Forward, 10));
		operations.push_back(new TurnOperation(Operation::TurnDirection::Left, Operation::MoveDirection::Forward, 90));

		// If shelf index bigger than 1, move path
		if (shelf_index != 1) {
			operations.push_back(new MoveOperation(Operation::MoveDirection::Forward, pathLen+10));
		}
	}

	

	//operations.push_back(new MoveOperation(Operation::MoveDirection::Forward, 0));
	//operations.push_back(new TurnOperation(Operation::TurnDirection::Left, Operation::MoveDirection::Forward, 90));
	//operations.push_back(new MoveOperation(Operation::MoveDirection::Backward, 15));
	//operations.push_back(new TurnOperation(Operation::TurnDirection::Right, Operation::MoveDirection::Forward, 90));
	//operations.push_back(new MoveOperation(Operation::MoveDirection::Backward, 20));
	//operations.push_back(new TurnOperation(Operation::TurnDirection::Left, Operation::MoveDirection::Backward, 90));
	//operations.push_back(new MoveOperation(Operation::MoveDirection::Forward, 10));

	//operations.push_back(new RaiseMastOperation(Operation::ShelfLevel::Level2));
	//operations.push_back(new MoveOperation(Operation::MoveDirection::Forward, 5));
	//operations.push_back(new LeavePalletOperation());
	//operations.push_back(new MoveOperation(Operation::MoveDirection::Backward, 5));
	//operations.push_back(new LowerMastOperation());

	//operations.push_back(new PickUpPalletOperation());
	//operations.push_back(new RaiseMastOperation(Operation::ShelfLevel::Level0));
	//operations.push_back(new MoveOperation(Operation::MoveDirection::Forward, 5));
	//operations.push_back(new LeavePalletOperation());
	//operations.push_back(new MoveOperation(Operation::MoveDirection::Backward, 5));
	//operations.push_back(new LowerMastOperation());

	//operations.push_back(new PickUpPalletOperation());
	//operations.push_back(new RaiseMastOperation(Operation::ShelfLevel::Level1));
	//operations.push_back(new MoveOperation(Operation::MoveDirection::Forward, 5));
	//operations.push_back(new LeavePalletOperation());
	//operations.push_back(new MoveOperation(Operation::MoveDirection::Backward, 5));
	//operations.push_back(new LowerMastOperation());

	return operations;
}
