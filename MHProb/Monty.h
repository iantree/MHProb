#pragma once
//*******************************************************************************************************************
//*																													*
//*   File:       Monty.h																							*
//*   Suite:      Experimental Algorithms																			*
//*   Version:    1.0.0	(Build: 01)																					*
//*   Author:     Ian Tree/HMNL																						*
//*																													*
//*   Copyright 2017 - 2025 Ian J. Tree.														*
//*******************************************************************************************************************
//*	Monty																											*
//*																													*
//*	The Monty class provides the simulation of Monty Hall, data storage and actions.								*
//*																													*
//*																													*
//*	NOTES:																											*
//*																													*
//*	1.																												*
//*																													*
//*******************************************************************************************************************
//*																													*
//*   History:																										*
//*																													*
//*	1.0.0 -		01/04/2025	-	Initial Release																		*
//*																													*
//*******************************************************************************************************************/

//  xymorg headers
#include	"../xymorg/xymorg.h"

//  Monty class definition
class Monty {
public:

	//*******************************************************************************************************************
	//*                                                                                                                 *
	//*   Constructors			                                                                                        *
	//*                                                                                                                 *
	//*******************************************************************************************************************

	//  Default Constructor 
	//
	//  Constructs an empty Monty object.
	//
	//  PARAMETERS:
	// 
	//		PRNG&		-		Reference to the entropy source to use
	//
	//  RETURNS:
	//
	//  NOTES:
	//

	Monty(PRNG& ESRef) 
		: ESrc(ESRef)
		, CarAt(-1)
		, CSelected(-1)
		, MSelected(-1)
	{
		//  Initialise the doors
		Door [3] = Door[2] = Door[1] = Door[0] = -1;

		//  Return to caller
		return;
	}

	//*******************************************************************************************************************
	//*                                                                                                                 *
	//*   Destructor			                                                                                        *
	//*                                                                                                                 *
	//*******************************************************************************************************************

	//  Destructor
	//
	//  Destroys the Monty object.
	//
	//  PARAMETERS:
	//
	//  RETURNS:
	//
	//  NOTES:
	//  

	~Monty() {

		//  Return to caller
		return;
	}

	//*******************************************************************************************************************
	//*                                                                                                                 *
	//*   Public Members                                                                                                *
	//*                                                                                                                 *
	//*******************************************************************************************************************

	//*******************************************************************************************************************
	//*                                                                                                                 *
	//*   Public Functions                                                                                              *
	//*                                                                                                                 *
	//*******************************************************************************************************************

	//  placeTheCar
	//
	//  This function will simulate Monty selecting a door at random and placing the car behind that door.
	//
	//	PARAMETERS:
	//
	//	RETURNS:
	//
	//		int			-		Door number that the car was placed behind
	// 
	//	NOTES:
	//

	int		placeTheCar() {
		std::uniform_int_distribution<>		Target(1, 3);					//  Random Door Selector

		//  Place goats behind each door
		Door[3] = Door[2] = Door[1] = 0;

		//  Place the car behind a random door
		CarAt = Target(ESrc);

		//  Update the door status
		Door[CarAt] = 1;

		//  Clear the selections
		CSelected = -1;
		MSelected = -1;

		//  Return the door number behind which the car was placed
		return CarAt;
	}

	//  selectedDoor
	//
	//  This function will tell Monty the door number that the contestant selected
	//
	//	PARAMETERS:
	//
	//		int			-		Door number that the contestant selected
	//
	//	RETURNS:
	// 
	//	NOTES:
	//

	void	selectedDoor(int NewDoor) {

		//  Record the door that was selected
		CSelected = NewDoor;

		//  Return to caller
		return;
	}

	//  openADoor
	//
	//  This function will simulate Monty opening a door (goat ONLY).
	//
	//	PARAMETERS:
	//
	//	RETURNS:
	//
	//		int			-		Door number that Monty opened
	// 
	//	NOTES:
	// 
	//	This operation is crucial in (mis)understanding the logic underpinning the Monty Hall Problem.
	//  Monty must select and open a door that meets the following two constraints.
	//		(1) The selected door MUST NOT have the car behind it.
	//		(2) The selected door MUST NOT be the one selected by the contestant.
	//	All of the information needed to make the selection is available to Monty.
	//

