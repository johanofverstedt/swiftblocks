
/**
 *
 *	Blocks.h
 *
 *	This file contains the definition of the Block class which
 *	is used to handle the moving blocks in the game.
 *
 *	Author:	Johan Öfverstedt
 *
 */

#ifndef BLOCKS_H
#define BLOCKS_H

/**
 *
 *	Definition NO_BLOCK
 *
 *	No block at this point.
 *
 */

#define NO_BLOCK 0

/**
 *
 *	Definition BLOCK_COLOR_RED
 *
 *	Red block colour.
 *
 */

#define BLOCK_COLOR_RED 1

/**
 *
 *	Definition BLOCK_COLOR_BLUE
 *
 *	Blue block colour.
 *
 */

#define BLOCK_COLOR_BLUE 2

/**
 *
 *	Definition BLOCK_COLOR_YELLOW
 *
 *	Yellow block colour.
 *
 */

#define BLOCK_COLOR_YELLOW 3

 /**
 *
 *	Definition BLOCK_COLOR_GREEN
 *
 *	Green block colour.
 *
 */

#define BLOCK_COLOR_GREEN 4

/**
 *
 *	Definition BLOCK_COLOR_PINK
 *
 *	Pink block colour.
 *
 */

#define BLOCK_COLOR_PINK 5

/**
 *
 *	Definition BLOCK_COLOR_ORANGE
 *
 *	Orange block colour
 *
 */

#define BLOCK_COLOR_ORANGE 6

/**
 *
 *	Class Block
 *
 *	Handles all the things that has to do with the moving block.
 *	Contains functions for adjusting the block position and create
 *	a new block by random.
 *
 */

class Block
{

public:

	Block() { clear(); }

	void clear();

	void createRandomBlock();

	long *getShape() { return m_shape[m_direction]; }
	
	long getDirection() { return m_direction; }

	long getMaxDirections() { return m_maxDirections; }

	long getX() { return m_x; }

	long getY() { return m_y; }

	void rotate(bool reverse);

	void setX(long x) { m_x = x; }

	void setY(long y) { m_y = y; }

	Block operator =(Block &Block2);

	long m_shape[4][16];

private:

	/**
	 *
	 *	Member variable m_direction
	 *
	 *	Keeps track of the direction of the block.
	 *	It can be a value of 1 to 4, depending
	 *	on how many directions the block
	 *	has(m_maxDirections).
	 *
	 */
	
	long m_direction;
	
	/**
	 *
	 *	Member varible m_maxDirections
	 *
	 *	The number of angles described for the current
	 *	block. Can be 1 to 4.
	 *
	 */

	long m_maxDirections;

	/**
	 *
	 *	Member variable m_x
	 *
	 *	Virtual x position in a grid where 1
	 *	is a whole square in the grid.
	 *
	 */

	long m_x;

	/**
	 *
	 *	Member variable m_y
	 *
	 *	Virtual y position in a grid where 1
	 *	is a whole square in the grid.
	 *
	 */
	
	long m_y;

};

#endif