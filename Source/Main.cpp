
/**
 *
 *	Main.cpp
 *
 *	This file contains the entry point of the game
 *	and it's here that the TetrisEngine objects, and
 *	all global variables are declared.
 *
 *	Author:	Johan Öfverstedt
 *
 */

//Basic Input/Output header:
#include <iostream>

//Game headers:
#include "Main.h"
#include "Menu.h"
#include "Gameplay.h"

//Config parser header:
#include "ConfigParser.h"

void configure();
void cleanUp();
void freeSurfaces();
void gameLoop();
void outputConfiguration();

/**
 *
 *	Global variable g_keys
 *
 *	Array of keystates, that contains
 *	the current keyboard status.
 *
 */

bool g_keys[512];

/**
 *
 *	Global variable g_screen
 *
 *	Pointer to the screen surface
 *	provided by SDL.
 *
 */

SDL_Surface *g_screen = 0;

/**
 *
 *	Global variable g_gameBGR
 *
 *	Pointer to the game background surface.
 *
 */

SDL_Surface *g_gameBGR = 0;

/**
 *
 *	Global variable g_gameIcon
 *
 *	Pointer to the game icon surface.
 *
 */

SDL_Surface *g_gameIcon = 0;

/**
 *
 *	Global variable g_advBar
 *
 *	Pointer to the advantage bar surface.
 *
 */

SDL_Surface *g_advBar = 0;

/**
 *
 *	Global variable g_screenWidth
 *
 *	The game window's width in pixels.
 *
 */

long g_screenWidth;

/**
 *
 *	Global variable g_screenHeight
 *
 *	The game window's height in pixels.
 *
 */

long g_screenHeight;

/**
 *
 *	Global variable g_inGame
 *
 *	Flag set to true, if the game is
 *	not in the menu.
 *
 */

bool g_inGame = false;

/**
 *
 *	Global variable g_quitGame
 *
 *	Flag set to true by any function when
 *	the game wishes to be exited.
 *
 */

bool g_quitGame = false;

/**
 *
 *	Global variable g_players
 *
 *	The number of players currently
 *	playing.
 *
 */

long g_players = 1;

/**
 *
 *	Variable drawError
 *
 *	Flag that makes sure, drawing errors
 *	are reported only once.
 *
 */

bool drawError = false;

/**
 *
 *	Variable playerEngine1
 *
 *	Pointer to a gameplay-handling object
 *	of type TetrisEngine.
 *	Handles player 1.
 *
 */

TetrisEngine *playerEngine1 = 0;

/**
 *
 *	Variable playerEngine2
 *
 *	Pointer to a gameplay-handling object
 *	of type TetrisEngine.
 *	Handles player 2.
 *
 */

TetrisEngine *playerEngine2 = 0;

/**
 *
 *	Variable g_soundEnabled
 *
 *	Flag that controls if any sound effects
 *	are to be played.
 *
 */

bool g_soundEnabled = true;

/**
 *
 *	Variable g_musicEnabled
 *
 *	Flag that controls if the background music
 *	is to be played.
 *
 */

bool g_musicEnabled = true;

/**
 *
 *	Variable g_musicChannel
 *
 *	The channel number that the music is
 *	playing on.
 *
 */

long g_musicChannel = 0;

/**
 *
 *	Variable g_backgroundMusic
 *
 *	Pointer to a sound-clip
 *	of type FSOUND_SAMPLE.
 *
 */

FSOUND_SAMPLE *g_backgroundMusic = 0;

#ifdef _DEBUG
#define WRITEDEBUGMACRO() writeLog("This is a debug version of the game!\n");
#else
#define WRITEDEBUGMACRO() ;
#endif

#ifdef WIN32
#include "Windows.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{

	main(0, 0);

	return 0;

}

#endif

/**
 *
 *	Function main
 *
 *	Entry point of the appliction and the
 *	function that initilizes and manages the
 *	whole application.
 *
 */

