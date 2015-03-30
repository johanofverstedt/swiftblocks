
/**
 *
 *	Gameplay.cpp
 *
 *	This file contains the implementation of the TetrisEngine class
 *	that handles the gameplay.
 *
 *	Author:	Johan Öfverstedt
 *
 */

//Basic Input/Output header:
#include <iostream>

//Time header:
#include "time.h"

//Game headers:
#include "Main.h"
#include "Blocks.h"
#include "Gameplay.h"

/**
 *
 *	Constructor TetrisEngine::TetrisEngine()
 *
 *	Initilizes the TetrisEngine object and
 *	resets all values, prepares it for use.
 *
 */

TetrisEngine::TetrisEngine(long xpos, long ypos)
{

	m_x = xpos;
	m_y = ypos;

	m_screen = 0;
	m_gameField = 0;
	m_scoreBoard = 0;

	m_blocks[0] = 0;
	m_blocks[1] = 0;
	m_blocks[2] = 0;
	m_blocks[3] = 0;
	m_blocks[4] = 0;
	m_blocks[5] = 0;

	m_levelUpSound = 0;
	m_lineRemoveSound = 0;
	m_gameOverSound = 0;

	m_scoreFont = 0;

	m_bgr = new char[255];

	m_linesToRemoveCount = 0;

	m_level = 0;
	m_linesErased = 0;

	m_countScore = false;		
	m_score = 0;

	m_smoothFactorX = 0.0;
	m_smoothFactorY = 0.0;
	m_smoothFactorFade = 0.0;

	m_deltaX = 0;
	m_deltaY = 0;

	m_gameOver = false;
	m_winner = false;
	m_pause = false;
	m_bindNext = false;

	m_soundEnabled = false;

	setKeyConfig(RotateKey, SDLK_UP);
	setKeyConfig(LeftKey, SDLK_LEFT);
	setKeyConfig(RightKey, SDLK_RIGHT);
	setKeyConfig(DownKey, SDLK_DOWN);

	m_removing = false;

	m_startTime = 0;

}

/**
 *
 *	Destructor TetrisEngine::~TetrisEngine()
 *
 *	Resets all values and deallocates all allocated
 *	memory.
 *
 */

TetrisEngine::~TetrisEngine()
{

	delete m_bgr;
	m_bgr = 0;

	m_linesToRemoveCount = 0;

	m_level = 0;
	m_linesErased = 0;

	m_countScore = false;		
	m_score = 0;

	m_smoothFactorX = 0.0;
	m_smoothFactorY = 0.0;
	m_smoothFactorFade = 0.0;

	m_deltaX = 0;
	m_deltaY = 0;

	m_removing = false;

	m_pause = false;
	m_bindNext = false;

	m_startTime = 0;

}

/**
 *
 *	Function TetrisEngine::bindToGrid()
 *
 *	Adds the current gameBlock to the grid,
 *	of static blocks. It does also prepares
 *	the next block.
 *
 */

void TetrisEngine::bindToGrid(Block *b)
{

	long currentIndex = 0;

	for(long i = 0; i < 4; ++i)
	{

		for(long j = 0; j < 4; ++j)
		{

			currentIndex = (j * 4) + i;

			if(m_gameBlock.getY() + j > -1)
			{

				if(m_gameBlock.getShape()[currentIndex] != 0)
				{

					m_grid[m_gameBlock.getX() + i][m_gameBlock.getY() + j] = m_gameBlock.getShape()[currentIndex];
					
				}
					
			}

		}

	}

	m_gameBlock.clear();

	m_gameBlock = m_nextBlock;
	m_nextBlock.createRandomBlock();

	m_gameBlock.setX(2);
	m_gameBlock.setY(-4);

}

/**
 *
 *	Function TetrisEngine::blockCollision()
 *
 *	Checks if the specified block collides with any block
 *	in the grid, if moved the full spaces spcified with the
 *	deltaX and deltaY parameters.
 *
 */

