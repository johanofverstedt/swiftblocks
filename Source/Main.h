
/**
 *
 *	Main.h
 *
 *	This file contains some headers that the most of the
 *	game's files will use.
 *	Also contains external definitions of the global
 *	variables that is defined in Main.cpp.
 *
 *	Author:	Johan Öfverstedt
 *
 */

#ifndef MAIN_H
#define MAIN_H

#ifndef GFX_PATH

/**
 *
 *	Definition GFX_PATH
 *
 *	Controls the subpath, the whole game
 *	is going to use, to access the graphics.
 *
 */

#define GFX_PATH "../Resources/Graphics/"

#endif

#ifndef SND_PATH

/**
 *
 *	Definition SND_PATH
 *
 *	Controls the subpath, the whole game
 *	is going to use, to access the sound.
 *
 */

#define SND_PATH "../Resources/Sound/"

#endif

#ifndef CONFIG_FILE

/**
 *
 *	Definition CONFIG_FILE
 *
 *	Controls the location of the config file
 *	the game saves the settings in.
 *
 */

#define CONFIG_FILE "../Config.cfg"

#endif

//SDL header:
#include "SDL.h"

//SDL_Image header:
#include "SDL_image.h"

//FMod header:
#include "fmod.h"

//BFont header:
#include "../BFont/BFont.h"

//Load util:
#include "Util.h"

//Log management header:
#include "Logfile.h"

using namespace LogFile;

/**
 *
 *	Global variable g_keys
 *
 *	Array of keystates, that contains
 *	the current keyboard status.
 *
 */

extern bool g_keys[512];

/**
 *
 *	Global variable g_screen
 *
 *	Pointer to the screen surface
 *	provided by SDL.
 *
 */

extern SDL_Surface *g_screen;

/**
 *
 *	Global variable g_gameBGR
 *
 *	Pointer to the game background surface.
 *
 */

extern SDL_Surface *g_gameBGR;

/**
 *
 *	Global variable g_gameIcon
 *
 *	Pointer to the game icon surface.
 *
 */

extern SDL_Surface *g_gameIcon;

/**
 *
 *	Global variable g_advBar
 *
 *	Pointer to the advantage bar surface.
 *
 */

extern SDL_Surface *g_advBar;

/**
 *
 *	Global variable g_screenWidth
 *
 *	The game window's width in pixels.
 *
 */

extern long g_screenWidth;

/**
 *
 *	Global variable g_screenHeight
 *
 *	The game window's height in pixels.
 *
 */

extern long g_screenHeight;

/**
 *
 *	Global variable g_inGame
 *
 *	Flag set to true, if the game is
 *	not in the menu.
 *
 */

extern bool g_inGame;

/**
 *
 *	Global variable g_quitGame
 *
 *	Flag set to true by any function when
 *	the game wishes to be exited.
 *
 */

extern bool g_quitGame;

/**
 *
 *	Global variable g_players
 *
 *	The number of players currently
 *	playing.
 *
 */

extern long g_players;

/**
 *
 *	Variable g_soundEnabled
 *
 *	Flag that controls if any sound effects
 *	are to be played.
 *
 */

extern bool g_soundEnabled;

/**
 *
 *	Variable g_musicEnabled
 *
 *	Flag that controls if the background music
 *	is to be played.
 *
 */

extern bool g_musicEnabled;

/**
 *
 *	Variable g_musicChannel
 *
 *	The channel number that the music is
 *	playing on.
 *
 */

extern long g_musicChannel;

/**
 *
 *	Variable g_backgroundMusic
 *
 *	Pointer to a sound-clip
 *	of type FSOUND_SAMPLE.
 *
 */

extern FSOUND_SAMPLE *g_backgroundMusic;

extern void outputConfiguration();

#endif