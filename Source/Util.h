
/**
 *
 *	Util.h
 *
 *	This file contains definitions of the resource loading
 *	functions that takes a path and a filename.
 *
 *	Author:	Johan Öfverstedt
 *
 */

#ifndef _LOADUTIL_HEADER_
#define _LOADUTIL_HEADER_

extern SDL_Surface *loadImg(const char *, const char *);

extern BFont_Info *loadFont(const char *, const char *);

extern FSOUND_SAMPLE *loadSound(const char *, const char *);

#endif