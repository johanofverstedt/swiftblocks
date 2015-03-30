
/**
 *
 *	Gameplay.h
 *
 *	This file contains the definitions and inlined functions of the 
 *	TetrisEngine class that handles the gameplay and some enumerations
 *	that are used in the class.
 *
 *	Author:	Johan Öfverstedt
 *
 */

#ifndef GAMEPLAY_H
#define GAMEPLAY_H

//SDL header:
#include "SDL.h"

//Game headers:
#include "Blocks.h"

/**
 *
 *	Definition GRID_COLS
 *
 *	The number of columns the grid
 *	will have.
 *
 */

#define GRID_COLS 8

 /**
 *
 *	Definition GRID_ROWS
 *
 *	The number of rows the grid
 *	will have.
 *
 */

#define GRID_ROWS 18

/**
 *
 *	Definition MAX_LEVELS
 *
 *	The number of levels that can
 *	be reached.
 *
 */

#define MAX_LEVELS 8

/**
 *
 *	Enumeration CollisionState
 *
 *	Is used to determine if there has been
 *	a collision, and if that's the case, what
 *	kind of collision.
 *
 */

enum CollisionState
{ 

	NoCollision = 0,
	RightBorderCollision = 1,
	LeftBorderCollision = 2,
	BlockCollision = 3,
	DownCollision = 4

};

/**
 *
 *	Enumeration InputConfig
 *
 *	Is used handle the different actions that
 *	can be bound to a key.
 *
 */

enum InputConfig
{

	RotateKey = 0,
	LeftKey = 1,
	RightKey = 2,
	DownKey = 3

};

/**
 *
 *	Class TetrisEngine
 *
 *	Handles all the things that has to do with the gameplay.
 *	To make sure that multiple instances of this class could be used
 *	at the same time, to for example, create the two-player mode, some
 *	things needs to be done outside of the class:
 *	
 *	Drawing the background.
 *	Event loop.
 *	Determine the player's speed.
 *	And more.
 *
 */

class TetrisEngine
{

public:
	
	TetrisEngine(long xpos, long ypos);

	~TetrisEngine();

	void bindToGrid(Block *b);

	CollisionState blockCollision(Block *b, long dx, long dy);

	void changeBGR(const char *newBGR);

	void destroyGame();

	bool drawGame();
	
	void eliminateRows();

	const char *getBGR() { return m_bgr; }

	bool getCountScore() { return m_countScore; }

	bool getGameOver() { return m_gameOver; }

	long getKeyConfig(InputConfig ic);

	long getLevel() { return m_level; }

	long getLinesErased() { return m_linesErased; }

	bool getPauseState() { return m_pause; }

	long getScore() { return m_score; }

	SDL_Surface *getScreen() { return m_screen; }

	bool getSoundEnabled() { return m_soundEnabled; }

	bool getWinner() { return m_winner; }

	bool loadGame();

	void resetGame();
	
	void setCountScore(bool cs) { m_countScore = cs; }

	void setGameOver(bool go) { m_gameOver = go; }
	
	void setKeyConfig(InputConfig ic, long newKey);

	void setLevel(long newLevel);

	void setPauseState(bool np) { m_pause = np; }

	void setScreen(SDL_Surface *scr) { m_screen = scr; }

	void setSoundEnabled(bool e) { m_soundEnabled = e; }

	void setWinner(bool w) { m_winner = w; }

	void setX(long nx) { m_x = nx; }

	void setY(long ny) { m_y = ny; }

	void updateGame();

protected:

	/**
	 *
	 *	Member variable m_screen
	 *
	 *	Pointer to the screen surface, provided
	 *	by the SDL library.
	 *
	 */

	SDL_Surface *m_screen;

	/**
	 *
	 *	Member variable m_gameField
	 *
	 *	Pointer to the background surface, for
	 *	this player.
	 *
	 */

	SDL_Surface *m_gameField;

	/**
	 *
	 *	Member array m_blocks
	 *
	 *	Array of surfaces to the different block
	 *	images.
	 *
	 */

	SDL_Surface *m_blocks[6];

	/**
	 *
	 *	Member variable m_scoreBoard
	 *
	 *	Pointer to the score board surface,
	 *	used as a background for the scoring
	 *	table.
	 *
	 */

	SDL_Surface *m_scoreBoard;

	/**
	 *
	 *	Member variable m_levelUpSound
	 *
	 *	Pointer to the sound played when
	 *	someone gets to the next level.
	 *
	 */

	FSOUND_SAMPLE *m_levelUpSound;

	/**
	 *
	 *	Member variable m_lineRemoveSound
	 *
	 *	Pointer to the sound played when
	 *	some lines get destroyed.
	 *
	 */

	FSOUND_SAMPLE *m_lineRemoveSound;

	/**
	 *
	 *	Member variable m_gameOverSound
	 *
	 *	Pointer to the sound played when
	 *	the game is over
	 *
	 */

	FSOUND_SAMPLE *m_gameOverSound;

	/**
	 *
	 *	Member variable m_fieldRect
	 *
	 *	A rect used to describe the rectangle
	 *	where the background will be drawn.
	 *
	 */

	SDL_Rect m_fieldRect;

	/**
	 *
	 *	Member variable m_scoreRect
	 *
	 *	A rect used to describe the rectangle
	 *	where the score board will be drawn.
	 *
	 */

	SDL_Rect m_scoreRect;

	/**
	 *
	 *	Member variable m_blockRect
	 *
	 *	A rect used to describe the rectangle
	 *	where a block will be drawn.
	 *
	 */

	SDL_Rect m_blockRect;

	/**
	 *
	 *	Member variable m_scoreFont
	 *
	 *	A font loaded with the BFont library.
	 *	Used to draw the score board, and
	 *	things like: game over, and you win.
	 *
	 */

