/***********************************************************************
 * Source File:
 *		ROOK
 * Author:
 *    <your name here>
 * Summary:
 *    The rook class
 ************************************************************************/

#include "pieceRook.h"
#include "board.h"
#include "uiDraw.h"    // for draw*()

 /***************************************************
 * PIECE DRAW
 * Draw all the pieces.
 ***************************************************/
void Rook::display(ogstream* pgout) const
{
	bool black = !isWhite();
	pgout->drawRook(getPosition(), black);
}


/**********************************************
 * BISHOP : GET POSITIONS
 *********************************************/
void Rook::getMoves(set <Move>& moves, const Board& board) const
{
	const Delta delta[] =
	{
		          { 0,  1},
		{-1,  0},           { 1,  0 },
		          { 0, -1}
	};

	moves = getMovesSlide(board, delta, 4);
}
