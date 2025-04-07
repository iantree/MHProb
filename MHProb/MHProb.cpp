//*******************************************************************************************************************
//*																													*
//*   File:       MHProb.cpp																						*
//*   Suite:      Experimental Algorithms																			*
//*   Version:    1.0.0	(Build: 01)																					*
//*   Author:     Ian Tree/HMNL																						*
//*																													*
//*   Copyright 2017 - 2025 Ian J. Tree.														*
//*******************************************************************************************************************
//*	MHProb																											*
//*																													*
//*	This application demonstrates the "Monty Hall Problem" - named after Monty Hall an american game show presenter	*
//* from the 1970's.																								*
//*																													*
//*	USAGE:																											*
//*																													*
//*		MHProb <Project>																							*
//*																													*
//*     where:-																										*
//*																													*
//*		<Project>			-	Is the path to the directory project files to use.									*
//*																													*
//*	NOTES:																											*
//*																													*
//*	1.																												*
//*																													*
//*******************************************************************************************************************
//*																													*
//*   History:																										*
//*																													*
//*	1.0.0 -		31/03/2025	-	Initial Release																		*
//*																													*
//*******************************************************************************************************************/

#include	"MHProb.h"

//
//  Main entry point for the MHProb application
//

int main(int argc, char* argv[])
{
	MHPCfg		Config(APP_NAME, argc, argv);									//  Application configuration
	PRNG		RGen{ std::random_device{}() };									//  Pseudo Random Number Generator

	if (!Config.isLogOpen()) {
		std::cerr << "ERROR: The application logger was unable to start, " << APP_NAME << " will not execute." << std::endl;
		return EXIT_FAILURE;
	}

	//  Show that program is starting 
	Config.Log << APP_TITLE << " (" << APP_NAME << ") Version: " << APP_VERSION << " is starting." << std::endl;

	//  Verify the capture of configuration variables
	if (!Config.isValid()) {
		Config.Log << "ERROR: The application configuration is not valid, no further processing is possible." << std::endl;
		return EXIT_FAILURE;
	}

	//
	//  Narrate the introduction to scenario #1 - IT'S SHOWTIME
	//

	Config.Log << xymorg::undecorate;
	Config.Log << std::endl;
	Config.Log << "SCENARIO #1 - IT'S SHOWTIME!" << std::endl;
	Config.Log << "----------------------------" << std::endl;
	Config.Log << std::endl;
	Config.Log << "In this scenario we strictly follow the protocols and information disclosure model of the gameshow." << std::endl;
	Config.Log << std::endl;
	Config.Log << xymorg::decorate;

	//  Run the Show - perform the requested number of trials and report the results
	runTheShow(RGen, Config);

	//  Make observations on the scenario run results
	Config.Log << xymorg::undecorate;
	Config.Log << std::endl;
	Config.Log << "OBSERVATIONS:" << std::endl;
	Config.Log << std::endl;
	Config.Log << "We see that the result clearly favours the strategy of switching doors by a factor of 2:1. Here lies the crux of" << std::endl;
	Config.Log << "of the problem, people favoured the strategy of sticking with the originally selected door by a massive 87% to" << std::endl;
	Config.Log << "13% majority. In the following scenarios we will show correctness of the switching doors strategy in a clear manner." << std::endl;
	Config.Log << std::endl;
	Config.Log << xymorg::decorate;

	//
	//  Narrate the introduction to scenario #2 - TWO CONTESTANTS
	//

	Config.Log << xymorg::undecorate;
	Config.Log << std::endl;
	Config.Log << "SCENARIO #2 - TWO CONTESTANTS." << std::endl;
	Config.Log << "------------------------------" << std::endl;
	Config.Log << std::endl;
	Config.Log << "The setup for this scenario is the same as in the gameshow, the car is randomly placed behind one of the doors and" << std::endl;
	Config.Log << "contestant #1 selects one of the doors at random. Contestant #2 is allocated the two remaining doors and the car" << std::endl;
	Config.Log << "winning position is evaluated and recorded." << std::endl;
	Config.Log << std::endl;
	Config.Log << xymorg::decorate;

	//  Run the contest - perform the requested number of trials and report the results
	runTheContest(RGen, Config);

	//  Make observations on the scenario run results
	Config.Log << xymorg::undecorate;
	Config.Log << std::endl;
	Config.Log << "OBSERVATIONS:" << std::endl;
	Config.Log << std::endl;
	Config.Log << "An unsurprising result, contestant #2 won out over contestant #1 by a resounding factor of 2:1." << std::endl;
	Config.Log << std::endl;
	Config.Log << xymorg::decorate;

	//
	//  Narrate the introduction to scenario #3 - MONTY RANDOMLY OPENS A DOOR
	//

	Config.Log << xymorg::undecorate;
	Config.Log << std::endl;
	Config.Log << "SCENARIO #3 - MONTY RANDOMLY OPENS A DOOR." << std::endl;
	Config.Log << "------------------------------------------" << std::endl;
	Config.Log << std::endl;
	Config.Log << "This scenario is an extesion of scenario #2, before the result of a trial is determined we allow Monty to select" << std::endl;
	Config.Log << "and open one of the doors allocated to contestant #2." << std::endl;
	Config.Log << std::endl;
	Config.Log << xymorg::decorate;

	//  Run the contest - perform the requested number of trials with Monty and report the results
	runWithMonty(RGen, Config);

	//  Make observations on the scenario run results
	Config.Log << xymorg::undecorate;
	Config.Log << std::endl;
	Config.Log << "OBSERVATIONS:" << std::endl;
	Config.Log << std::endl;
	Config.Log << "This is clearly NOT what we want, Monty should not be allowed to win a car (he has enough of them)." << std::endl;
	Config.Log << std::endl;
	Config.Log << xymorg::decorate;

	//
	//  Narrate the introduction to scenario #4 - GET MONTY INTO LINE
	//

	Config.Log << xymorg::undecorate;
	Config.Log << std::endl;
	Config.Log << "SCENARIO #4 - GET MONTY INTO LINE." << std::endl;
	Config.Log << "----------------------------------" << std::endl;
	Config.Log << std::endl;
	Config.Log << "This scenario is an extension of scenario #3, before the result of a trial is determined we allow Monty to select" << std::endl;
	Config.Log << "and open one of the doors allocated to contestant #2, he may ONLY select a door with a goat behind it." << std::endl;
	Config.Log << std::endl;
	Config.Log << xymorg::decorate;

	//  Run the contest - perform the requested number of trials with Monty and report the results
	runWithMontyConstrained(RGen, Config);

	//  Make observations on the scenario run results
	Config.Log << xymorg::undecorate;
	Config.Log << std::endl;
	Config.Log << "OBSERVATIONS:" << std::endl;
	Config.Log << std::endl;
	Config.Log << "We have returned to the result from scenario #2, even with Monty opening a door. This follows the same protocol" << std::endl;
	Config.Log << "as is used in the gameshow." << std::endl;
	Config.Log << std::endl;
	Config.Log << xymorg::decorate;

	//
	//  Narrate the introduction to scenario #5 - ONE SMALL STEP
	//

	Config.Log << xymorg::undecorate;
	Config.Log << std::endl;
	Config.Log << "SCENARIO #5 - ONE SMALL STEP." << std::endl;
	Config.Log << "-----------------------------" << std::endl;
	Config.Log << std::endl;
	Config.Log << "This scenario is an extension of scenario #4, before the result of a trial is determined and after Monty has opened a door" << std::endl;
	Config.Log << "we allow contestant #1 to switch doors with contestant #2." << std::endl;
	Config.Log << std::endl;
	Config.Log << xymorg::decorate;

	//  Run the contest - perform the requested number of trials with Monty and report the results
	runWithSwitching(RGen, Config);

	//  Make observations on the scenario run results
	Config.Log << xymorg::undecorate;
	Config.Log << std::endl;
	Config.Log << "OBSERVATIONS:" << std::endl;
	Config.Log << std::endl;
	Config.Log << "We have demonstrated the correctness of choosing to switch, using exactly the same protocol as is used in the gameshow." << std::endl;
	Config.Log << "Observe that contestant #2 has no agency, acting only as a placeholder for ownership of the doors not selected by Contestant #1. " << std::endl;
	Config.Log << "So I think it is Quod Erat Demonstrandum folks, good night and thank you for watching!" << std::endl;
	Config.Log << std::endl;
	Config.Log << xymorg::decorate;

	//  Show normal termination
	Config.Log << APP_TITLE << " (" << APP_NAME << ") Version: " << APP_VERSION << " has completed normally." << std::endl;

	//  Dismiss the xymorg sub-systems
	Config.dismiss();

	//
	//  PLATFORM SPECIFIC for Windows DEBUG ONLY
	//
	//  Check for memory leaks
	//
#if ((defined(_WIN32) || defined(_WIN64)) && defined(_DEBUG))
	CheckForMemoryLeaks();
#endif

	return EXIT_SUCCESS;
}

