
/**
 *
 *	Blocks.cpp
 *
 *	This file contains the implementation of the Block class which
 *	is used to handle the moving blocks in the game.
 *
 *	Author:	Johan Öfverstedt
 *
 */

//Basic Input/Output header:
#include <iostream>

//Time header:
#include "time.h"

//Game headers:
#include "Blocks.h"

/**
 *
 *	Function Block::clear()
 *
 *	Clears the current block arrays, and values.
 *
 */

void Block::clear()
{

	for(long i = 0; i < 4; ++i)
	{

		for(long j = 0; j < 18; ++j)
		{

			m_shape[i][j] = 0;

		}

	}

	m_maxDirections = 0;
	m_direction = 0;

	m_x = 0;
	m_y = 0;

}

/**
 *
 *	Function Block::createRandomBlock()
 *
 *	Create the block from one of the 6 block-types
 *	at random.
 *
 */

void Block::createRandomBlock()
{

	static long seed = 0;

	if(seed == 0)
	{
		
		seed = time(0);

		srand(seed);

	}

	seed *= time(0) % 255;

	long newShape = (rand()) % 7;

	if(newShape == 7)
		newShape = 0;

	if(newShape == 8)
		newShape = 3;

	if(newShape == 9)
		newShape = 4;

	clear();

	switch(newShape)
	{

	/*
	
		0X00	0000
		0X00	0000
		0X00	XXXX
		0X00	0000
		
	*/

	case 0:
		{

			long color = (rand() % 2) + 1;

			if(color == 2)
				color = 6;

			m_shape[0][1] = color;
			m_shape[0][5] = color;
			m_shape[0][9] = color;
			m_shape[0][13] = color;

			m_shape[1][8] = color;
			m_shape[1][9] = color;
			m_shape[1][10] = color;
			m_shape[1][11] = color;

			m_maxDirections = 2;
			
			break;

		}

	/*
	
		0000
		0XX0
		0XX0
		0000
		
	*/

	case 1:
		{

			long color = (rand() % 2) + 1;

			if(color == 1)
				color = 2;
			else if(color == 2)
				color = 3;

			m_shape[0][5] = color;
			m_shape[0][6] = color;
			m_shape[0][9] = color;
			m_shape[0][10] = color;

			m_maxDirections = 1;
			
			break;

		}

	/*
	
		0000	0000
		0XX0	00X0
		00XX	0XX0
		0000	0X00
		
	*/

	case 2:
		{

			long color = (rand() % 2) + 1;

			if(color == 1)
				color = 4;
			else if(color == 2)
				color = 5;

			m_shape[0][5] = color;
			m_shape[0][6] = color;
			m_shape[0][10] = color;
			m_shape[0][11] = color;

			m_shape[1][6] = color;
			m_shape[1][9] = color;
			m_shape[1][10] = color;
			m_shape[1][13] = color;

			m_maxDirections = 2;
			
			break;

		}

	/*
	
		0000	0000	0000	0000
		0X00	0XXX	00XX	0000
		0X00	0X00	000X	000X
		0XX0	0000	000X	0XXX
		
	*/

	case 3:
		{

			long color = (rand() % 2) + 1;

			if(color == 1)
				color = 5;
			else if(color == 2)
				color = 1;

			m_shape[0][5] = color;
			m_shape[0][9] = color;
			m_shape[0][13] = color;
			m_shape[0][14] = color;

			m_shape[1][5] = color;
			m_shape[1][6] = color;
			m_shape[1][7] = color;
			m_shape[1][9] = color;

			m_shape[2][6] = color;
			m_shape[2][7] = color;
			m_shape[2][11] = color;
			m_shape[2][15] = color;

			m_shape[3][13] = color;
			m_shape[3][14] = color;
			m_shape[3][11] = color;
			m_shape[3][15] = color;

			m_maxDirections = 4;
			
			break;

		}

	/*
	
		0000	0000	0000	0000
		00X0	0000	0XX0	0XXX
		00X0	0X00	0X00	000X
		0XX0	0XXX	0X00	0000
		
	*/

	case 4:
		{

			long color = (rand() % 2) + 1;

			if(color == 1)
				color = 4;
			else if(color == 2)
				color = 3;

			m_shape[0][6] = color;
			m_shape[0][10] = color;
			m_shape[0][13] = color;
			m_shape[0][14] = color;

			m_shape[1][9] = color;
			m_shape[1][13] = color;
			m_shape[1][14] = color;
			m_shape[1][15] = color;

			m_shape[2][5] = color;
			m_shape[2][6] = color;
			m_shape[2][9] = color;
			m_shape[2][13] = color;

			m_shape[3][5] = color;
			m_shape[3][6] = color;
			m_shape[3][7] = color;
			m_shape[3][11] = color;

			m_maxDirections = 4;
			
			break;

		}

	/*
	
		0000	0000
		00XX	0X00
		0XX0	0XX0
		0000	00X0
		
	*/

	case 5:
		{

			long color = (rand() % 2) + 1;

			if(color == 1)
				color = 2;
			else if(color == 2)
				color = 6;

			m_shape[0][6] = color;
			m_shape[0][7] = color;
			m_shape[0][9] = color;
			m_shape[0][10] = color;

			m_shape[1][6] = color;
			m_shape[1][10] = color;
			m_shape[1][11] = color;
			m_shape[1][15] = color;

			m_maxDirections = 2;
			
			break;

		}

	/*
	
		0000	0000	0000	0000
		0000	0X00	0XXX	000X
		00X0	0XX0	00X0	00XX
		0XXX	0X00	0000	000X
		
	*/

	case 6:
		{

			long color = (rand() % 2) + 1;

			if(color == 1)
				color = 4;
			else if(color == 2)
				color = 6;

			m_shape[0][10] = color;
			m_shape[0][13] = color;
			m_shape[0][14] = color;
			m_shape[0][15] = color;

			m_shape[1][5] = color;
			m_shape[1][9] = color;
			m_shape[1][10] = color;
			m_shape[1][13] = color;

			m_shape[2][5] = color;
			m_shape[2][6] = color;
			m_shape[2][7] = color;
			m_shape[2][10] = color;

			m_shape[3][7] = color;
			m_shape[3][10] = color;
			m_shape[3][11] = color;
			m_shape[3][15] = color;

			m_maxDirections = 4;
			
			break;

		}

	}

}

