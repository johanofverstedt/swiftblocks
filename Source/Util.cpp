
/**
 *
 *	Util.cpp
 *
 *	This file contains the resource loading
 *	functions that takes a path and a filename.
 *
 *	Author:	Johan Öfverstedt
 *
 */

//Basic Input/Output:
#include "stdio.h"
#include "string.h"

//Game headers:
#include "Main.h"

/**
 *
 *	Function loadImg
 *
 *	Takes a path and a file name,
 *	and loads an image file using
 *	the SDL_image library.
 *
 */

SDL_Surface *loadImg(const char *path, const char *file)
{

	char tmpPath[1024];
	
	sprintf(tmpPath, path);
	
	strcat(tmpPath, file);

	return IMG_Load(tmpPath);

}

/**
 *
 *	Function loadFont
 *
 *	Takes a path and a file name,
 *	and loads a font file using
 *	the BFont library.
 *
 */

BFont_Info *loadFont(const char *path, const char *file)
{

	char tmpPath[1024];
	
	sprintf(tmpPath, path);
	
	strcat(tmpPath, file);

	return LoadFont(tmpPath);

}

/**
 *
 *	Function loadSound
 *
 *	Takes a path and a file name,
 *	and loads a sound file using
 *	the FMod library.
 *
 */

FSOUND_SAMPLE *loadSound(const char *path, const char *file)
{

	char tmpPath[1024];
	
	sprintf(tmpPath, path);
	
	strcat(tmpPath, file);

	return FSOUND_Sample_Load(FSOUND_FREE, tmpPath, 0, 0);

}