int main(int argc, char **argv)
{

	setLogFile("../Output.txt");

	clearLog();

	configure();

	WRITEDEBUGMACRO();

	//Initilize SDL:
	SDL_Init(SDL_INIT_VIDEO);

	//Initilize FMod:
	FSOUND_Init(44100, 32, 0);

	atexit(cleanUp);

	if(!g_gameIcon)
		g_gameIcon = loadImg(GFX_PATH, "gameicon.png");

	if(!g_gameIcon)
	{

		writeLog("Loading of the game icon failed.\n");

		g_quitGame = true;

		return 0;

	}

	SDL_WM_SetIcon(g_gameIcon, 0);

	g_screenWidth = 800;
	g_screenHeight = 600;

	if(SDL_VideoModeOK(g_screenWidth, g_screenHeight, 32, SDL_DOUBLEBUF | SDL_HWSURFACE | SDL_ANYFORMAT) == 0)
	{

		writeLog("Hardware rendering not supported, software rendering used.\n");

		g_screen = SDL_SetVideoMode(g_screenWidth, g_screenHeight, 32, SDL_DOUBLEBUF | SDL_SWSURFACE | SDL_ANYFORMAT);

	} else {

		g_screen = SDL_SetVideoMode(g_screenWidth, g_screenHeight, 32, SDL_DOUBLEBUF | SDL_HWSURFACE | SDL_ANYFORMAT);

	}

	if(!g_screen)
	{

		writeLog("SDL initiated unsuccessfully. \n");

		freeSurfaces();

		return 0;

	}

	SDL_WM_SetCaption("Swift blocks", 0);

	if(!g_gameBGR)
		g_gameBGR = loadImg(GFX_PATH, "gamebgr.jpg");

	if(!g_gameBGR)
	{

		writeLog("Loading of the game background failed.\n");

		g_quitGame = true;

		return 0;

	}

	if(!g_advBar)
		g_advBar = loadImg(GFX_PATH, "advbar.png");

	if(!g_advBar)
	{

		writeLog("Loading of the advantage bar failed.\n");

		g_quitGame = true;

		return 0;

	}

	g_backgroundMusic = loadSound(SND_PATH, "Music.ogg");

	if(!g_backgroundMusic)
	{

		writeLog("Loading of the background music failed.\n");

		destroyMenu();

		freeSurfaces();

		g_quitGame = true;

		return 0;

	}
	
	if(g_musicEnabled)
	{
	
		FSOUND_SetLoopMode(g_musicChannel = FSOUND_PlaySound(FSOUND_FREE, g_backgroundMusic), FSOUND_LOOP_NORMAL);

	}

	if(!loadMenu())
	{

		writeLog("Loading of the menu failed.\n");

		destroyMenu();

		freeSurfaces();

		g_quitGame = true;

		return 0;

	}

	playerEngine1 = new TetrisEngine(420, 120);
	playerEngine2 = new TetrisEngine(50, 120);

	playerEngine1->setScreen(g_screen);
	playerEngine2->setScreen(g_screen);

	playerEngine2->setKeyConfig(LeftKey, SDLK_a);
	playerEngine2->setKeyConfig(RightKey, SDLK_d);
	playerEngine2->setKeyConfig(RotateKey, SDLK_w);
	playerEngine2->setKeyConfig(DownKey, SDLK_s);

	playerEngine1->setCountScore(true);
	playerEngine2->setCountScore(true);

	playerEngine1->setSoundEnabled(g_soundEnabled);
	playerEngine2->setSoundEnabled(g_soundEnabled);

	if(!playerEngine1->loadGame())
	{

		writeLog("Loading of the game failed.\n");

		destroyMenu();

		freeSurfaces();

		playerEngine1->destroyGame();

		g_quitGame = true;

		return 0;

	}

	if(!playerEngine2->loadGame())
	{

		writeLog("Loading of the game failed.\n");

		destroyMenu();

		freeSurfaces();

		playerEngine1->destroyGame();

		playerEngine2->destroyGame();

		g_quitGame = true;

		return 0;

	}

	while(!g_quitGame)
	{

		while(!g_inGame && !g_quitGame)
		{
		
			menuLoop();

		}

		playerEngine1->resetGame();
		playerEngine2->resetGame();

		playerEngine1->setSoundEnabled(g_soundEnabled);
		playerEngine2->setSoundEnabled(g_soundEnabled);

		if(SDL_BlitSurface(g_gameBGR, 0, g_screen, 0) < 0)
		{
	
			if(!drawError)
			{

				writeLog("Failed to draw game background.\n");

			}

			drawError = true;

		}

		if(g_players == 1)
		{

			playerEngine1->setX(250);
			playerEngine1->setY(120);
			playerEngine2->setX(50);
			playerEngine2->setY(120);

		} 
		else if(g_players == 2)
		{

			playerEngine1->setX(420);
			playerEngine1->setY(120);
			playerEngine2->setX(50);
			playerEngine2->setY(120);

		}

		while(g_inGame && !g_quitGame)
		{

			if(g_players == 2)
			{

				SDL_Rect rect;
				long stepSize = 0;

				rect.x = 170;
				rect.y = 500;

				if(SDL_BlitSurface(g_advBar, 0, g_screen, &rect) < 0)
				{
	
					if(!drawError)
					{

						writeLog("Failed to draw advantage bar.\n");

					}

					drawError = true;

				}

				if(playerEngine1->getLevel() != 0 || playerEngine2->getLevel() != 0)
				{

					stepSize = (g_advBar->w - 10) / 14;
					
					if(playerEngine2->getLevel() != 0)
					{

						rect.x = 170 + 6 + (g_advBar->w - 12) * 0.5;
						rect.y = 500 + 6;

						rect.w = stepSize * playerEngine2->getLevel();

					} else {

						rect.x = 170 + 6 + ((g_advBar->w - 12) * 0.5) - (stepSize * playerEngine1->getLevel());
						rect.y = 500 + 6;

						rect.w = stepSize * playerEngine1->getLevel();

					}

					rect.h = g_advBar->h - 12;

					SDL_FillRect(g_screen, &rect, 0x000090);

				}

				rect.x = 170 + 6 + ((g_advBar->w - 12) * 0.5);
				rect.y = 500 + 6;
				rect.h = g_advBar->h - 12;
				rect.w = 1;

				SDL_FillRect(g_screen, &rect, 0xFFFFFF);

			}

			if(g_players == 1)
			{

				if(playerEngine1->getLinesErased() > 10)
				{

					playerEngine1->setLevel(1);

					if(playerEngine1->getLinesErased() > 20)
					{

						playerEngine1->setLevel(2);

					}

					if(playerEngine1->getLinesErased() > 40)
					{

						playerEngine1->setLevel(3);

					}

					if(playerEngine1->getLinesErased() > 60)
					{

						playerEngine1->setLevel(4);

					}

					if(playerEngine1->getLinesErased() > 80)
					{

						playerEngine1->setLevel(5);

					}

					if(playerEngine1->getLinesErased() > 110)
					{

						playerEngine1->setLevel(6);

					}

					if(playerEngine1->getLinesErased() > 140)
					{

						playerEngine1->setLevel(7);

					}

					char path[255];

					sprintf(path, "%sgamefield%d.jpg", GFX_PATH, playerEngine1->getLevel() + 1);

					playerEngine1->changeBGR(path);

				}

			} else if(g_players == 2) {

				long erased = 0;

				erased = playerEngine1->getLinesErased();

				if(erased > 10 && erased < 21)
				{

					char path[255];

					sprintf(path, "%sgamefield2.jpg", GFX_PATH);

					playerEngine1->changeBGR(path);

				}

				if(erased > 20 && erased < 41)
				{

					char path[255];

					sprintf(path, "%sgamefield3.jpg", GFX_PATH);

					playerEngine1->changeBGR(path);

				}

				if(erased > 40 && erased < 61)
				{

					char path[255];

					sprintf(path, "%sgamefield4.jpg", GFX_PATH);

					playerEngine1->changeBGR(path);

				}

				if(erased > 60 && erased < 81)
				{

					char path[255];

					sprintf(path, "%sgamefield5.jpg", GFX_PATH);

					playerEngine1->changeBGR(path);

				}

				if(erased > 80 && erased < 111)
				{

					char path[255];

					sprintf(path, "%sgamefield6.jpg", GFX_PATH);

					playerEngine1->changeBGR(path);

				}

				if(erased > 110 && erased < 141)
				{

					char path[255];

					sprintf(path, "%sgamefield7.jpg", GFX_PATH);

					playerEngine1->changeBGR(path);

				}

				if(erased > 140)
				{

					char path[255];

					sprintf(path, "%sgamefield8.jpg", GFX_PATH);

					playerEngine1->changeBGR(path);

				}

				erased = playerEngine2->getLinesErased();

				if(erased > 10 && erased < 21)
				{

					char path[255];

					sprintf(path, "%sgamefield2.jpg", GFX_PATH);

					playerEngine2->changeBGR(path);

				}

				if(erased > 20 && erased < 41)
				{

					char path[255];

					sprintf(path, "%sgamefield3.jpg", GFX_PATH);

					playerEngine2->changeBGR(path);

				}

				if(erased > 40 && erased < 61)
				{

					char path[255];

					sprintf(path, "%sgamefield4.jpg", GFX_PATH);

					playerEngine2->changeBGR(path);

				}

				if(erased > 60 && erased < 81)
				{

					char path[255];

					sprintf(path, "%sgamefield5.jpg", GFX_PATH);

					playerEngine2->changeBGR(path);

				}

				if(erased > 80 && erased < 111)
				{

					char path[255];

					sprintf(path, "%sgamefield6.jpg", GFX_PATH);

					playerEngine2->changeBGR(path);

				}

				if(erased > 110 && erased < 141)
				{

					char path[255];

					sprintf(path, "%sgamefield7.jpg", GFX_PATH);

					playerEngine2->changeBGR(path);

				}

				if(erased > 140)
				{

					char path[255];

					sprintf(path, "%sgamefield8.jpg", GFX_PATH);

					playerEngine2->changeBGR(path);

				}				

				if(playerEngine1->getLinesErased() == playerEngine2->getLinesErased())
				{
				
					playerEngine1->setLevel(0);
					playerEngine2->setLevel(0);

				}
				else if(playerEngine1->getLinesErased() > playerEngine2->getLinesErased())
				{

					long delta = (playerEngine1->getLinesErased() - playerEngine2->getLinesErased());

					if(delta < 2)
					{

						playerEngine1->setLevel(0);
						playerEngine2->setLevel(0);

					}

					if(delta >= 2)
					{

						playerEngine1->setLevel(0);
						playerEngine2->setLevel(1);

					}

					if(delta >= 4)
					{

						playerEngine1->setLevel(0);
						playerEngine2->setLevel(2);

					}

					if(delta >= 6)
					{

						playerEngine1->setLevel(0);
						playerEngine2->setLevel(3);

					}

					if(delta >= 8)
					{

						playerEngine1->setLevel(0);
						playerEngine2->setLevel(4);

					}

					if(delta >= 10)
					{

						playerEngine1->setLevel(0);
						playerEngine2->setLevel(5);

					}

					if(delta >= 12)
					{

						playerEngine1->setLevel(0);
						playerEngine2->setLevel(6);

					}

					if(delta >= 14)
					{

						playerEngine1->setLevel(0);
						playerEngine2->setLevel(7);

					}

				}
				else
				{

					long delta = (playerEngine2->getLinesErased() - playerEngine1->getLinesErased());

					if(delta < 2)
					{

						playerEngine1->setLevel(0);
						playerEngine2->setLevel(0);

					}

					if(delta >= 2)
					{

						playerEngine2->setLevel(0);
						playerEngine1->setLevel(1);

					}

					if(delta >= 4)
					{

						playerEngine2->setLevel(0);
						playerEngine1->setLevel(2);

					}

					if(delta >= 6)
					{

						playerEngine2->setLevel(0);
						playerEngine1->setLevel(3);

					}

					if(delta >= 8)
					{

						playerEngine2->setLevel(0);
						playerEngine1->setLevel(4);

					}

					if(delta >= 10)
					{

						playerEngine2->setLevel(0);
						playerEngine1->setLevel(5);

					}

					if(delta >= 12)
					{

						playerEngine2->setLevel(0);
						playerEngine1->setLevel(6);

					}

					if(delta >= 14)
					{

						playerEngine2->setLevel(0);
						playerEngine1->setLevel(7);

					}

				}

			}

			gameLoop();

			if(playerEngine1->getGameOver())
			{

				playerEngine2->setWinner(true);

			} else if(playerEngine2->getGameOver())
			{

				playerEngine1->setWinner(true);

			}

		}

	}

	destroyMenu();

	freeSurfaces();

	playerEngine1->destroyGame();
	playerEngine2->destroyGame();

	if(playerEngine1)
	{
		
		delete playerEngine1;

		playerEngine1 = 0;

	}

	if(playerEngine2)
	{
		
		delete playerEngine2;

		playerEngine2 = 0;

	}

	return 0;

}

