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
	pgout->drawBishop(getPosition(), isWhite());
}

/*************************************************
* BISHOP : GET MOVES
**************************************************/
set <Move> Bishop::getMovesSlide(const Board& board, const Delta deltas[], int numDelta) const
{
	set <Move> moves;
	for (int i = 0; i < numDelta; i++)
	{
		Position posMove(position, deltas[i]);
		posMove.setCol(delta[i].dCol /* * */);
		int r = position.getRow() + deltas[i].dRow;
		int c = position.getCol() + deltas[i].dCol;
		while (r >= 0 && r < 8 && c >= 0 && c < 8 && board[r * 8 + c] == SPACE)
		{
			moves.insert(/*some kind of move object...*/r * 8 + c);
			r += moves[i].row;
			c += moves[i].col;
		}

		if (posMove.isValid() && (board[posMove].isWhite() != fWhite || board[posMove] == SPACE))
		{
			Move move;
			Position posCopy = getPosition();
			move.setSource(posCopy);
			move.setDest(posMove);
			// set to white's turn?...
			if (board[posMove] != SPACE)
				move.setCapture(board[posMove].getType());
			moves.insert(move);
		}
	}

	return moves;
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

	moves = getMovesSlide(board, delta, sizeof(delta) / sizeof(delta[0]));
}
