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
//virtual void Piece::getMoves(set <Move>& movesSet, const Board& board) const;

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

/*******************************************
* PIECE
* get moves for sliding pieces, queen, bishop and rook
*******************************************/
set <Move> Piece::getMovesSlide(const Board& board, const Delta deltas[], int numDelta) const
{
   set <Move> moves;
   for (int i = 0; i < numDelta; i++)
   {
      // new Position that is the next possible move
      Position posMove(position.getCol() + deltas[i].dCol,
         position.getRow() + deltas[i].dRow);

      while (posMove.isValid() &&
         (board[posMove].isWhite() != fWhite ||
            board[posMove].getType() == SPACE))
      {
         // create a new possible move and attributes
         Move move;
         Position posCopy = getPosition(); // new pos because it needs to be const
         move.setSource(posCopy);
         move.setDest(posMove);
         move.setCapture(board[posMove].getType());

         // insert into possible moves
         moves.insert(move);

         // change posMove to the next delta position for the next loop
         posMove.setRow(posMove.getRow() + deltas[i].dRow);
         posMove.setCol(posMove.getCol() + deltas[i].dCol);
      }
   }

   return moves;
}