/**
 *
 *	Function configure
 *
 *	Loads the configuration file and
 *	changes the game according to it.
 *
 */

void configure()
{

	ConfigParser p;

	if(!p.loadFile(CONFIG_FILE))
	{

		writeLog("No configuration file present.\n");

		return;

	}

	if(p.readLong("sound", 0) == 1)
	{

		g_soundEnabled = true;

	} else {

		g_soundEnabled = false;

	}

	if(p.readLong("music", 0) == 1)
	{

		g_musicEnabled = true;

	} else {

		g_musicEnabled = false;

	}

}

/**
 *
 *	Function cleanUp
 *
 *	Callback function that is called when the
 *	application is terminated for any reason.
 *
 */

void cleanUp()
{

	if(playerEngine1)
	{
		
		delete playerEngine1;

		playerEngine1 = 0;

	}

	if(playerEngine2)
	{
		
		delete playerEngine2;

		playerEngine2 = 0;

	}

	if(g_backgroundMusic)
	{
		
		FSOUND_Sample_Free(g_backgroundMusic);
		
		g_backgroundMusic = 0;

	}

	
	SDL_Quit();

}

/**
 *
 *	Function gameLoop
 *
 *	Handles event handling during gameplay, 
 *	updates the game status, and flips the screen.
 *
 */