//  runTheShow
//
//  This function will simulate the show running the requested number of trials and reporting the results.
//
//	PARAMETERS:
// 
//		PRNG&		-		Reference to the entropy source (Pseudo Random Number Generator) 
//		MHPCfg&		-		Reference to the application configuration
//
//	RETURNS:
//
//	NOTES:
//

void	runTheShow(PRNG& Entropy, MHPCfg& Config) {
	Monty		MyMonty(Entropy);												//  Monty Hall - the game show host
	Contestant	MyContestant(Entropy);											//  A contestant on the show
	xymorg::TIMER	SS = xymorg::CLOCK::now();									//  Show Start time
	xymorg::TIMER	ES = xymorg::CLOCK::now();									//  Show End time
	xymorg::MILLISECONDS	ShowMS(0);											//  Show Run time in milliseconds
	int			Trials = 0;														//  Number of trials performed
	int			StickWonCar = 0;												//  Count of times that "sticking" would have won the car
	int			SwitchWonCar = 0;												//  Count of times that "switching" would have won the car
	int			CarDoor[3] = { 0,0,0 };											//  Count of times the car was placed behind each door
	int			ConGuess[3] = { 0,0,0 };										//  Count of times the contestant guessed each door
	int			Pct = 0;														//  Percentages for reporting
	int			Transient = -1;													//  Values passed between Monty and the Contestant

	//  Log the fact that the show is starting
	Config.Log << "INFO: Starting the show, performing: " << Config.getTrials() << " trials." << std::endl;

	//
	//  Perform the show by running the requested number of trials
	//

	while (Trials < Config.getTrials()) {

		//  Increment the trial counter
		Trials++;

		//  Step 1:		Monty will place the car behind a random door
		Transient = MyMonty.placeTheCar();
		if (Config.isVerboseLogging()) {
			Config.Log << "INFO: Starting trial: " << Trials << "." << std::endl;
			Config.Log << "INFO: Monty has placed the car behind door number: " << Transient << "." << std::endl;
		}
		CarDoor[Transient - 1]++;
		Transient = -1;

		//  Step 2:		Ask the contestant to select a door
		Transient = MyContestant.pickADoor();
		//  Notify the door selected to Monty
		MyMonty.selectedDoor(Transient);

		if (Config.isVerboseLogging()) {
			Config.Log << "INFO: The contestant has selected door number: " << Transient << "." << std::endl;
		}
		ConGuess[Transient - 1]++;
		Transient = -1;

		//  Step 3:		Ask Monty to open a door
		Transient = MyMonty.openADoor();
		//  Inform the contestant which door was opened
		MyContestant.openedDoor(Transient);
		if (Config.isVerboseLogging()) {
			Config.Log << "INFO: Monty has opened door number: " << Transient << ", revealing a goat." << std::endl;
		}
		Transient = -1;

		//  Step 4:		Interrogate Monty to find out if Stick or Switch would have won the car
		if (MyMonty.haveIWon(MyContestant.Stick())) {
			if (Config.isVerboseLogging()) {
				Config.Log << "INFO: The contestant has won a car by STICKING to the original door selection (" << MyContestant.Stick() << ")." << std::endl;
			}
			StickWonCar++;
		}
		if (MyMonty.haveIWon(MyContestant.Switch())) {
			if (Config.isVerboseLogging()) {
				Config.Log << "INFO: The contestant has won a car by SWITCHING from the original door selection (" << MyContestant.Switch() << ")." << std::endl;
			}
			SwitchWonCar++;
		}
	}

	//  Report the results
	ES = xymorg::CLOCK::now();
	Config.Log << "INFO: Show has ended with: " << Trials << " trials performed." << std::endl;
	Pct = (CarDoor[0] * 100) / Trials;
	Config.Log << "INFO: The car was placed behind the first door: " << CarDoor[0] << " times (" << Pct << "%)." << std::endl;
	Pct = (CarDoor[1] * 100) / Trials;
	Config.Log << "INFO: The car was placed behind the second door: " << CarDoor[1] << " times (" << Pct << "%)." << std::endl;
	Pct = (CarDoor[2] * 100) / Trials;
	Config.Log << "INFO: The car was placed behind the third door: " << CarDoor[2] << " times (" << Pct << "%)." << std::endl;
	Pct = (ConGuess[0] * 100) / Trials;
	Config.Log << "INFO: The contestant guessed the car was behind the first door: " << ConGuess[0] << " times (" << Pct << "%)." << std::endl;
	Pct = (ConGuess[1] * 100) / Trials;
	Config.Log << "INFO: The contestant guessed the car was behind the second door: " << ConGuess[1] << " times (" << Pct << "%)." << std::endl;
	Pct = (ConGuess[2] * 100) / Trials;
	Config.Log << "INFO: The contestant guessed the car was behind the third door: " << ConGuess[2] << " times (" << Pct << "%)." << std::endl;
	Pct = (StickWonCar * 100) / Trials;
	Config.Log << "INFO: Sticking won: " << StickWonCar << " cars (" << Pct << "%)." << std::endl;
	Pct = (SwitchWonCar * 100) / Trials;
	Config.Log << "INFO: Switching won: " << SwitchWonCar << " cars (" << Pct << "%)." << std::endl;
	ShowMS = DURATION(xymorg::MILLISECONDS, ES - SS);
	Config.Log << "INFO: The show ran for: " << ShowMS.count() << " ms." << std::endl;

	//  Return to caller
	return;
}

