#pragma once
//*******************************************************************************************************************
//*																													*
//*   File:       MHProb.h																							*
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

//  Define xymorg sub-system requirements

//  Include xymorg headers
#include	"../xymorg/xymorg.h"															//  xymorg system headers

//  Define the type of Pseudo Random Number Generator (PRNG) to use
typedef		std::mt19937			PRNG;

//  Application Headers
#include	"MHPCfg.h"
#include	"Monty.h"
#include	"Contestant.h"

//  Identification Constants
constexpr auto		APP_NAME = "MHProb";
constexpr auto		APP_TITLE = "Monty Hall Problem";
#ifdef _DEBUG
constexpr auto		APP_VERSION = "1.0.0 build: 01 Debug";
#else
constexpr auto		APP_VERSION = "1.0.0 build: 01";
#endif

//  Forward Declarations/ Function Prototypes
void	runTheShow(PRNG& Entropy, MHPCfg& Config);										//  Run the show
void	runTheContest(PRNG& Entropy, MHPCfg& Config);									//  Run the contest (with two contestants)
void	runWithMonty(PRNG& Entropy, MHPCfg& Config);									//  Run the contest (with Monty)
void	runWithMontyConstrained(PRNG& Entropy, MHPCfg& Config);							//  Run the contest (with Monty constrained)
void	runWithSwitching(PRNG& Entropy, MHPCfg& Config);								//  Run the contest (with door switching)
