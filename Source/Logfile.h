
/**
 *
 *	Logfile.h
 *
 *	This file contains a set of functions for writing and reading
 *	to/from a log file. Specify which file to use with the function
 *	setLogFile.
 *
 *	Author:	Johan Öfverstedt
 *
 */

#ifndef LOGFILE_H
#define LOGFILE_H

/**
 *
 *	The namespace LogFile contains functions for managing a log file:
 *  
 *	Clearing the log.
 *	Reading the contents of the log.
 *	Writing formatted data to the log.
 *
 */

namespace LogFile
{

	extern char *currentLogFile;

	void clearLog(); //Clears the specified log file.
	
	char *getLogFile(); //Gets the current log file.
		
	void setLogFile(char *file); //Sets the current log file.
	
	void writeLog(char *msg, ...); //Appends the formatted string to the current log file.

};

#endif