//  runTheContest
//
//  This function will simulate the contest with two contestants running the requested number of trials and reporting the results.
//
//	PARAMETERS:
// 
//		PRNG&		-		Reference to the entropy source (Pseudo Random Number Generator) 
//		MHPCfg&		-		Reference to the application configuration
//
//	RETURNS:
//
//	NOTES:
//

void	runTheContest(PRNG& Entropy, MHPCfg& Config) {
	Monty		MyMonty(Entropy);												//  Monty Hall - the game show host
	Contestant	C1(Entropy);													//  Contestant #1 on the show
	Contestant	C2(Entropy);													//  Contestant #2 on the show
	xymorg::TIMER	SS = xymorg::CLOCK::now();									//  Show Start time
	xymorg::TIMER	ES = xymorg::CLOCK::now();									//  Show End time
	xymorg::MILLISECONDS	ShowMS(0);											//  Show Run time in milliseconds
	int			Trials = 0;														//  Number of trials performed
	int			CarDoor[3] = { 0,0,0 };											//  Count of times the car was placed behind each door
	int			C1Guess[3] = { 0,0,0 };											//  Count of times that contestant #1 guessed each door
	int			C1Wins = 0;														//  Count of car wins by contestant #1
	int			C2Wins = 0;														//  Count of car wins by contestant #1
	int			Pct = 0;														//  Percentages for reporting
	int			Transient = -1;													//  Values passed between Monty and the Contestants

	//  Log the fact that the show is starting
	Config.Log << "INFO: Starting the contest, performing: " << Config.getTrials() << " trials." << std::endl;

	//
	//  Perform the contest by running the requested number of trials
	//

	while (Trials < Config.getTrials()) {

		//  Increment the trial counter
		Trials++;

		//  Step 1:		Monty will place the car behind a random door
		Transient = MyMonty.placeTheCar();
		if (Config.isVerboseLogging()) {
			Config.Log << "INFO: Starting trial: " << Trials << "." << std::endl;
			Config.Log << "INFO: Monty has placed the car behind door number: " << Transient << "." << std::endl;
		}
		CarDoor[Transient - 1]++;
		Transient = -1;

		//  Step 2:		Ask the contestant to select a door
		Transient = C1.pickADoor();
		//  Notify the door selected to Monty
		MyMonty.selectedDoor(Transient);
		//  Notify the door selected to contestant #2
		C2.selectedDoor(Transient);

		if (Config.isVerboseLogging()) {
			Config.Log << "INFO: Contestant #1 has selected door number: " << Transient << "." << std::endl;
		}
		C1Guess[Transient - 1]++;
		Transient = -1;

		//  Step 3:		Interrogate Monty to find out if contestant #1 or contestant #2 would have won the car
		if (MyMonty.haveIWon(C1.Stick())) {
			if (Config.isVerboseLogging()) {
				Config.Log << "INFO: Contestant #1 has won a car with selection (" << C1.Stick() << ")." << std::endl;
			}
			C1Wins++;
		}
		if (MyMonty.haveIWon(C2.firstDoor())) {
			if (Config.isVerboseLogging()) {
				Config.Log << "INFO: Contestant #2 has won a car with selection (" << C2.firstDoor() << ")." << std::endl;
			}
			C2Wins++;
		}
		if (MyMonty.haveIWon(C2.secondDoor())) {
			if (Config.isVerboseLogging()) {
				Config.Log << "INFO: Contestant #2 has won a car with selection (" << C2.secondDoor() << ")." << std::endl;
			}
			C2Wins++;
		}
	}

	//  Report the results
	ES = xymorg::CLOCK::now();
	Config.Log << "INFO: The contest has ended with: " << Trials << " trials performed." << std::endl;
	Pct = (CarDoor[0] * 100) / Trials;
	Config.Log << "INFO: The car was placed behind the first door: " << CarDoor[0] << " times (" << Pct << "%)." << std::endl;
	Pct = (CarDoor[1] * 100) / Trials;
	Config.Log << "INFO: The car was placed behind the second door: " << CarDoor[1] << " times (" << Pct << "%)." << std::endl;
	Pct = (CarDoor[2] * 100) / Trials;
	Config.Log << "INFO: The car was placed behind the third door: " << CarDoor[2] << " times (" << Pct << "%)." << std::endl;
	Pct = (C1Guess[0] * 100) / Trials;
	Config.Log << "INFO: The first contestant guessed the car was behind the first door: " << C1Guess[0] << " times (" << Pct << "%)." << std::endl;
	Pct = (C1Guess[1] * 100) / Trials;
	Config.Log << "INFO: The first contestant guessed the car was behind the second door: " << C1Guess[1] << " times (" << Pct << "%)." << std::endl;
	Pct = (C1Guess[2] * 100) / Trials;
	Config.Log << "INFO: The first contestant guessed the car was behind the third door: " << C1Guess[2] << " times (" << Pct << "%)." << std::endl;
	Pct = (C1Wins * 100) / Trials;
	Config.Log << "INFO: Contestant #1 won: " << C1Wins << " cars (" << Pct << "%)." << std::endl;
	Pct = (C2Wins * 100) / Trials;
	Config.Log << "INFO: Contestant #2 won: " << C2Wins << " cars (" << Pct << "%)." << std::endl;
	ShowMS = DURATION(xymorg::MILLISECONDS, ES - SS);
	Config.Log << "INFO: The contest ran for: " << ShowMS.count() << " ms." << std::endl;

	//  Return to caller
	return;
}

