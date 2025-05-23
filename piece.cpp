/***********************************************************************
 * Source File:
 *    PIECE 
 * Author:
 *    <your name here>
 * Summary:
 *    The Piece base class and all the derived classes:
 *       SPACE, KING, QUEEN, ROOK, KNIGHT, BISHOP, PAWN
 ************************************************************************/

#include "position.h"  // for POSITION
#include "piece.h"     // for all the PIECE class definitions
#include "pieceSpace.h"
#include "pieceKnight.h"
#include "board.h"     // for BOARD
#include "uiDraw.h"    // for draw*()
#include <cassert>     // because we are paranoid
using namespace std;


/************************************************
 * PIECE : ASSIGN
 ***********************************************/
const Piece & Piece::operator = (const Piece & rhs)
{
   this->fWhite = rhs.fWhite;
   this->lastMove = rhs.lastMove;
   this->nMoves = rhs.nMoves;
   return *this;
}

/************************************************
 * PIECE : GET MOVES
 * Iterate through the moves decorator to allow a piece to move
 ***********************************************/
void Piece::getMoves(set <Move> & movesSet, const Board & board) const
{
}

set <Move> Piece::getMovesNoSlide(const Board& board, const Delta deltas[], int numDelta) const
{
   set <Move> moves;
   // Iterate through the deltas
   for (int i = 0; i < numDelta; i++)
   {
      // make a position for the new location
      Position posDest(position, deltas[i]);
      
      // Check if we can move there
      if (posDest.isValid() &&
          (board[posDest].isWhite() != fWhite || board[posDest].getType() == SPACE) )
      {
         // Make a new move
         Move move;
         Position posCopy = getPosition(); // new source because it needs to be const
         move.setSource(posCopy);
         move.setDest(posDest);
         // see if its a capture.
         if (board[posDest] != SPACE)
            move.setCapture(board[posDest].getType());
         moves.insert(move);
      }
   }
   return moves;
}
