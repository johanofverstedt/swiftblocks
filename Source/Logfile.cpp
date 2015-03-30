
/**
 *
 *	Logfile.cpp
 *
 *	This file contains a set of functions for writing and reading
 *	to/from a log file. Specify which file to use with the function
 *	setLogFile.
 *
 *	Author:	Johan Öfverstedt
 *
 */

//Basic Input/Output header:
#include <iostream>

//Standard argument header:
#include "stdarg.h"

//Game headers:
#include "Logfile.h"

char *LogFile::currentLogFile = "./log.txt";

/**
 *
 *	Function LogFile::clearLog()
 *
 *	Clears the specified log file.
 *
 */

void LogFile::clearLog()
{

	FILE *hFile = 0;

	if(currentLogFile == 0)
	{

		return;

	}
		
	hFile =	fopen(currentLogFile, "w+");
	
	fwrite("", 0, 0, hFile);

	fclose(hFile);

}

/**
 *
 *	Function LogFile::getLogFile()
 *
 *	Retrieves the current log file.
 *
 */

char *LogFile::getLogFile()
{

	return currentLogFile;

}

/**
 *
 *	Function LogFile::setLogFile()
 *
 *	Sets the current log file.
 *
 */

void LogFile::setLogFile(char *file)
{

	currentLogFile = file;

}

/**
 *
 *	Function LogFile::writeLog()
 *
 *	Appends a formatted string to the current
 *	log file.
 *
 */

void LogFile::writeLog(char *msg, ...)
{

	va_list list;
	char buffer[512];
	int bytes = 0;
	FILE *hFile = 0;

	if(currentLogFile == 0)
	{

		return;

	}

	hFile = fopen(currentLogFile, "a+");

	va_start(list, msg);

		bytes = vsprintf(buffer, msg, list);

	va_end(list);

	fwrite(buffer, bytes, 1, hFile);

	fclose(hFile);

}