/**
 *
 *	Function Block::rotate()
 *
 *	Change the direction of the block
 *	clockwise if reverse is false, and counter-clockwise
 *	if reverse is true.
 *
 */

void Block::rotate(bool reverse)
{

	if(!reverse)
	{

		if((m_direction + 1) >= m_maxDirections)
		{

			m_direction = 0;

		} else {

			++m_direction;

		}

	} else {

		if((m_direction - 1) < 0)
		{

			m_direction = m_maxDirections - 1;

		} else {

			--m_direction;

		}

	}

}

/**
 *
 *	Operator Block::=
 *
 *	Copy a Block object to another.
 *
 */

Block Block::operator =(Block &Block2)
{
	
	m_shape[0][0] = Block2.m_shape[0][0];
	m_shape[0][1] = Block2.m_shape[0][1];
	m_shape[0][2] = Block2.m_shape[0][2];
	m_shape[0][3] = Block2.m_shape[0][3];
	m_shape[0][4] = Block2.m_shape[0][4];
	m_shape[0][5] = Block2.m_shape[0][5];
	m_shape[0][6] = Block2.m_shape[0][6];
	m_shape[0][7] = Block2.m_shape[0][7];
	m_shape[0][8] = Block2.m_shape[0][8];
	m_shape[0][9] = Block2.m_shape[0][9];
	m_shape[0][10] = Block2.m_shape[0][10];
	m_shape[0][11] = Block2.m_shape[0][11];
	m_shape[0][12] = Block2.m_shape[0][12];
	m_shape[0][13] = Block2.m_shape[0][13];
	m_shape[0][14] = Block2.m_shape[0][14];
	m_shape[0][15] = Block2.m_shape[0][15];

	m_shape[1][0] = Block2.m_shape[1][0];
	m_shape[1][1] = Block2.m_shape[1][1];
	m_shape[1][2] = Block2.m_shape[1][2];
	m_shape[1][3] = Block2.m_shape[1][3];
	m_shape[1][4] = Block2.m_shape[1][4];
	m_shape[1][5] = Block2.m_shape[1][5];
	m_shape[1][6] = Block2.m_shape[1][6];
	m_shape[1][7] = Block2.m_shape[1][7];
	m_shape[1][8] = Block2.m_shape[1][8];
	m_shape[1][9] = Block2.m_shape[1][9];
	m_shape[1][10] = Block2.m_shape[1][10];
	m_shape[1][11] = Block2.m_shape[1][11];
	m_shape[1][12] = Block2.m_shape[1][12];
	m_shape[1][13] = Block2.m_shape[1][13];
	m_shape[1][14] = Block2.m_shape[1][14];
	m_shape[1][15] = Block2.m_shape[1][15];

	m_shape[2][0] = Block2.m_shape[2][0];
	m_shape[2][1] = Block2.m_shape[2][1];
	m_shape[2][2] = Block2.m_shape[2][2];
	m_shape[2][3] = Block2.m_shape[2][3];
	m_shape[2][4] = Block2.m_shape[2][4];
	m_shape[2][5] = Block2.m_shape[2][5];
	m_shape[2][6] = Block2.m_shape[2][6];
	m_shape[2][7] = Block2.m_shape[2][7];
	m_shape[2][8] = Block2.m_shape[2][8];
	m_shape[2][9] = Block2.m_shape[2][9];
	m_shape[2][10] = Block2.m_shape[2][10];
	m_shape[2][11] = Block2.m_shape[2][11];
	m_shape[2][12] = Block2.m_shape[2][12];
	m_shape[2][13] = Block2.m_shape[2][13];
	m_shape[2][14] = Block2.m_shape[2][14];
	m_shape[2][15] = Block2.m_shape[2][15];

	m_shape[3][0] = Block2.m_shape[3][0];
	m_shape[3][1] = Block2.m_shape[3][1];
	m_shape[3][2] = Block2.m_shape[3][2];
	m_shape[3][3] = Block2.m_shape[3][3];
	m_shape[3][4] = Block2.m_shape[3][4];
	m_shape[3][5] = Block2.m_shape[3][5];
	m_shape[3][6] = Block2.m_shape[3][6];
	m_shape[3][7] = Block2.m_shape[3][7];
	m_shape[3][8] = Block2.m_shape[3][8];
	m_shape[3][9] = Block2.m_shape[3][9];
	m_shape[3][10] = Block2.m_shape[3][10];
	m_shape[3][11] = Block2.m_shape[3][11];
	m_shape[3][12] = Block2.m_shape[3][12];
	m_shape[3][13] = Block2.m_shape[3][13];
	m_shape[3][14] = Block2.m_shape[3][14];
	m_shape[3][15] = Block2.m_shape[3][15];

	m_direction = Block2.getDirection();

	m_maxDirections = Block2.getMaxDirections();

	m_x = Block2.getX();

	m_y = Block2.getY();

	return *this;

}