CollisionState TetrisEngine::blockCollision(Block *b, long deltaX, long deltaY)
{

	long i = 0;
	long j = 0;

	long currentIndex = 0;

	for(i = b->getX() + deltaX; i < b->getX() + deltaX + 4; ++i)
	{

		for(j = b->getY() + deltaY; j < b->getY() + deltaY + 4; ++j)
		{

			currentIndex = (i - b->getX() - deltaX) + ((j - b->getY() - deltaY) * 4);

			if(b->getShape()[currentIndex] != 0)
			{

				if(i < 0)
				{

					return LeftBorderCollision;

				}

				if(i > (GRID_COLS - 1))
				{

					return RightBorderCollision;

				}

				if(j > (GRID_ROWS - 1))
				{

					return DownCollision;

				}

				if(j > -1)
				{

					if(m_grid[i][j] != 0)
					{

						return BlockCollision;

					}

				}

			}

		}

	}

	return NoCollision;

}

/**
 *
 *	Function TetrisEngine::changeBGR()
 *
 *	Changes the current background into another
 *	from a file specified with the parameter
 *	newBGR.
 *
 *	TODO: Add fading of the background changes!
 *
 */

void TetrisEngine::changeBGR(const char *newBGR)
{

	if(strcmp(newBGR, m_bgr) == 0)
	{

		return;

	}

	if(m_gameField)
	{
	
		SDL_FreeSurface(m_gameField);
		m_gameField = 0;

	}

	if(!m_gameField)	
		m_gameField = loadImg("", newBGR);

	if(!m_gameField)
	{

		writeLog("Failed to load the game frame.\n");

		return;

	}

	if(m_soundEnabled)
		FSOUND_PlaySound(FSOUND_FREE, m_levelUpSound);

	sprintf(m_bgr, "%s", newBGR);

}

/**
 *
 *	Function TetrisEngine::destroyGame()
 *
 *	Frees all memory allocated by the class,
 *	and sets all game flags to default.
 *
 */

void TetrisEngine::destroyGame()
{

	if(m_blocks[0])
		SDL_FreeSurface(m_blocks[0]);
	
	if(m_blocks[1])
		SDL_FreeSurface(m_blocks[1]);
	
	if(m_blocks[2])
		SDL_FreeSurface(m_blocks[2]);
	
	if(m_blocks[3])
		SDL_FreeSurface(m_blocks[3]);
	
	if(m_blocks[4])
		SDL_FreeSurface(m_blocks[4]);
	
	if(m_blocks[5])
		SDL_FreeSurface(m_blocks[5]);

	if(m_scoreBoard)
	{

		SDL_FreeSurface(m_scoreBoard);
		m_scoreBoard = 0;

	}

	if(m_gameField)
	{
	
		SDL_FreeSurface(m_gameField);
		m_gameField = 0;

	}

	if(m_scoreFont)
	{

		FreeFont(m_scoreFont);

		m_scoreFont = 0;

	}

	if(m_levelUpSound)
	{
		
		FSOUND_Sample_Free(m_levelUpSound);
		
		m_levelUpSound = 0;

	}

	if(m_lineRemoveSound)
	{
		
		FSOUND_Sample_Free(m_lineRemoveSound);
		
		m_lineRemoveSound = 0;

	}

	if(m_gameOverSound)
	{
		
		FSOUND_Sample_Free(m_gameOverSound);
		
		m_gameOverSound = 0;

	}

}

/**
 *
 *	Function TetrisEngine::drawGame()
 *
 *	Takes care of all the drawing of the playfield
 *	that this instance of the class handles.
 *
 */

