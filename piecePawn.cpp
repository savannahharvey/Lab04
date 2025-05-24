//
//  piecePawn.cpp
//  Lab04
//
//  Created by Mckay Larman on 5/21/25.
//

#include "piecePawn.h"
#include "board.h"
#include "uiDraw.h"    // for draw*()

 /***************************************************
 * PIECE DRAW
 * Draw all the pieces.
 ***************************************************/
void Pawn::display(ogstream* pgout) const
{
   bool black = !isWhite();
   pgout->drawPawn(getPosition(), black);
}


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

      // Check for promotion
      if (fWhite ? row + 1 == 7 : row - 1 == 0)
      {
         move.setMoveType(Move::PROMOTION);
      }
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
          !board[Position(col + 1, row + 1)].isWhite()) // it should be a black thing
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

   // Check for enpassant
   if (fWhite)
   {
      // check right capture
      if (board[Position(col + 1, row)].getType() == PAWN &&  // if a pawn
         board[Position(col + 1, row)].isWhite() == false &&  // if opposite color
         board[Position(col + 1, row)].getNMoves() == 1   )  // if only moved once
      {
         Move move;
         Position source(position);
         move.setSource(source);
         move.setDest(Position(col + 1, row + 1));
         move.setCapture(PAWN);
         move.setMoveType(Move::ENPASSANT);
         moves.insert(move);
      }

      // check left capture
      if (board[Position(col - 1, row)].getType() == PAWN &&  // if a pawn
         board[Position(col - 1, row)].isWhite() == false &&  // if opposite color
         board[Position(col - 1, row)].getNMoves() == 1   )  // if only moved once
      {
         Move move;
         Position source(position);
         move.setSource(source);
         move.setDest(Position(col - 1, row + 1));
         move.setCapture(PAWN);
         move.setMoveType(Move::ENPASSANT);
         moves.insert(move);
      }
   }
   else
   {
      // check right capture
      if (board[Position(col - 1, 3)].getType() == PAWN &&  // if a pawn
         board[Position(col - 1, row)].isWhite() == false &&  // if opposite color
         board[Position(col - 1, row)].getNMoves() == 1   )  // if only moved once
      {
         Move move;
         Position source(position);
         move.setSource(source);
         move.setDest(Position(col - 1, row - 1));
         move.setCapture(PAWN);
         move.setMoveType(Move::ENPASSANT);
         moves.insert(move);
      }

      // check left capture
      if (board[Position(col + 1, row)].getType() == PAWN &&  // if a pawn
         board[Position(col + 1, row)].isWhite() == false &&  // if opposite color
         board[Position(col + 1, row)].getNMoves() == 1   )  // if only moved once
      {
         Move move;
         Position source(position);
         move.setSource(source);
         move.setDest(Position(col + 1, row - 1));
         move.setCapture(PAWN);
         move.setMoveType(Move::ENPASSANT);
         moves.insert(move);
      }
   }
   // Check enpassant - good luck with this
   // We have to check the last move of the adjecent spaces to see what it is and where it came from.
   // If its a pawn and the old position is 2 rows different from the current one then we can enpassant
}
