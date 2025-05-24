//
//  piecePawn.cpp
//  Lab04
//
//  Created by Mckay Larman on 5/21/25.
//

#include "piecePawn.h"
#include "board.h"
#include "uiDraw.h"    // for draw*()

void Pawn::getMoves(set <Move>& moves, const Board& board) const
{
   int col = position.getCol();
   int row = position.getRow();
   
   // Check space in front of us
   if (fWhite ? board[Position(col, row + 1)].getType() == SPACE :
                board[Position(col, row - 1)].getType() == SPACE)
   {
      Move move;
      Position source(position);
      move.setSource(source);
      fWhite ? move.setDest(Position(col, row + 1)) :
               move.setDest(Position(col, row - 1));
      moves.insert(move);
   }
   
   // Check if we have moved and if the space 2 in front is clear
   if (nMoves == 0 &&
       (fWhite ? board[Position(col, row + 2)].getType() == SPACE :
                 board[Position(col, row - 2)].getType() == SPACE))
   {
      Move move;
      Position source(position);
      move.setSource(source);
      fWhite ? move.setDest(Position(col, row + 2)) :
               move.setDest(Position(col, row - 2));
      moves.insert(move);
   }
   
   // Check capture
   if (fWhite)
   {
      // check right capture
      if (board[Position(col + 1, row + 1)].getType() != SPACE &&
      ! board[Position(col + 1, row + 1)].isWhite()) // it should be a black thing
      {
         Move move;
         Position source(position);
         move.setSource(source);
         move.setDest(Position(col + 1, row + 1));
         move.setCapture(board[Position(col + 1, row + 1)].getType());
         moves.insert(move);
      }
      
      // check left captue
      if (board[Position(col - 1, row + 1)].getType() != SPACE &&
      ! board[Position(col - 1, row + 1)].isWhite()) // it should be a black thing
      {
         Move move;
         Position source(position);
         move.setSource(source);
         move.setDest(Position(col - 1, row + 1));
         move.setCapture(board[Position(col - 1, row + 1)].getType());
         moves.insert(move);
      }
   }
   else
   {
      // check right capture
      if (board[Position(col + 1, row - 1)].getType() != SPACE &&
          board[Position(col + 1, row - 1)].isWhite()) // it should be a white thing
      {
         Move move;
         Position source(position);
         move.setSource(source);
         move.setDest(Position(col + 1, row - 1));
         move.setCapture(board[Position(col + 1, row - 1)].getType());
         moves.insert(move);
      }
      
      // check left captue
      if (board[Position(col - 1, row - 1)].getType() != SPACE &&
          board[Position(col - 1, row - 1)].isWhite()) // it should be a white thing
      {
         Move move;
         Position source(position);
         move.setSource(source);
         move.setDest(Position(col - 1, row - 1));
         move.setCapture(board[Position(col - 1, row - 1)].getType());
         moves.insert(move);
      }
   }
   
   // Check enpassant - good luck with this
   // We have to check the last move of the adjecent spaces to see what it is and where it came from.
   // If its a pawn and the old position is 2 rows different from the current one then we can enpassant
   
   // Check promotion
   // see if its at the opposite end and then promote it
   // fwhite ? row is 7 : row is 0
}
