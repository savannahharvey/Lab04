/***********************************************************************
 * Source File:
 *    KNIGHT
 * Author:
 *    <your name here>
 * Summary:
 *    The knight class
 ************************************************************************/

#include "pieceKnight.h"
#include "board.h"
#include "uiDraw.h"    // for draw*()

 /***************************************************
 * PIECE DRAW
 * Draw all the pieces.
 ***************************************************/
void Knight::display(ogstream* pgout) const
{
   bool black = !isWhite();
	pgout->drawKnight(getPosition(), black);
}


/**********************************************
 * KNIGHT : GET POSITIONS
 *********************************************/
void Knight::getMoves(set <Move>& moves, const Board& board) const
{
   const Delta delta[] =
   {
                 { -1,  2 }, { 1,  2 },
      { -2,  1 },                      { 2,  1 },
      { -2, -1 },                      { 2, -1 },
                 { -1, -2 }, { 1, -2 }
   };

   moves = getMovesNoSlide(board, delta, 8);
}
