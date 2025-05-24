/***********************************************************************
 * Source File:
 *    BISHOP
 * Author:
 *    <your name here>
 * Summary:
 *    The bishop class
 ************************************************************************/

#include "pieceBishop.h"
#include "board.h"
#include "uiDraw.h"    // for draw*()

 /***************************************************
 * PIECE DRAW
 * Draw all the pieces.
 ***************************************************/
void Bishop::display(ogstream* pgout) const
{
	bool black = !isWhite();
	pgout->drawBishop(getPosition(), black);
}


/**********************************************
 * BISHOP : GET POSITIONS
 *********************************************/
void Bishop::getMoves(set <Move>& moves, const Board& board) const
{
	const Delta delta[] =
	{
		{-1,  1},       { 1,  1},

		{-1, -1},       { 1, -1}
	};

	moves = getMovesSlide(board, delta, 4);
}