bool TetrisEngine::drawGame()
{

	m_fieldRect.x = m_x;
	m_fieldRect.y = m_y;

	SDL_SetAlpha(m_gameField, SDL_SRCALPHA, 255);
	
	if(SDL_BlitSurface(m_gameField, 0, m_screen, &m_fieldRect) < 0)
    {
		
		return false;

	}

	for(long i = 0; i < GRID_COLS; ++i)
	{

		for(long j = 0; j < GRID_ROWS; ++j)
		{

			if(m_grid[i][j] > 0)
			{

				m_blockRect.x = m_x + 5 + (i * m_blocks[m_grid[i][j] - 1]->w);
				m_blockRect.y = m_y + 6 + (j * m_blocks[m_grid[i][j] - 1]->h);
				m_blockRect.w = m_blocks[m_grid[i][j] - 1]->w;
				m_blockRect.h = m_blocks[m_grid[i][j] - 1]->h;

				if(m_linesToRemoveCount > 0)
				{

					if(m_linesToRemove[j] == true)
					{
					
						SDL_SetAlpha(m_blocks[m_grid[i][j] - 1], SDL_SRCALPHA, 164 - (164 * m_smoothFactorFade));

					} else {

						SDL_SetAlpha(m_blocks[m_grid[i][j] - 1], SDL_SRCALPHA, 164);

					}

				} else {
				
					SDL_SetAlpha(m_blocks[m_grid[i][j] - 1], SDL_SRCALPHA, 164);

				}

				if(SDL_BlitSurface(m_blocks[m_grid[i][j] - 1], 0, m_screen, &m_blockRect) < 0)
				{

					return false;

				}
				
			}

		}

	}

	{

		long currentIndex = 0;

		for(long i = 0; i < 4; ++i)
		{

			for(long j = 0; j < 4; ++j)
			{

				currentIndex = (j * 4) + i;

				if(m_gameBlock.getY() + j == -1)
				{

					SDL_Rect srcRect;

					srcRect.x = 0;
					srcRect.y = m_blocks[0]->h - (m_blocks[0]->h * m_smoothFactorY);
					srcRect.w = m_blocks[0]->w;
					srcRect.h = (m_blocks[0]->h * m_smoothFactorY) + 1;

					m_blockRect.x = m_x + 5 + ((m_gameBlock.getX() + i) * m_blocks[0]->w) + (long)(m_deltaX * m_smoothFactorX * 19);
					m_blockRect.y = m_y + 6 + ((m_gameBlock.getY() + j) * m_blocks[0]->h) + (long)(m_deltaY * m_smoothFactorY * 19) + m_blocks[0]->h - (m_blocks[0]->h * m_smoothFactorY);
					m_blockRect.w = m_blocks[0]->w;
					m_blockRect.h = (m_blocks[0]->h * m_smoothFactorY);

					SDL_SetAlpha(m_blocks[m_gameBlock.getShape()[currentIndex] - 1], SDL_SRCALPHA, 164);

					if(m_gameBlock.getShape()[currentIndex] != 0)
					{

						if(SDL_BlitSurface(m_blocks[m_gameBlock.getShape()[currentIndex] - 1], &srcRect, m_screen, &m_blockRect) < 0)
						{

							return false;

						}
					
					}
					
				}

				if(m_gameBlock.getY() + j > -1)
				{

					m_blockRect.x = m_x + 5 + ((m_gameBlock.getX() + i) * m_blocks[0]->w) + (long)(m_deltaX * m_smoothFactorX * 19);
					m_blockRect.y = m_y + 6 + ((m_gameBlock.getY() + j) * m_blocks[0]->h) + (long)(m_deltaY * m_smoothFactorY * 19);
					m_blockRect.w = m_blocks[0]->w;
					m_blockRect.h = m_blocks[0]->h;

					SDL_SetAlpha(m_blocks[m_gameBlock.getShape()[currentIndex] - 1], SDL_SRCALPHA, 164);

					if(m_gameBlock.getShape()[currentIndex] != 0)
					{

						if(SDL_BlitSurface(m_blocks[m_gameBlock.getShape()[currentIndex] - 1], 0, m_screen, &m_blockRect) < 0)
						{

							return false;

						}
					
					}
					
				}

			}

		}

	}

	m_scoreRect.x = m_fieldRect.x + m_fieldRect.w + 15;
	m_scoreRect.y = m_fieldRect.y;
	m_scoreRect.w = m_scoreBoard->w;
	m_scoreRect.h = m_scoreBoard->h;

	if(SDL_BlitSurface(m_scoreBoard, 0, m_screen, &m_scoreRect) < 0)
	{

		return false;

	}

	{

		char text[80];

		sprintf(text, "Lines:  %d", m_linesErased);

		PutStringFont(m_screen, m_scoreFont, m_fieldRect.x + m_fieldRect.w + 15 + 15, m_fieldRect.y + 15, text);

		if(m_countScore)
		{

			sprintf(text, "Score:  %d", m_score);

			PutStringFont(m_screen, m_scoreFont, m_fieldRect.x + m_fieldRect.w + 15 + 15, m_fieldRect.y + 15 + 30, text);
	
		}

		sprintf(text, "Next:");
		
		//sprintf(text, "FPS: %d", (long)((m_framesDrawn * 1000) / (m_timeElapsed + 1)));

		PutStringFont(m_screen, m_scoreFont, m_fieldRect.x + m_fieldRect.w + 15 + 15, m_fieldRect.y + 15 + 60, text);

		if(m_winner || m_gameOver)
		{

			PutStringFont(m_screen, m_scoreFont, 20, m_screen->h - 40, "Press escape to abort game!");

		}

		if(m_winner)
		{

			sprintf(text, "You win");

			PutStringFont(m_screen, m_scoreFont, m_fieldRect.x + 20 + 25, m_fieldRect.y + m_fieldRect.h / 2 - 15, text);

		}

		if(m_gameOver)
		{
		
			sprintf(text, "Game Over");

			PutStringFont(m_screen, m_scoreFont, m_fieldRect.x + 20 + 15, m_fieldRect.y + m_fieldRect.h / 2 - 15, text);

		}

	}

	{

		long currentIndex = 0;

		for(long i = 0; i < 4; ++i)
		{

			for(long j = 0; j < 4; ++j)
			{

				currentIndex = (j * 4) + i;

				m_blockRect.x = m_fieldRect.x + m_fieldRect.w + 15 + 15 + 50 + (i * m_blocks[0]->w);
				m_blockRect.y = m_fieldRect.y + 15 + 90 + (j * m_blocks[0]->h);
				m_blockRect.w = m_blocks[0]->w;
				m_blockRect.h = m_blocks[0]->h;

				SDL_SetAlpha(m_blocks[m_nextBlock.getShape()[currentIndex] - 1], SDL_SRCALPHA, 164);

				if(m_nextBlock.getShape()[currentIndex] != 0)
				{

					if(SDL_BlitSurface(m_blocks[m_nextBlock.getShape()[currentIndex] - 1], 0, m_screen, &m_blockRect) < 0)
					{

						return false;

					}
					
				}
					
			}

		}

	}

	return true;

}