//  runWithMonty
//
//  This function will simulate the contest with two contestants running the requested number of trials and reporting the results.
//  Monty is allowed to open one of the doors allocated to contestant #2. 
//
//	PARAMETERS:
// 
//		PRNG&		-		Reference to the entropy source (Pseudo Random Number Generator) 
//		MHPCfg&		-		Reference to the application configuration
//
//	RETURNS:
//
//	NOTES:
//

void	runWithMonty(PRNG& Entropy, MHPCfg& Config) {
	Monty		MyMonty(Entropy);												//  Monty Hall - the game show host
	Contestant	C1(Entropy);													//  Contestant #1 on the show
	Contestant	C2(Entropy);													//  Contestant #2 on the show
	xymorg::TIMER	SS = xymorg::CLOCK::now();									//  Show Start time
	xymorg::TIMER	ES = xymorg::CLOCK::now();									//  Show End time
	xymorg::MILLISECONDS	ShowMS(0);											//  Show Run time in milliseconds
	int			Trials = 0;														//  Number of trials performed
	int			CarDoor[3] = { 0,0,0 };											//  Count of times the car was placed behind each door
	int			C1Guess[3] = { 0,0,0 };											//  Count of times that contestant #1 guessed each door
	int			C1Wins = 0;														//  Count of car wins by contestant #1
	int			C2Wins = 0;														//  Count of car wins by contestant #1
	int			MontyWins = 0;													//  Count of car wins by Monty
	int			Pct = 0;														//  Percentages for reporting
	int			Transient = -1;													//  Values passed between Monty and the Contestants

	//  Log the fact that the show is starting
	Config.Log << "INFO: Starting the contest, performing: " << Config.getTrials() << " trials." << std::endl;

	//
	//  Perform the contest by running the requested number of trials
	//

	while (Trials < Config.getTrials()) {

		//  Increment the trial counter
		Trials++;

		//  Step 1:		Monty will place the car behind a random door
		Transient = MyMonty.placeTheCar();
		if (Config.isVerboseLogging()) {
			Config.Log << "INFO: Starting trial: " << Trials << "." << std::endl;
			Config.Log << "INFO: Monty has placed the car behind door number: " << Transient << "." << std::endl;
		}
		CarDoor[Transient - 1]++;
		Transient = -1;

		//  Step 2:		Ask the contestant to select a door
		Transient = C1.pickADoor();
		//  Notify the door selected to Monty
		MyMonty.selectedDoor(Transient);
		//  Notify the door selected to contestant #2
		C2.selectedDoor(Transient);

		if (Config.isVerboseLogging()) {
			Config.Log << "INFO: Contestant #1 has selected door number: " << Transient << "." << std::endl;
		}
		C1Guess[Transient - 1]++;
		Transient = -1;

		//  Step 3:		Allow Monty to open one of the doors (at random) that was allocated to contestant #2
		Transient = MyMonty.openADoorAtRandom();
		if (Config.isVerboseLogging()) {
			Config.Log << "INFO: Monty has opened door number: " << Transient << "." << std::endl;
		}

		//  Step 4:		Interrogate Monty to find out if contestant #1 or contestant #2 would have won the car
		if (MyMonty.haveIWon(C1.Stick())) {
			if (Config.isVerboseLogging()) {
				Config.Log << "INFO: Contestant #1 has won a car with selection (" << C1.Stick() << ")." << std::endl;
			}
			C1Wins++;
		}
		if (MyMonty.haveIWon(C2.firstDoor())) {
			if (Config.isVerboseLogging()) {
				Config.Log << "INFO: Contestant #2 has won a car with selection (" << C2.firstDoor() << ")." << std::endl;
			}
			C2Wins++;
		}
		if (MyMonty.haveIWon(C2.secondDoor())) {
			if (Config.isVerboseLogging()) {
				Config.Log << "INFO: Contestant #2 has won a car with selection (" << C2.secondDoor() << ")." << std::endl;
			}
			C2Wins++;
		}
		if (MyMonty.didYouWin()) {
			if (Config.isVerboseLogging()) {
				Config.Log << "INFO: Monty has won a car with selection (" << C2.secondDoor() << ")." << std::endl;
			}
			MontyWins++;
		}
	}

	//  Report the results
	ES = xymorg::CLOCK::now();
	Config.Log << "INFO: The contest has ended with: " << Trials << " trials performed." << std::endl;
	Pct = (CarDoor[0] * 100) / Trials;
	Config.Log << "INFO: The car was placed behind the first door: " << CarDoor[0] << " times (" << Pct << "%)." << std::endl;
	Pct = (CarDoor[1] * 100) / Trials;
	Config.Log << "INFO: The car was placed behind the second door: " << CarDoor[1] << " times (" << Pct << "%)." << std::endl;
	Pct = (CarDoor[2] * 100) / Trials;
	Config.Log << "INFO: The car was placed behind the third door: " << CarDoor[2] << " times (" << Pct << "%)." << std::endl;
	Pct = (C1Guess[0] * 100) / Trials;
	Config.Log << "INFO: The first contestant guessed the car was behind the first door: " << C1Guess[0] << " times (" << Pct << "%)." << std::endl;
	Pct = (C1Guess[1] * 100) / Trials;
	Config.Log << "INFO: The first contestant guessed the car was behind the second door: " << C1Guess[1] << " times (" << Pct << "%)." << std::endl;
	Pct = (C1Guess[2] * 100) / Trials;
	Config.Log << "INFO: The first contestant guessed the car was behind the third door: " << C1Guess[2] << " times (" << Pct << "%)." << std::endl;
	Pct = (C1Wins * 100) / Trials;
	Config.Log << "INFO: Contestant #1 won: " << C1Wins << " cars (" << Pct << "%)." << std::endl;
	Pct = (C2Wins * 100) / Trials;
	Config.Log << "INFO: Contestant #2 won: " << C2Wins << " cars (" << Pct << "%)." << std::endl;
	Pct = (MontyWins * 100) / Trials;
	Config.Log << "INFO: Monty won: " << MontyWins << " cars (" << Pct << "%)." << std::endl;
	ShowMS = DURATION(xymorg::MILLISECONDS, ES - SS);
	Config.Log << "INFO: The contest ran for: " << ShowMS.count() << " ms." << std::endl;

	//  Return to caller
	return;
}

