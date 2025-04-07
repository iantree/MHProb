#pragma once
//*******************************************************************************************************************
//*																													*
//*   File:       MHPCfg.h																							*
//*   Suite:      Experimental Algorithms																			*
//*   Version:    1.0.0	(Build: 01)																					*
//*   Author:     Ian Tree/HMNL																						*
//*																													*
//*   Copyright 2017 - 2025 Ian J. Tree.														*
//*******************************************************************************************************************
//*	MHPCfg																											*
//*																													*
//*	This header extends the xymorg AppConfig class to define the class that provides the singleton containing		*
//* all application configuration data plus the xymorg service access objects.										*
//*																													*
//*	USAGE:																											*
//*																													*
//*		The class definition must extend the xymorg::AppConfig class												*
//*																													*
//*	NOTES:																											*
//*																													*
//*	1.																												*
//*																													*
//*******************************************************************************************************************
//*	CONFIGURATION XML SPECIFICATION																					*
//*	---------------------------																						*
//*																													*
//*		<monty trials="t"></monty>																					*
//*																													*
//*			where t is the number of number of trials to perform													*
//*																													*
//*******************************************************************************************************************
//*	COMMAND LINE SPECIFICATION																						*
//*	--------------------------																						*
//*																													*
//*		MHProb -V -E -T:n																							*
//*																													*
//*		Where -V or (-v)	==>	Verbose logging enabled																*
//*		-E or (-e)			==> Echo the log to the console															*
//*		-T:n or -t:n		==> Perform n trials																	*
//*																													*
//*******************************************************************************************************************
//*																													*
//*   History:																										*
//*																													*
//*	1.0.0 -		01/04/2025	-	Initial Release																		*
//*																													*
//*******************************************************************************************************************/

//  Include xymorg headers
#include	"../xymorg/xymorg.h"															//  xymorg system headers

//
//  MHPCfg Class
//

class MHPCfg : public xymorg::AppConfig {
public:

	//*******************************************************************************************************************
	//*                                                                                                                 *
	//*   Constructors			                                                                                        *
	//*                                                                                                                 *
	//*******************************************************************************************************************

	//  Constructor 
	//
	//  Constructs the application configuration object and loads the persistent settings from the config file and command line
	//
	//  PARAMETERS:
	//
	//		char *			-		Const pointer to the application name
	//		int				-		Count of application invocation parameters
	//		char*[]			-		Array of pointers to the application invocation parameters
	//
	//  RETURNS:
	//
	//  NOTES:
	//

