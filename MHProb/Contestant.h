#pragma once
//*******************************************************************************************************************
//*																													*
//*   File:       Contestant.h																						*
//*   Suite:      Experimental Algorithms																			*
//*   Version:    1.0.0	(Build: 01)																					*
//*   Author:     Ian Tree/HMNL																						*
//*																													*
//*   Copyright 2017 - 2025 Ian J. Tree.														*
//*******************************************************************************************************************
//*	Contestant																										*
//*																													*
//*	The Contestant class provides the simulation of a Contestant, data storage and actions.							*
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

//  Contestant class definition

class Contestant {
public:

	//*******************************************************************************************************************
	//*                                                                                                                 *
	//*   Constructors			                                                                                        *
	//*                                                                                                                 *
	//*******************************************************************************************************************

	//  Default Constructor 
	//
	//  Constructs an empty Contestant object.
	//
	//  PARAMETERS:
	// 
	//		PRNG&		-		Refernce to the entropy source to use
	//
	//  RETURNS:
	//
	//  NOTES:
	//

	Contestant(PRNG& ESRef) 
		: ESrc(ESRef)
		, DoorSelected(-1)
		, DoorOpened(-1)
	{
		MyDoors[1] = MyDoors[0] = -1;

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
	//  Destroys the Contestant object.
	//
	//  PARAMETERS:
	//
	//  RETURNS:
	//
	//  NOTES:
	//  

	~Contestant() {

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

	//  pickADoor
	//
	//  This function will simulate the contestant selecting a door at random.
	//
	//	PARAMETERS:
	//
	//	RETURNS:
	//
	//		int			-		Door number that the contestant selected
	// 
	//	NOTES:
	//

	int		pickADoor() {
		std::uniform_int_distribution<>		Target(1, 3);					//  Random Door Selector

		//  Select a door at random
		DoorSelected = Target(ESrc);

		//  Report the door selected
		return DoorSelected;
	}

	//  openedDoor
	//
	//  This function will notify the contestant of which door Monty has opened
	//
	//	PARAMETERS:
	//
	//		int			-		Door number that Monty opened
	//
	//	RETURNS:
	// 
	//	NOTES:
	//

	void	openedDoor(int NewOpened) {

		//  Record the door that was opened by Monty
		DoorOpened = NewOpened;

		//  Return to caller
		return;
	}

	//  selectedDoor
	//
	//  This function will tell the contestant the door number that the opponent selected
	//
	//	PARAMETERS:
	//
	//		int			-		Door number that the opponent selected
	//
	//	RETURNS:
	// 
	//	NOTES:
	//

	void	selectedDoor(int NewDoor) {

		//  Record the doors that are allocated - all doors except that selected
		switch (NewDoor) {
		case 1:
			MyDoors[0] = 2;
			MyDoors[1] = 3;
			break;
		case 2:
			MyDoors[0] = 1;
			MyDoors[1] = 3;
			break;
		case 3:
			MyDoors[0] = 1;
			MyDoors[1] = 2;
			break;
		}

		//  Return to caller
		return;
	}

	//  Stick
	//
	//  This function will return the door number that the contestant originally selected i.e. sticking to the original guess.
	//
	//	PARAMETERS:
	//
	//	RETURNS:
	//
	//		int			-		Door number originally selected
	// 
	//	NOTES:
	//

	int		Stick() const { return DoorSelected; }

	//  Switch
	//
	//  This function will return the door number that the contestant did not originall select i.e. switching.
	//
	//	PARAMETERS:
	//
	//	RETURNS:
	//
	//		int			-		Door number NOT originally selected
	// 
	//	NOTES:
	//

	int		Switch() const {
		switch (DoorSelected) {
		case 1:
			if (DoorOpened == 2) return 3;
			else return 2;
		case 2:
			if (DoorOpened == 1) return 3;
			else return 1;
		case 3:
			if (DoorOpened == 1) return 2;
			else return 1;
		}

		//  Should Never Occur
		return -1;
	}

	//  firstDoor
	//
	//  This function will return the first door number allocated to the contestant.
	//
	//	PARAMETERS:
	//
	//	RETURNS:
	//
	//		int			-		First door number allocated
	// 
	//	NOTES:
	//

	int		firstDoor() const { return MyDoors[0]; }

	//  secondDoor
	//
	//  This function will return the second door number allocated to the contestant.
	//
	//	PARAMETERS:
	//
	//	RETURNS:
	//
	//		int			-		Second door number allocated
	// 
	//	NOTES:
	//

	int		secondDoor() const { return MyDoors[1]; }

private:

	//*******************************************************************************************************************
	//*                                                                                                                 *
	//*   Private Members			                                                                                    *
	//*                                                                                                                 *
	//*******************************************************************************************************************

	PRNG&	ESrc;																//  Entropy Source
	int		DoorSelected;														//  Guess door selected
	int		DoorOpened;															//  Door opened by Monty
	int		MyDoors[2];															//  Allocated doors

	//*******************************************************************************************************************
	//*                                                                                                                 *
	//*   Private Functions                                                                                             *
	//*                                                                                                                 *
	//*******************************************************************************************************************


};
