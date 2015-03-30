
/**
 *
 *	ConfigParser.cpp
 *
 *	This file contains the implementation of the ConfigParser
 *	class which is used to read the configuration file.
 *
 *	Author:	Johan Öfverstedt
 *
 */

#include "ConfigParser.h"
#include <fstream>

ConfigParser::ConfigParser()
{

	m_buffer = "";

	m_pos = 0;

	m_source = "";
	
}

ConfigParser::~ConfigParser()
{

	m_buffer = "";

	m_buffer.resize(0);

	m_pos = 0;

	m_source = "";

	m_source.resize(0);

}

bool ConfigParser::loadFile(string file)
{

	char byte = 0;

	ifstream in(file.c_str(), ios::in);
	
	if(!in)
	{

		return false;

	}

	m_source = "";

	while(!in.eof())
	{

		m_source += in.get();

	}
	
	if(m_source.size() < 1)
	{

		return false;

	}

	return true;

}

string ConfigParser::parseLine()
{

	bool middleOfString = false;

	char *latest = new char[2];

	int readCount = 0;

	bool comment = false;

	m_buffer = "";

	while(true)
	{
	
		if(m_pos > m_source.size() - 1)
		{
			
			break;

		}

		const char *ptr = m_source.c_str();

		//ptr += m_pos;

		latest[0] = *(ptr + m_pos);
		latest[1] = '\0';

		m_pos++;

		if(latest[0] == '\0')
		{

			break;

		}

		if(latest[0] == '\n' && !middleOfString && comment == false)
		{

			if(readCount > 0)
			{

			} else {

				

			}

			break;

		}

		if(latest[0] == '#' && readCount == 0)
		{

			comment = true;

		}

		if(latest[0] == '\"')
		{

			middleOfString = !middleOfString;

		}

		if(latest[0] != ' ' && latest[0] != '\n')
		{
			
			if(!comment)
			{

				m_buffer.append(latest);

				readCount++;

			}

		}

		if(latest[0] == ' ' && middleOfString)
		{

			if(!comment)
			{

				m_buffer.append(latest);

				readCount++;

			}

		}
		
		if(comment && latest[0] == '\n')
		{
		
			comment = false;

		}

	}

	delete latest;

	return m_buffer;

}

float ConfigParser::readFloat(string var, float dflt)
{

	string buffer;
	string left;
	string right;

	int dir = 0;

	bool isString = false;

	bool reachedEnd = false;

	char *tempchr = new char[2];

	removeBlanks(&var);

	for(int i = 0; i < var.length(); i++)
	{

		var[i] = tolower(var[i]);

	}

	m_pos = 0;

	buffer = parseLine();

	while(!reachedEnd)
	{
		
		if(m_pos > m_source.size() - 1)
		{

			reachedEnd = true;

		}

		for(int i = 0; i < buffer.length(); ++i)
		{

			if(dir == 0)
			{

				if(buffer[i] != '=')
				{
				
					tempchr[0] = buffer[i];
					tempchr[1] = '\0';

					left.append(tempchr);


				} else {

					dir = 1;

				}

			} else if(dir == 1)
			{
				
				if(buffer[i] != '\"')
				{
				
					tempchr[0] = buffer[i];
					tempchr[1] = '\0';

					right.append(tempchr);

				} else {

					isString = true;

				}

			}

		}

		if(!isString)
		{

			for(int j = 0; j < left.length(); ++j)
			{

				left[j] = tolower(left[j]);

			}

			if(strcmp(left.c_str(), var.c_str()) == 0)
			{

				float out = 0;

				if(parseFloat(right, &out))
				{

					delete tempchr;
			
					return out;

				}

			}

		}

		isString = false;

		left = "";
		right = "";

		dir = 0;

		buffer = parseLine();

	}

	delete tempchr;

	return dflt;

}

string ConfigParser::readString(string var, string dflt)
{

	string buffer;
	string left;
	string right;

	int dir = 0;

	bool isString = false;

	bool reachedEnd = false;

	char *tempchr = new char[2];

	removeBlanks(&var);

	for(int i = 0; i < var.length(); ++i)
	{

		var[i] = tolower(var[i]);

	}

	m_pos = 0;

	buffer = parseLine();

	while(!reachedEnd)
	{
		
		if(m_pos > m_source.size() - 1)
		{

			reachedEnd = true;

		}

		for(int i = 0; i < buffer.length(); ++i)
		{

			if(dir == 0)
			{

				if(buffer[i] != '=')
				{
				
					tempchr[0] = buffer[i];
					tempchr[1] = '\0';

					left.append(tempchr);


				} else {

					dir = 1;

				}

			} else if(dir == 1)
			{
				
				if(buffer[i] != '\"')
				{
				
					tempchr[0] = buffer[i];
					tempchr[1] = '\0';

					right.append(tempchr);

				} else {

					isString = true;

				}

			}

		}

		if(isString)
		{

			for(int j = 0; j < left.length(); ++j)
			{

				left[j] = tolower(left[j]);

			}

			if(strcmp(left.c_str(), var.c_str()) == 0)
			{

				delete tempchr;
			
				return right;

			}

		}

		isString = false;

		left = "";
		right = "";

		dir = 0;

		buffer = parseLine();

	}

	delete tempchr;

	return dflt;

}