void gameLoop()
{

	SDL_Event e;
	
	while(SDL_PollEvent(&e)) {
	
		if(e.type == SDL_QUIT)
		{

			g_inGame = false;
			
			g_quitGame = true;

			return;

		}

		if(e.type == SDL_KEYDOWN)
		{

			if(e.key.keysym.sym == SDLK_ESCAPE)
			{

				g_inGame = false;

			}

			g_keys[e.key.keysym.sym] = true;

			if(g_keys[SDLK_p])
			{

				playerEngine1->setPauseState(!playerEngine1->getPauseState());

				if(g_players > 1)
				{

					playerEngine2->setPauseState(!playerEngine2->getPauseState());
					

				}

				g_keys[SDLK_g] = false;

			}

		}

		if(e.type == SDL_KEYUP)
		{

			g_keys[e.key.keysym.sym] = false;

		}
		
	};

	if(g_players > 0)
		playerEngine1->updateGame();
	if(g_players > 1)
		playerEngine2->updateGame();

	if(g_players > 0)
	{

		if(!playerEngine1->drawGame())
		{

			if(!drawError)
			{

				writeLog("Failed to draw game.\n");

			}

			drawError = true;

		}

	}

	if(g_players > 1)
	{

		if(!playerEngine2->drawGame())
		{

			if(!drawError)
			{

				writeLog("Failed to draw game.\n");

			}

			drawError = true;

		}

	}

	if(SDL_Flip(g_screen) < 0)
	{
		
		if(!drawError)
		{

			writeLog("Failed to flip buffers.\n");

		}

		drawError = true;

	}


}

/**
 *
 *	Function freeSurfaces
 *
 *	Frees all the SDL surfaces loaded
 *	during the duration of the game from
 *	this file.
 *
 */

void freeSurfaces()
{

	if(g_gameIcon)
	{

		SDL_FreeSurface(g_gameIcon);

		g_gameIcon = 0;

	}

	if(g_gameBGR)
	{

		SDL_FreeSurface(g_gameBGR);

		g_gameBGR = 0;

	}

	if(g_advBar)
	{

		SDL_FreeSurface(g_advBar);

		g_advBar = 0;

	}

}

void outputConfiguration()
{

	FILE *f = fopen(CONFIG_FILE, "w");

	if(!f)
		return;

	fprintf(f, "#Config file for Swift blocks.\n\n");
	fprintf(f, "#Sound status (1 = on, 0 = off):\n");
	
	if(g_soundEnabled)
	{

		fprintf(f, "Sound = 1;\n\n");

	} else {

		fprintf(f, "Sound = 0;\n\n");

	}

	fprintf(f, "#Music status (1 = on, 0 = off):\n");
	
	if(g_musicEnabled)
	{

		fprintf(f, "Music = 1;");

	} else {

		fprintf(f, "Music = 0;");

	}

}