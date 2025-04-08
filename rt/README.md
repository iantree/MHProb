THE MHProb APPLICATION
----------------------

The MHProb application illustrates the Monty Hall Problem and provides a series of scenarios that demonstrate the 
corectness of supporting the "switch" strategy.

Running The Application
-----------------------

Run the application from the rt/ directory. Setup the application by either editing the rt/Config/MHProb.xml file
or specifying command line parameters.

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
//*		-E or (-e)		==> Echo the log to the console															*
//*		-T:n or -t:n		==> Perform n trials																	*
//*																													*
//*******************************************************************************************************************

The resulting log file for a run can be found in the rt/Logs directory.

WARNING
-------

Verbose means verbose do not specify verbose logging with a large number of trials as it will generate
an extremely large log file.