//  runWithMontyConstrained
//
//  This function will simulate the contest with two contestants running the requested number of trials and reporting the results.
//  Monty is allowed to open one of the doors allocated to contestant #2, the door MUST have a goat behind it. 
//
//	PARAMETERS:
// 
//		PRNG&		-		Reference to the entropy source (Pseudo Random Number Generator) 
//		MHPCfg&		-		Reference to the application configuration
//
//	RETURNS:
//
//	NOTES:
//

void	runWithMontyConstrained(PRNG& Entropy, MHPCfg& Config) {
	Monty		MyMonty(Entropy);												//  Monty Hall - the game show host
	Contestant	C1(Entropy);													//  Contestant #1 on the show
	Contestant	C2(Entropy);													//  Contestant #2 on the show
	xymorg::TIMER	SS = xymorg::CLOCK::now();									//  Show Start time
	xymorg::TIMER	ES = xymorg::CLOCK::now();									//  Show End time
	xymorg::MILLISECONDS	ShowMS(0);											//  Show Run time in milliseconds
	int			Trials = 0;														//  Number of trials performed
	int			CarDoor[3] = { 0,0,0 };											//  Count of times the car was placed behind each door
	int			C1Guess[3] = { 0,0,0 };											//  Count of times that contestant #1 guessed each door
	int			C1Wins = 0;														//  Count of car wins by contestant #1
	int			C2Wins = 0;														//  Count of car wins by contestant #2
	int			MontyWins = 0;													//  Count of car wins by Monty
	int			Pct = 0;														//  Percentages for reporting
	int			Transient = -1;													//  Values passed between Monty and the Contestants

	//  Log the fact that the show is starting
	Config.Log << "INFO: Starting the contest, performing: " << Config.getTrials() << " trials." << std::endl;

	//
	//  Perform the contest by running the requested number of trials
	//

	while (Trials < Config.getTrials()) {

		//  Increment the trial counter
		Trials++;

		//  Step 1:		Monty will place the car behind a random door
		Transient = MyMonty.placeTheCar();
		if (Config.isVerboseLogging()) {
			Config.Log << "INFO: Starting trial: " << Trials << "." << std::endl;
			Config.Log << "INFO: Monty has placed the car behind door number: " << Transient << "." << std::endl;
		}
		CarDoor[Transient - 1]++;
		Transient = -1;

		//  Step 2:		Ask the contestant to select a door
		Transient = C1.pickADoor();
		//  Notify the door selected to Monty
		MyMonty.selectedDoor(Transient);
		//  Notify the door selected to contestant #2
		C2.selectedDoor(Transient);

		if (Config.isVerboseLogging()) {
			Config.Log << "INFO: Contestant #1 has selected door number: " << Transient << "." << std::endl;
		}
		C1Guess[Transient - 1]++;
		Transient = -1;

		//  Step 3:		Allow Monty to open one of the doors (with a goat) that was allocated to contestant #2
		Transient = MyMonty.openADoor();
		if (Config.isVerboseLogging()) {
			Config.Log << "INFO: Monty has opened door number: " << Transient << "." << std::endl;
		}

		//  Step 4:		Interrogate Monty to find out if contestant #1 or contestant #2 would have won the car
		if (MyMonty.haveIWon(C1.Stick())) {
			if (Config.isVerboseLogging()) {
				Config.Log << "INFO: Contestant #1 has won a car with selection (" << C1.Stick() << ")." << std::endl;
			}
			C1Wins++;
		}
		if (MyMonty.haveIWon(C2.firstDoor())) {
			if (Config.isVerboseLogging()) {
				Config.Log << "INFO: Contestant #2 has won a car with selection (" << C2.firstDoor() << ")." << std::endl;
			}
			C2Wins++;
		}
		if (MyMonty.haveIWon(C2.secondDoor())) {
			if (Config.isVerboseLogging()) {
				Config.Log << "INFO: Contestant #2 has won a car with selection (" << C2.secondDoor() << ")." << std::endl;
			}
			C2Wins++;
		}
		if (MyMonty.didYouWin()) {
			if (Config.isVerboseLogging()) {
				Config.Log << "INFO: Monty has won a car with selection (" << C2.secondDoor() << ")." << std::endl;
			}
			MontyWins++;
		}
	}

	//  Report the results
	ES = xymorg::CLOCK::now();
	Config.Log << "INFO: The contest has ended with: " << Trials << " trials performed." << std::endl;
	Pct = (CarDoor[0] * 100) / Trials;
	Config.Log << "INFO: The car was placed behind the first door: " << CarDoor[0] << " times (" << Pct << "%)." << std::endl;
	Pct = (CarDoor[1] * 100) / Trials;
	Config.Log << "INFO: The car was placed behind the second door: " << CarDoor[1] << " times (" << Pct << "%)." << std::endl;
	Pct = (CarDoor[2] * 100) / Trials;
	Config.Log << "INFO: The car was placed behind the third door: " << CarDoor[2] << " times (" << Pct << "%)." << std::endl;
	Pct = (C1Guess[0] * 100) / Trials;
	Config.Log << "INFO: The first contestant guessed the car was behind the first door: " << C1Guess[0] << " times (" << Pct << "%)." << std::endl;
	Pct = (C1Guess[1] * 100) / Trials;
	Config.Log << "INFO: The first contestant guessed the car was behind the second door: " << C1Guess[1] << " times (" << Pct << "%)." << std::endl;
	Pct = (C1Guess[2] * 100) / Trials;
	Config.Log << "INFO: The first contestant guessed the car was behind the third door: " << C1Guess[2] << " times (" << Pct << "%)." << std::endl;
	Pct = (C1Wins * 100) / Trials;
	Config.Log << "INFO: Contestant #1 won: " << C1Wins << " cars (" << Pct << "%)." << std::endl;
	Pct = (C2Wins * 100) / Trials;
	Config.Log << "INFO: Contestant #2 won: " << C2Wins << " cars (" << Pct << "%)." << std::endl;
	Pct = (MontyWins * 100) / Trials;
	Config.Log << "INFO: Monty won: " << MontyWins << " cars (" << Pct << "%)." << std::endl;
	ShowMS = DURATION(xymorg::MILLISECONDS, ES - SS);
	Config.Log << "INFO: The contest ran for: " << ShowMS.count() << " ms." << std::endl;

	//  Return to caller
	return;
}