/**
 *
 *	Function TetrisEngine::eliminateRows()
 *
 *	Tags any full row for removal so that the 
 *	function updateGame() can fade these
 *	and ultimatly, remove them.
 *
 */

void TetrisEngine::eliminateRows()
{

	for(long i = 0; i < GRID_ROWS; ++i)
	{

		long count = 0;

		for(long j = 0; j < GRID_COLS; ++j)
		{

			if(m_grid[j][i] > 0)
			{

				++count;

			}

			if(count == GRID_COLS)
			{

				m_smoothFactorY = 0;

				m_removing = true;

				m_linesToRemove[i] = true;

				++m_linesToRemoveCount;

			} else {

				m_linesToRemove[i] = false;

			}

		}

	}

	if(m_removing)
	{

		if(m_soundEnabled)
		{
			
			FSOUND_PlaySound(FSOUND_FREE, m_lineRemoveSound);

		}

	}

}

/**
 *
 *	Function TetrisEngine::getKeyConfig()
 *
 *	Retrieves the current key, that's set
 *	for one of the actions that are defined
 *	in the enumeration InputConfig.
 *
 */

long TetrisEngine::getKeyConfig(InputConfig ic)
{

	if(ic == RotateKey)
		return m_rotateKey;
	
	if(ic == LeftKey)
		return m_leftKey;
	
	if(ic == RightKey)
		return m_rightKey;
	
	if(ic == DownKey)
		return m_downKey;

	return 0;

}

/**
 *
 *	Function TetrisEngine::loadGame()
 *
 *	Loads all the resources needed and clears
 *	all important flags and values.
 *
 */

