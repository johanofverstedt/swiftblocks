
/**
 *
 *	ConfigParser.h
 *
 *	This file contains the definition of the ConfigParser
 *	class which is used to read the configuration file.
 *
 *	Author:	Johan Öfverstedt
 *
 */

#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include <iostream>
#include <math.h>

using namespace std;

class ConfigParser
{

protected:

	string m_buffer;

	long m_pos;

	string m_source;

	bool parseFloat(string str, float *out);
	
	string parseLine();

	bool parseLong(string str, long *out);

	void removeBlanks(string *str);

public:

	ConfigParser();
	
	~ConfigParser();
	
	bool loadFile(string file);

	float readFloat(string var, float dflt);
	
	long readLong(string var, long dflt);

	string readString(string var, string dflt);
	
};

#endif