long ConfigParser::readLong(string var, long dflt)
{

	string buffer;
	string left;
	string right;

	int dir = 0;

	bool isString = false;

	bool reachedEnd = false;

	char *tempchr = new char[2];

	removeBlanks(&var);

	for(int i = 0; i < var.length(); ++i)
	{

		var[i] = tolower(var[i]);

	}

	m_pos = 0;

	buffer = parseLine();

	while(!reachedEnd)
	{

		if(m_pos > m_source.size() - 1)
		{

			reachedEnd = true;

		}

		for(int i = 0; i < buffer.length(); ++i)
		{

			if(dir == 0)
			{

				if(buffer[i] != '=')
				{
				
					tempchr[0] = buffer[i];
					tempchr[1] = '\0';

					left.append(tempchr);


				} else {

					dir = 1;

				}

			} else if(dir == 1)
			{
				
				if(buffer[i] != '\"')
				{
				
					tempchr[0] = buffer[i];
					tempchr[1] = '\0';

					right.append(tempchr);

				} else {

					isString = true;

				}

			}

		}

		if(!isString)
		{

			for(int j = 0; j < left.length(); j++)
			{

				left[j] = tolower(left[j]);

			}

			if(strcmp(left.c_str(), var.c_str()) == 0)
			{

				long out = 0;

				if(parseLong(right, &out))
				{

					delete tempchr;
			
					return out;

				}

			}

		}

		isString = false;

		left = "";
		right = "";

		dir = 0;

		buffer = parseLine();

	}

	delete tempchr;

	return dflt;

}

bool ConfigParser::parseFloat(string str, float *out)
{

	bool dec = false;
	float *f = out;
	int afterdec = 0;

	for(int i = 0; i < str.length(); i++)
	{

		if(str[i] == '.')
		{

			if(dec)
			{

				return false;

			}

			dec = true;

		} else {

			if(str[i] == '0' || str[i] == '1' || str[i] == '2' || str[i] == '3' || str[i] == '4' || str[i] == '5' || str[i] == '6' || str[i] == '7' || str[i] == '8' || str[i] == '9')
			{

				int j = 0;

				switch(str[i])
				{

				case '1':
					{

						j = 1;
					
						break;

					}
				case '2':
					{

						j = 2;
					
						break;

					}
				case '3':
					{

						j = 3;
					
						break;

					}
				case '4':
					{

						j = 4;
					
						break;

					}
				case '5':
					{

						j = 5;
					
						break;

					}
				case '6':
					{

						j = 6;
					
						break;

					}
				case '7':
					{

						j = 7;
					
						break;

					}
				case '8':
					{

						j = 8;
					
						break;

					}
				case '9':
					{

						j = 9;
					
						break;

					}
				case '0':
					{

						j = 0;
					
						break;

					}

				}

				if(dec)
				{

					afterdec++;

					*f += (j * (1.0f / (pow(10.0, (double)afterdec))));

				} else {

					*f *= 10;
				
					*f += (j);

				}

			}

		}

	}

	return true;

}

bool ConfigParser::parseLong(string str, long *out)
{

	bool dec = false;
	long *l = out;
	int afterdec = 0;

	for(int i = 0; i < str.length(); i++)
	{

		if(str[i] == '.')
		{

			return false;

		} else {

			if(str[i] == '0' || str[i] == '1' || str[i] == '2' || str[i] == '3' || str[i] == '4' || str[i] == '5' || str[i] == '6' || str[i] == '7' || str[i] == '8' || str[i] == '9')
			{

				int j = 0;

				switch(str[i])
				{

				case '1':
					{

						j = 1;
					
						break;

					}
				case '2':
					{

						j = 2;
					
						break;

					}
				case '3':
					{

						j = 3;
					
						break;

					}
				case '4':
					{

						j = 4;
					
						break;

					}
				case '5':
					{

						j = 5;
					
						break;

					}
				case '6':
					{

						j = 6;
					
						break;

					}
				case '7':
					{

						j = 7;
					
						break;

					}
				case '8':
					{

						j = 8;
					
						break;

					}
				case '9':
					{

						j = 9;
					
						break;

					}
				case '0':
					{

						j = 0;
					
						break;

					}

				}

				*l *= 10;
				
				*l += (j);

			}

		}

	}

	return true;

}
void ConfigParser::removeBlanks(string *str)
{

	string tmpstr = "";

	string tmp = *str;

	char *latest = new char[2];

	for(int i = 0; i < tmp.length(); i++)
	{

		if(tmp[i] != ' ')
		{

			latest[0] = tmp[i];
			latest[1] = '\0';

			tmpstr.append(latest);

		}

	}

	*str = tmpstr;

}
