/***********************************************************************
 * Source File:
 *		QUEEN
 * Author:
 *    <your name here>
 * Summary:
 *    The queen class
 ************************************************************************/

#include "pieceQueen.h"
#include "board.h"
#include "uiDraw.h"    // for draw*()

 /***************************************************
 * PIECE DRAW
 * Draw all the pieces.
 ***************************************************/
void Queen::display(ogstream* pgout) const
{
	bool black = !isWhite();
	pgout->drawQueen(getPosition(), black);
}


/**********************************************
 * BISHOP : GET POSITIONS
 *********************************************/
void Queen::getMoves(set <Move>& moves, const Board& board) const
{
	const Delta delta[] =
	{
		{-1,  1}, { 0,  1}, { 1,  1 },
		{-1,  0},           { 1,  0 },
		{-1, -1}, { 0, -1}, { 1, -1 }
	};

	moves = getMovesSlide(board, delta, 8);
}