	MHPCfg(const char* szAppName, int argc, char* argv[])
		: xymorg::AppConfig(szAppName, argc, argv)
		, ConfigValid(false)
		, NumTrials(-1)
	{
		//  Handle any command line parameters
		if (handleCmdLine(argc, argv)) ConfigValid = true;

		//  Handle the local application configuration settings (if needed)
		if (!ConfigValid) {
			if (pCfgImg == nullptr) handleNoConfig();
			else handleConfig();
		}

		//  Release the configuration image
		releaseConfigImage();

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
	//  Destroys the MHPCfg object, dismissing the underlying objects/allocations
	//
	//  PARAMETERS:
	//
	//  RETURNS:
	//
	//  NOTES:
	//  

	~MHPCfg() {

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

	//  isValid
	//
	//  This function will return the state of the configuration
	//
	//	PARAMETERS:
	//
	//	RETURNS:
	//
	//		bool		-		The current validity state
	//
	//	NOTES:
	//

	bool	isValid() const { return ConfigValid; }

	//  getTrials
	//
	//  This function will return the number of trials requested
	//
	//	PARAMETERS:
	//
	//	RETURNS:
	//
	//		int		-		The requested number of trials
	//
	//	NOTES:
	//

	int		getTrials() const { return NumTrials; }

private:

	//*******************************************************************************************************************
	//*                                                                                                                 *
	//*   Private Members			                                                                                    *
	//*                                                                                                                 *
	//*******************************************************************************************************************

	bool				ConfigValid;												//  Validity state of configuration
	int					NumTrials;													//  Number of trials to perform

	//*******************************************************************************************************************
	//*                                                                                                                 *
	//*   Private Functions                                                                                             *
	//*                                                                                                                 *
	//*******************************************************************************************************************

	//  handleCmdLine
	//
	//  This function will handle the parsing of parameters from the command line.
	//
	//  PARAMETERS:
	//
	//		int				-		Count of application invocation parameters
	//		char*[]			-		Array of pointers to the application invocation parameters
	//
	//  RETURNS:
	// 
	//		bool		-		if true then parsing of the configuration XML is not required
	//
	//  NOTES:
	//

	bool	handleCmdLine(int argc, char* argv[]) {
		int				FirstSwitch = 1;															//  First switch parameter 
		bool			Configured = false;															//  Fully configured indicator
		bool			SWValid = false;															//  Switch validity

		//  No parameters are present on the command line - use the config XML file
		if (argc == 1) return false;

		//  If the first command line parameter is in use (xymorg project root directory) then bump the first switch
		if (isFirstCLPUsed()) {
			FirstSwitch = 2;
			if (argc == 2) return false;
		}

		//  Process each switch in turn
		for (int SWX = FirstSwitch; SWX < argc; SWX++) {
			SWValid = false;

			//  Test for logging verbosity asserted
			if (strlen(argv[SWX]) == 2) {
				if (_memicmp(argv[SWX], "-V", 2) == 0) {
					SWValid = true;
					setVerboseLogging(true);
				}
			}

			//  Test for log echoing
			if (strlen(argv[SWX]) == 2) {
				if (_memicmp(argv[SWX], "-E", 2) == 0) {
					SWValid = true;
					setEchoLogging(true);
				}
			}

			//  Test for number of trials
			if (strlen(argv[SWX]) > 3) {
				if (_memicmp(argv[SWX], "-T:", 3) == 0) {
					SWValid = true;
					NumTrials = atoi(argv[SWX] + 3);
					if (NumTrials < 1) {
						Log << "ERROR: The number of trials specified on the command line -T:n, n MUST be greater than 0." << std::endl;
						return false;
					}
					else Configured = true;
				}
			}

			//  Invalid switch
			if (!SWValid) {
				Log << "ERROR: Command line parameter: '" << argv[SWX] << "' is invalid and has been ignored." << std::endl;
			}
		}
		
		//  Return the configuration state
		return Configured;
	}

	//  handleNoConfig
	//
	//  This function is the handler for the "No Config Loaded" event. It will clear the validity flag.
	//
	//  PARAMETERS:
	//
	//  RETURNS:
	//
	//  NOTES:
	//

	void handleNoConfig() {

		//  Clear the validity flage
		ConfigValid = false;

		Log << "ERROR: Unable to load the application configuration." << std::endl;

		//  Return to caller
		return;
	}

	//  handleConfig
	//
	//  This function is the handler for the "Config Loaded" event. It will parse the application specific values from the 
	//  configuration file and set the validity indicator.
	//
	//  PARAMETERS:
	//
	//  RETURNS:
	//
	//  NOTES:
	//

	void	handleConfig() {
		xymorg::XMLMicroParser					CfgXML(pCfgImg);									//  XML Micro Parser for the application configuration file
		xymorg::XMLMicroParser::XMLIterator		MNode = CfgXML.getScope("monty");					//  Monty definition node of the configuration

		//  Safety/Validity
		ConfigValid = false;
		if (!CfgXML.isValid()) {
			Log << "ERROR: The configuration XML is not a valid XML document." << std::endl;
			return;
		}

		if (MNode.isNull() || MNode.isClosing()) {
			Log << "ERROR: There is no valid <monty> in the configuration XML document." << std::endl;
			return;
		}

		//  Extract the number of trials to perform
		NumTrials = MNode.getAttributeInt("trials");

		//  Validate the number of trials
		if (NumTrials <= 0) {
			Log << "ERROR: The number of trials (trials=) attribute on the <monty> node is invalid or missing." << std::endl;
			return;
		}

		//  Mark configuration as valid
		ConfigValid = true;

		//  Return to caller
		return;
	}
};