bool TetrisEngine::loadGame()
{

	long i = 0;

	sprintf(m_bgr, "gamefield1.jpg");

	if(!m_gameField)	
		m_gameField = loadImg(GFX_PATH, "gamefield1.jpg");

	if(!m_gameField)
	{

		writeLog("Failed to load the game frame.\n");

		return false;

	}

	if(!m_scoreBoard)	
		m_scoreBoard = loadImg(GFX_PATH, "scoreboard.png");

	if(!m_scoreBoard)
	{

		writeLog("Failed to load the score board.\n");
		
		return false;

	}

	if(!m_blocks[0])
		m_blocks[0] = loadImg(GFX_PATH, "redblock.png");
	if(!m_blocks[1])
		m_blocks[1] = loadImg(GFX_PATH, "blueblock.png");
	if(!m_blocks[2])
		m_blocks[2] = loadImg(GFX_PATH, "yellowblock.png");
	if(!m_blocks[3])
		m_blocks[3] = loadImg(GFX_PATH, "greenblock.png");
	if(!m_blocks[4])
		m_blocks[4] = loadImg(GFX_PATH, "pinkblock.png");
	if(!m_blocks[5])
		m_blocks[5] = loadImg(GFX_PATH, "orangeblock.png");

	for(i = 0; i < 6; ++i)
	{
	
		if(!m_blocks[i])
		{

			writeLog("Failed to load the block bitmaps.\n");

			return false;

		}

	}

	SDL_SetColorKey(m_blocks[0], SDL_SRCCOLORKEY, 0xFFFFFF);
	SDL_SetColorKey(m_blocks[1], SDL_SRCCOLORKEY, 0xFFFFFF);
	SDL_SetColorKey(m_blocks[2], SDL_SRCCOLORKEY, 0xFFFFFF);
	SDL_SetColorKey(m_blocks[3], SDL_SRCCOLORKEY, 0xFFFFFF);
	SDL_SetColorKey(m_blocks[4], SDL_SRCCOLORKEY, 0xFFFFFF);
	SDL_SetColorKey(m_blocks[5], SDL_SRCCOLORKEY, 0xFFFFFF);

	m_fieldRect.x = m_x;
	m_fieldRect.y = m_y;
	m_fieldRect.w = m_blocks[0]->w * GRID_COLS + 10;
	m_fieldRect.h = m_blocks[0]->h * GRID_ROWS + 10;

	m_gameBlock.createRandomBlock();
	m_nextBlock.createRandomBlock();

	m_gameBlock.setX(2);
	m_gameBlock.setY(-4);
	
	for(i = 0; i < GRID_COLS; ++i)
	{

		for(long j = 0; j < GRID_ROWS; ++j)
		{

			m_grid[i][j] = 0;

		}

	}

	if(!m_scoreFont)
		m_scoreFont = loadFont(GFX_PATH, "topaz.png");

	if(!m_scoreFont)
	{

		writeLog("Failed to load the font.\n");

		return false;

	}

	if(!m_levelUpSound)
		m_levelUpSound = loadSound(SND_PATH, "Levelup.ogg");

	if(!m_levelUpSound)
	{

		writeLog("Failed to load the level up sound.\n");

		return false;

	}

	if(!m_lineRemoveSound)
		m_lineRemoveSound = loadSound(SND_PATH, "Blipp.ogg");

	if(!m_lineRemoveSound)
	{

		writeLog("Failed to load the line removal sound.\n");

		return false;

	}

	if(!m_gameOverSound)
		m_gameOverSound = loadSound(SND_PATH, "Gameover.ogg");

	if(!m_gameOverSound)
	{

		writeLog("Failed to load the line removal sound.\n");

		return false;

	}

	resetGame();	

	m_startTime = SDL_GetTicks();

	return true;

}

/**
 *
 *	Function TetrisEngine::resetGame()
 *
 *	Clears all flags and values and makes the game
 *	ready to restart.
 *
 */