	int		openADoor() {
		std::uniform_int_distribution<>		Target(0, 1);					//  Random Door Selector
		int		AvailableDoors[2] = { 0, 0 };								//  Doors available for selection

		//	Condition 1 - the contestant has selected the door with the car behind it.
		//  This gives Monty the two other doors to choose from (which he does randomly)
		if (CSelected == CarAt) {

			//  Setup the doors that are available for selection
			switch (CarAt) {
			case 1:
				AvailableDoors[0] = 2;
				AvailableDoors[1] = 3;
				break;
			case 2:
				AvailableDoors[0] = 1;
				AvailableDoors[1] = 3;
				break;
			case 3:
				AvailableDoors[0] = 1;
				AvailableDoors[1] = 2;
				break;
			}

			//  Pick one of the available doors at random
			
			int Selected = Target(ESrc);

			//  Mark the selected door as open
			Door[AvailableDoors[Selected]] = 2;

			//  Save the selected door
			MSelected = AvailableDoors[Selected];

			//  Return the selected door
			return AvailableDoors[Selected];
		}

		//  Condition 2 - The contestant has NOT selected the door with the car behind.
		//  This leaves Monty with no option as there is only one door that meets the two constraints.

		switch (CarAt) {
		case 1:
			switch (CSelected) {
			case 2:
				Door[3] = 2;
				MSelected = 3;
				break;
			case 3:
				Door[2] = 2;
				MSelected = 2;
				break;
			}
			break;
		case 2:
			switch (CSelected) {
			case 1:
				Door[3] = 2;
				MSelected = 3;
				break;
			case 3:
				Door[1] = 2;
				MSelected = 1;
				break;
			}
			break;
		case 3:
			switch (CSelected) {
			case 1:
				Door[2] = 2;
				MSelected = 2;
				break;
			case 2:
				Door[1] = 2;
				MSelected = 1;
				break;
			}
			break;
		}

		//  Return the selected door
		return MSelected;
	}

	//  openADoorAtRandom
	//
	//  This function will simulate Monty opening a door allocated to contestant #2 at random
	//
	//	PARAMETERS:
	//
	//	RETURNS:
	//
	//		int			-		Door number that Monty opened
	// 
	//	NOTES:
	// 

	int		openADoorAtRandom() {
		std::uniform_int_distribution<>		Target(0, 1);					//  Random Door Selector
		int		AvailableDoors[2] = { 0, 0 };								//  Doors available for selection

		//  Setup the doors that are available for selection
		switch (CSelected) {
		case 1:
			AvailableDoors[0] = 2;
			AvailableDoors[1] = 3;
			break;
		case 2:
			AvailableDoors[0] = 1;
			AvailableDoors[1] = 3;
			break;
		case 3:
			AvailableDoors[0] = 1;
			AvailableDoors[1] = 2;
			break;
		}

		//  Pick one of the available doors at random
		int Selected = Target(ESrc);

		//  Mark the selected door as open
		Door[AvailableDoors[Selected]] = 2;

		//  Save the selected door
		MSelected = AvailableDoors[Selected];

		//  Return the selected door
		return AvailableDoors[Selected];
	}

	//  didYouWin
	//
	//  This function will see if monty won the car
	//
	//	PARAMETERS:
	//
	//	RETURNS:
	// 
	//		bool		-		True if Monty won, otherwise false
	// 
	//	NOTES:
	//

	bool	didYouWin() const {
		if (MSelected == CarAt) return true;
		return false;
	}

	//  whichDoor
	//
	//  This function will return the door that Monty selected to open
	//
	//	PARAMETERS:
	//
	//	RETURNS:
	// 
	//		int		-		Door number that Monty selected to open
	// 
	//	NOTES:
	//

	int		whichDoor() const { return MSelected; }

	//  haveIWon
	//
	//  This function will see if the passed door number has a car behind it (true) or a goat (false)
	//
	//	PARAMETERS:
	//
	//		int			-		Door number to be tested
	//
	//	RETURNS:
	// 
	//		bool		-		True if it has a car behind it, false if it has a goat
	// 
	//	NOTES:
	//

	bool	haveIWon(int DoorNo) const {
		if (Door[DoorNo] == 1) return true;
		return false;
	}

private:


	//*******************************************************************************************************************
	//*                                                                                                                 *
	//*   Private Members			                                                                                    *
	//*                                                                                                                 *
	//*******************************************************************************************************************

	PRNG&		ESrc;															//  Entropy Source

	//
	//   Door states - 0 goat behind door, 1 car behind door, 2 door is open
	//   Element 0 is unused - therefore we can use the door number directly as an index into the array
	// 
	int			Door[4];

	int			CarAt;															//  Door with the car behind
	int			CSelected;														//  Door selected by contestant
	int			MSelected;														//  Door selected by Monty

	//*******************************************************************************************************************
	//*                                                                                                                 *
	//*   Private Functions                                                                                             *
	//*                                                                                                                 *
	//*******************************************************************************************************************


};