//  runWithSwitching
//
//  This function will simulate the contest with two contestants running the requested number of trials and reporting the results.
//  Monty is allowed to open one of the doors allocated to contestant #2, the door MUST have a goat behind it.
//  Contestant #1 is allowed to stick with the originally selected door or switch doors with contestant #2.
//
//	PARAMETERS:
// 
//		PRNG&		-		Reference to the entropy source (Pseudo Random Number Generator) 
//		MHPCfg&		-		Reference to the application configuration
//
//	RETURNS:
//
//	NOTES:
//

void	runWithSwitching(PRNG& Entropy, MHPCfg& Config) {
	Monty		MyMonty(Entropy);												//  Monty Hall - the game show host
	Contestant	C1(Entropy);													//  Contestant #1 on the show
	Contestant	C2(Entropy);													//  Contestant #2 on the show
	xymorg::TIMER	SS = xymorg::CLOCK::now();									//  Show Start time
	xymorg::TIMER	ES = xymorg::CLOCK::now();									//  Show End time
	xymorg::MILLISECONDS	ShowMS(0);											//  Show Run time in milliseconds
	int			Trials = 0;														//  Number of trials performed
	int			CarDoor[3] = { 0,0,0 };											//  Count of times the car was placed behind each door
	int			C1Guess[3] = { 0,0,0 };											//  Count of times that contestant #1 guessed each door
	int			StickC1Wins = 0;												//  Count of car wins by contestant #1 when sticking
	int			StickC2Wins = 0;												//  Count of car wins by contestant #2 when sticking
	int			SwitchC1Wins = 0;												//  Count of car wins by contestant #1 when switching
	int			SwitchC2Wins = 0;												//  Count of car wins by contestant #2 when switching
	int			MontyWins = 0;													//  Count of car wins by Monty
	int			Pct = 0;														//  Percentages for reporting
	int			Transient = -1;													//  Values passed between Monty and the Contestants

	//  Log the fact that the show is starting
	Config.Log << "INFO: Starting the contest, performing: " << Config.getTrials() << " trials." << std::endl;

	//
	//  Perform the contest by running the requested number of trials
	//

	while (Trials < Config.getTrials()) {

		//  Increment the trial counter
		Trials++;

		//  Step 1:		Monty will place the car behind a random door
		Transient = MyMonty.placeTheCar();
		if (Config.isVerboseLogging()) {
			Config.Log << "INFO: Starting trial: " << Trials << "." << std::endl;
			Config.Log << "INFO: Monty has placed the car behind door number: " << Transient << "." << std::endl;
		}
		CarDoor[Transient - 1]++;
		Transient = -1;

		//  Step 2:		Ask the contestant to select a door
		Transient = C1.pickADoor();
		//  Notify the door selected to Monty
		MyMonty.selectedDoor(Transient);
		//  Notify the door selected to contestant #2
		C2.selectedDoor(Transient);

		if (Config.isVerboseLogging()) {
			Config.Log << "INFO: Contestant #1 has selected door number: " << Transient << "." << std::endl;
		}
		C1Guess[Transient - 1]++;
		Transient = -1;

		//  Step 3:		Allow Monty to open one of the doors (with a goat) that was allocated to contestant #2
		Transient = MyMonty.openADoor();
		if (Config.isVerboseLogging()) {
			Config.Log << "INFO: Monty has opened door number: " << Transient << "." << std::endl;
		}

		//  Step 4:		Interrogate Monty to find out if contestant #1 or contestant #2 would have won the car.
		//				Results are collected for sticking and switching
		
		//  STICK
		
		if (MyMonty.haveIWon(C1.Stick())) {
			if (Config.isVerboseLogging()) {
				Config.Log << "INFO: Contestant #1 has won a car by sticking with selection (" << C1.Stick() << ")." << std::endl;
			}
			StickC1Wins++;
		}
		if (MyMonty.haveIWon(C2.firstDoor())) {
			if (Config.isVerboseLogging()) {
				Config.Log << "INFO: Contestant #2 has won a car by sticking with selection (" << C2.firstDoor() << ")." << std::endl;
			}
			StickC2Wins++;
		}
		if (MyMonty.haveIWon(C2.secondDoor())) {
			if (Config.isVerboseLogging()) {
				Config.Log << "INFO: Contestant #2 has won a car by sticking with selection (" << C2.secondDoor() << ")." << std::endl;
			}
			StickC2Wins++;
		}

		//  SWITCH

		if (MyMonty.haveIWon(C1.Stick())) {
			if (Config.isVerboseLogging()) {
				Config.Log << "INFO: Contestant #2 has won a car by switching to selection (" << C1.Stick() << ")." << std::endl;
			}
			SwitchC2Wins++;
		}
		if (MyMonty.haveIWon(C2.firstDoor())) {
			if (Config.isVerboseLogging()) {
				Config.Log << "INFO: Contestant #1 has won a car by switching selection (" << C2.firstDoor() << ")." << std::endl;
			}
			SwitchC1Wins++;
		}
		if (MyMonty.haveIWon(C2.secondDoor())) {
			if (Config.isVerboseLogging()) {
				Config.Log << "INFO: Contestant #1 has won a car by switching selection (" << C2.secondDoor() << ")." << std::endl;
			}
			SwitchC1Wins++;
		}

		if (MyMonty.didYouWin()) {
			if (Config.isVerboseLogging()) {
				Config.Log << "INFO: Monty has won a car with selection (" << C2.secondDoor() << ")." << std::endl;
			}
			MontyWins++;
		}
	}

	//  Report the results
	ES = xymorg::CLOCK::now();
	Config.Log << "INFO: The contest has ended with: " << Trials << " trials performed." << std::endl;
	Pct = (CarDoor[0] * 100) / Trials;
	Config.Log << "INFO: The car was placed behind the first door: " << CarDoor[0] << " times (" << Pct << "%)." << std::endl;
	Pct = (CarDoor[1] * 100) / Trials;
	Config.Log << "INFO: The car was placed behind the second door: " << CarDoor[1] << " times (" << Pct << "%)." << std::endl;
	Pct = (CarDoor[2] * 100) / Trials;
	Config.Log << "INFO: The car was placed behind the third door: " << CarDoor[2] << " times (" << Pct << "%)." << std::endl;
	Pct = (C1Guess[0] * 100) / Trials;
	Config.Log << "INFO: The first contestant guessed the car was behind the first door: " << C1Guess[0] << " times (" << Pct << "%)." << std::endl;
	Pct = (C1Guess[1] * 100) / Trials;
	Config.Log << "INFO: The first contestant guessed the car was behind the second door: " << C1Guess[1] << " times (" << Pct << "%)." << std::endl;
	Pct = (C1Guess[2] * 100) / Trials;
	Config.Log << "INFO: The first contestant guessed the car was behind the third door: " << C1Guess[2] << " times (" << Pct << "%)." << std::endl;
	//  STICK
	Pct = (StickC1Wins * 100) / Trials;
	Config.Log << "INFO: Contestant #1 won: " << StickC1Wins << " cars (" << Pct << "%) by sticking to their original choice." << std::endl;
	Pct = (StickC2Wins * 100) / Trials;
	Config.Log << "INFO: Contestant #2 won: " << StickC2Wins << " cars (" << Pct << "%) by sticking with their original allocation." << std::endl;
	Pct = (MontyWins * 100) / Trials;
	//  SWITCH
	Pct = (SwitchC1Wins * 100) / Trials;
	Config.Log << "INFO: Contestant #1 won: " << SwitchC1Wins << " cars (" << Pct << "%) by switching from their original choice." << std::endl;
	Pct = (SwitchC2Wins * 100) / Trials;
	Config.Log << "INFO: Contestant #2 won: " << SwitchC2Wins << " cars (" << Pct << "%) by switching from their original allocation." << std::endl;
	Pct = (MontyWins * 100) / Trials;
	Config.Log << "INFO: Monty won: " << MontyWins << " cars (" << Pct << "%)." << std::endl;
	ShowMS = DURATION(xymorg::MILLISECONDS, ES - SS);
	Config.Log << "INFO: The contest ran for: " << ShowMS.count() << " ms." << std::endl;

	//  Return to caller
	return;
}