void TetrisEngine::resetGame()
{

	sprintf(m_bgr, "%s", "gamefield1.jpg");

	if(m_gameField)
	{
	
		SDL_FreeSurface(m_gameField);
		m_gameField = 0;

	}

	if(!m_gameField)	
		m_gameField = loadImg(GFX_PATH, m_bgr);

	if(!m_gameField)
	{

		writeLog("Failed to load the game frame.\n");

		return;

	}

	m_gameBlock.createRandomBlock();

	m_gameBlock.setX(2);
	m_gameBlock.setY(-4);
	
	for(long i = 0; i < GRID_COLS; ++i)
	{

		for(long j = 0; j < GRID_ROWS; ++j)
		{

			m_grid[i][j] = NO_BLOCK;

		}

	}

	m_deltaY = 1;
	m_deltaX = 0;

	m_gameOver = false;
	m_pause = false;
	m_winner = false;

	m_level = 0;
	m_linesErased = 0;
	m_score = 0;

	m_startTime = SDL_GetTicks();

}

/**
 *
 *	Function TetrisEngine::setLevel()
 *
 *	Sets the current level of the game.
 *	Used by the outside gameloop to manage
 *	which background to display, and internaly
 *	to determine which speed to move the
 *	m_gameBlock with.
 *
 */

void TetrisEngine::setLevel(long newLevel)
{
	
	if(newLevel >= 0 && newLevel < MAX_LEVELS)
	{
		
		m_level = newLevel;

	}

}

/**
 *
 *	Function TetrisEngine::setKeyConfig()
 *
 *	Sets the key, that's to perform
 *	one of the actions that are defined
 *	in the enumeration InputConfig.
 *
 */

void TetrisEngine::setKeyConfig(InputConfig ic, long newKey)
{

	if(ic == RotateKey)
		m_rotateKey = newKey;
	
	if(ic == LeftKey)
		m_leftKey = newKey;
	
	if(ic == RightKey)
		m_rightKey = newKey;
	
	if(ic == DownKey)
		m_downKey = newKey;

}

/**
 *
 *	Function TetrisEngine::updateGame()
 *
 *	Handles all every-frame chores such as
 *	updating block position, collision detection,
 *	fading values and more.
 *	Currently uses the global key array declared
 *	in TetrisClone.h, might want to replace it
 *	with something that is more OO.
 *
 */