	BFont_Info *m_scoreFont;

	/**
	 *
	 *	Member variable m_bgr
	 *
	 *	A string that contains the path to
	 *	the file, that is the current background.
	 *
	 */

	char *m_bgr;

	/**
	 *
	 *	Member array m_grid
	 *
	 *	Array containing the informtaion about
	 *	the game grid.
	 *
	 */

	long m_grid[GRID_COLS][GRID_ROWS];

	/**
	 *
	 *	Member array m_linesToRemove
	 *
	 *	Array which contains the lines that are
	 *	flagged for removal.
	 *
	 */

	bool m_linesToRemove[GRID_ROWS];

	/**
	 *
	 *	Member variable m_linetoRemoveCount
	 *
	 *	Number of lines to remove currently.
	 *
	 */

	long m_linesToRemoveCount;

	/**
	 *
	 *	Member variable m_linesErased
	 *
	 *	Number of lines that has been removed
	 *	so far this game.
	 *
	 */

	long m_linesErased;

	/**
	 *
	 *	Member variable m_level
	 *
	 *	Which level currently active.
	 *	Effects the speed.
	 *
	 */

	long m_level;

	/**
	 *
	 *	Member variable m_countScore
	 *
	 *	Flag that says if the score should
	 *	be counted or not.
	 *
	 */

	bool m_countScore;

	/**
	 *
	 *	Member variable m_score
	 *
	 *	Current earned score.
	 *
	 */

	long m_score;

	/**
	 *
	 *	Member variable m_smoothFactorX
	 *
	 *	X interpolation value between grid
	 *	squares, when moving the block.
	 *	Will allways be a value between 0.0f
	 *	and 1.0f.
	 *
	 */

	double m_smoothFactorX;

	/**
	 *
	 *	Member variable m_smoothFactorY
	 *
	 *	Y interpolation value between grid
	 *	squares, when moving the block.
	 *	Will allways be a value between 0.0f
	 *	and 1.0f.
	 *
	 */

	double m_smoothFactorY;

	/**
	 *
	 *	Member variable m_smoothFactorFade
	 *
	 *	Fade interpolation value when
	 *	removing a line.
	 *	Will allways be a value between 0.0f
	 *	and 1.0f.
	 *
	 */

	double m_smoothFactorFade;

	/**
	 *
	 *	Member variable m_deltaX
	 *
	 *	Keeps track of where the block is going.
	 *	-1 = Going left, 0 = Standing still, 
	 *	1 = Going right.
	 *	Will allways be either 0, 1, or -1.
	 *
	 */
	
	long m_deltaX;

	/**
	 *
	 *	Member variable m_deltaY
	 *
	 *	Keeps track of where the block is going.
	 *	0 = Standing still, 1 = Going down.
	 *	Will allways be either 0 or 1.
	 *
	 */

	long m_deltaY;

	/**
	 *
	 *	Member variable m_downKey
	 *
	 *	This player's key to send the block down,
	 *	instantaneous.
	 *
	 */

	long m_downKey;

	/**
	 *
	 *	Member variable m_leftKey
	 *
	 *	This player's key to move the block to
	 *	the left.
	 *
	 */

	long m_leftKey;

	/**
	 *
	 *	Member variable m_rightKey
	 *
	 *	This player's key to move the block to
	 *	the right.
	 *
	 */

	long m_rightKey;

	/**
	 *
	 *	Member variable m_rotateKey
	 *
	 *	This player's key to rotate the block.
	 *
	 */

	long m_rotateKey;

	/**
	 *
	 *	Member variable m_removing
	 *
	 *	Flag that is set true, when one or more
	 *	lines are full, and their content is fading
	 *	away.
	 *
	 */

	bool m_removing;

	/**
	 *
	 *	Member variable m_pause
	 *
	 *	Flag that is set true, when the game is
	 *	paused, and should not be subject to
	 *	any updates.
	 *
	 */

	bool m_pause;

	/**
	 *
	 *	Member variable m_gameOver
	 *
	 *	Flag that is set true, when the game is
	 *	over, and should not be subject to
	 *	any updates, just display the "game over"
	 *	text.
	 *
	 */

	bool m_gameOver;

	/**
	 *
	 *	Member variable m_gameOver
	 *
	 *	Flag that is set true, when the game is
	 *	over and this player has won, and should
	 *	not be subject to any updates, just display
	 *	the "you win" text.
	 *
	 */

	bool m_winner;

	/**
	 *
	 *	Variable m_soundEnabled
	 *
	 *	Flag that controls if any sound effects
	 *	are to be played.
	 *
	 */
	
	bool m_soundEnabled;
	
	/**
	 *
	 *	Member variable m_bindNext
	 *
	 *	Flag that is set true, when the block is
	 *	possibly touching ground, and should be
	 *	bound to the grid next update.
	 *
	 */
	
	bool m_bindNext;

	/**
	 *
	 *	Member variable m_x
	 *
	 *	The x offset at which this player's game
	 *	should be drawn.
	 *
	 */

	long m_x;

	/**
	 *
	 *	Member variable m_y
	 *
	 *	The y offset at which this player's game
	 *	should be drawn.
	 *
	 */

	long m_y;

	/**
	 *
	 *	Member variable m_startTime
	 *
	 *	The time that is set last time the game
	 *	was updated. Used to maintain computer
	 *	speed independence.
	 *
	 */

	long m_startTime;

	/**
	 *
	 *	Member object m_gameBlock
	 *
	 *	Handles the current moving block.
	 *
	 */

	Block m_gameBlock;

	/**
	 *
	 *	Member object m_nextBlock
	 *
	 *	Handles the block coming next.
	 *
	 */

	Block m_nextBlock;
	
};

#endif