void TetrisEngine::updateGame()
{

	CollisionState cs = NoCollision;

	long timeElapsed = 0;

	if(!m_removing)
		eliminateRows();

	if(g_keys[m_leftKey] && !g_keys[m_rotateKey] && !m_pause)
	{

		g_keys[m_leftKey] = false;

		cs = blockCollision(&m_gameBlock, -1, m_deltaY);

		if(cs == NoCollision)
		{
				
			if(m_deltaX == 0)
				m_deltaX = -1;

		}

	}

	if(g_keys[m_rightKey] && !g_keys[m_rotateKey] && !m_pause)
	{

		g_keys[m_rightKey] = false;

		cs = blockCollision(&m_gameBlock, 1, m_deltaY);

		if(cs == NoCollision)
		{
				
			if(m_deltaX == 0)
				m_deltaX = 1;

		}

	}
	
	if(g_keys[m_downKey] && !g_keys[m_rotateKey] && !m_pause && !m_gameOver && !m_winner)
	{

		if(m_gameBlock.getY() > -1)
		{

			while(blockCollision(&m_gameBlock, 0, 1) == NoCollision)
			{

				m_gameBlock.setY(m_gameBlock.getY() + 1);

			}

		}

	}

	if(g_keys[m_rotateKey] && !m_pause && !m_gameOver && !m_winner)
	{

		g_keys[m_rotateKey] = false;

		m_gameBlock.rotate(false);
		
		cs = blockCollision(&m_gameBlock, m_deltaX, 0);

		if(cs == LeftBorderCollision)
		{

			CollisionState cs2 = blockCollision(&m_gameBlock, m_deltaX + 1, 0);

			if(cs2 == NoCollision)
			{
		
				m_gameBlock.setX(m_gameBlock.getX() + 1);

		
			} else {

				cs2 = blockCollision(&m_gameBlock, m_deltaX + 2, 0);

				if(cs2 == NoCollision)
				{

					m_gameBlock.setX(m_gameBlock.getX() + 2);

				}

			}
			

		}

		if(cs == RightBorderCollision)
		{

			CollisionState cs2 = blockCollision(&m_gameBlock, m_deltaX - 1, 0);

			if(cs2 == NoCollision)
			{
		
				m_gameBlock.setX(m_gameBlock.getX() - 1);

		
			} else {

				cs2 = blockCollision(&m_gameBlock, m_deltaX - 2, 0);

				if(cs2 == NoCollision)
				{

					m_gameBlock.setX(m_gameBlock.getX() - 2);

				}

			}
			

		}

		cs = blockCollision(&m_gameBlock, m_deltaX, 0);
		
		if(cs != NoCollision)
			m_gameBlock.rotate(true);

	}

	cs = blockCollision(&m_gameBlock, m_deltaX, 1);

	if(cs == NoCollision)
	{
			
		if(m_deltaY == 0)			
			m_deltaY = 1;

		m_bindNext = false;

	}

	if(cs == BlockCollision)
	{

		long firstRow = 0;
		bool set = false;

		for(long i = 0; i < 4; ++i)
		{

			for(long j = 0; j < 4; ++j)
			{

				if(m_gameBlock.getShape()[(i * 4) + j] > 0)
				{

					if(!set)
						firstRow = i;

					set = true;

					i = 4;
					j = 4;

				}

			}

		}

		if((m_gameBlock.getY() + firstRow) < 1)
		{

			if(!m_gameOver)
			{
			
				if(m_gameOverSound)
				{

					if(m_soundEnabled)
					{
					
						FSOUND_PlaySound(FSOUND_FREE, m_gameOverSound);

					}

				}

			}

			m_gameOver = true;

		}

		m_smoothFactorY = 0;
		m_deltaY = 0;

		if(m_bindNext && m_smoothFactorY == 0)
		{

			bindToGrid(&m_gameBlock);

			m_bindNext = false;

		} else {

			m_bindNext = true;

		}

	}

	if(cs == DownCollision)
	{

		m_deltaY = 0;
				
		if(m_bindNext && m_smoothFactorY == 0)
		{

			bindToGrid(&m_gameBlock);

			m_bindNext = false;

		} else {

			m_bindNext = true;

		}

	}

	if(m_gameOver || m_winner)
	{
	
		timeElapsed = 0;

	} else {
		
		timeElapsed = SDL_GetTicks() - m_startTime;

	}

	if(m_removing && !m_pause)
	{

		m_smoothFactorFade += (0.0008 * timeElapsed);
		
		if(m_smoothFactorFade > 1.0)
		{

			m_smoothFactorY = 0;
			timeElapsed = 0;

			if(m_countScore)
			{

				m_score += (m_linesToRemoveCount * m_linesToRemoveCount) * 62;

			}
	
			m_linesErased += m_linesToRemoveCount;

			for(long j = 0; j < GRID_ROWS; ++j)
			{

				if(m_linesToRemove[j])
				{
		
					for(long k = j; k > 0; --k)
					{

						for(long i = 0; i < GRID_COLS; ++i)
						{

							m_grid[i][k] = m_grid[i][k - 1];

						}

					}

				}

				m_linesToRemoveCount--;

				m_linesToRemove[j] = false;

			}

			m_smoothFactorFade = 0.0;

			m_linesToRemoveCount = 0;

			m_removing = false;

			return;

		}
		
	}

	if(m_pause)
		timeElapsed = 0;

	if(m_removing)
		timeElapsed = 0;

	m_smoothFactorX += (0.020 * timeElapsed);
	m_smoothFactorY += ((0.004 + (m_level * 0.00035)) * timeElapsed);

	if(m_smoothFactorX >= 1)
	{

		m_smoothFactorX = 0;

		m_gameBlock.setX(m_gameBlock.getX() + m_deltaX);

		m_deltaX = 0;

	}

	if(m_smoothFactorY >= 1)
	{

		m_smoothFactorY = 0;

		m_gameBlock.setY(m_gameBlock.getY() + m_deltaY);

		m_deltaY = 0;

	}

	m_startTime = SDL_GetTicks();

}
