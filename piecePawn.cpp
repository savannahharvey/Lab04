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
   Position posMove;
   
   // Set posMove to the spot in front of us if we are black or white.
   posMove = fWhite ? Position(col, row + 1) : Position(col, row - 1);
   
   // we can only move foreward if its empty and a valid spot.
   if (posMove.isValid() && board[posMove].getType() == SPACE )
   {
      Move move;
      Position source(position);
      move.setSource(source);
      move.setDest(posMove);
      moves.insert(move);
      
      // Check Double move.
      posMove = fWhite ? Position(col, row + 2) : Position(col, row - 2);
      // Check if we have moved and the spaces in front of us are clear.
      if (nMoves == 0 && board[posMove] == SPACE)
      {
         Move move;
         Position source(position);
         move.setSource(source);
         move.setDest(posMove);
         moves.insert(move);
      }

      // Check for promotion
      if (fWhite ? row + 1 == 7 : row - 1 == 0)
      {
         move.setMoveType(Move::PROMOTION);
      }
   }
   
   // CHECK RIGHT CAPTURE
   // assign posMove for black or white.
   posMove = fWhite ? Position(col + 1, row + 1) : Position(col + 1, row - 1);
   
   if (posMove.isValid() &&                         // is valid
       board[posMove].getType() != SPACE &&         // anything but space
       board[posMove].isWhite() != this->isWhite()) // different colors
   {
      Move move;
      Position source(position);
      move.setSource(source);
      move.setDest(Position(posMove));
      move.setCapture(board[Position(posMove)].getType());
      moves.insert(move);
   }
   
   // CHECK LEFT CAPTURE
   // assign posMove for black or white
   posMove = fWhite ? Position(col - 1, row + 1) : Position(col - 1, row - 1);
   
   if (posMove.isValid() &&                         // is valid
       board[posMove].getType() != SPACE &&         // anything but space
       board[posMove].isWhite() != this->isWhite()) // different colors
   {
      Move move;
      Position source(position);
      move.setSource(source);
      move.setDest(Position(posMove));
      move.setCapture(board[Position(posMove)].getType());
      moves.insert(move);
   }

   // Check for enpassant
   if (fWhite)
   {
      posMove = Position(col + 1, row + 1);
      // check right capture
      if (posMove.isValid() &&
          board[Position(col + 1, row)].getType() == PAWN &&   // if a pawn
          board[Position(col + 1, row)].isWhite() == false &&  // if opposite color
          board[Position(col + 1, row)].getNMoves() == 1   )   // if only moved once
      {
         Move move;
         Position source(position);
         move.setSource(source);
         move.setDest(Position(posMove));
         move.setCapture(PAWN);
         move.setMoveType(Move::ENPASSANT);
         moves.insert(move);
      }

      posMove = Position(col - 1, row + 1);
      // check left capture
      if (posMove.isValid() &&
          board[Position(col - 1, row)].getType() == PAWN &&  // if a pawn
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
   // Black side en-passant
   else
   {
      posMove = Position(col - 1, row - 1);
      // check right capture
      if (posMove.isValid() &&
          board[Position(col - 1, row)].getType() == PAWN &&   // if a pawn
          board[Position(col - 1, row)].isWhite() == false &&  // if opposite color
          board[Position(col - 1, row)].getNMoves() == 1   )   // if only moved once
      {
         Move move;
         Position source(position);
         move.setSource(source);
         move.setDest(Position(posMove));
         move.setCapture(PAWN);
         move.setMoveType(Move::ENPASSANT);
         moves.insert(move);
      }
      
      posMove = Position(col + 1, row - 1);
      // check left capture
      if (posMove.isValid() &&
          board[Position(col + 1, row)].getType() == PAWN &&   // if a pawn
          board[Position(col + 1, row)].isWhite() == false &&  // if opposite color
          board[Position(col + 1, row)].getNMoves() == 1   )   // if only moved once
      {
         Move move;
         Position source(position);
         move.setSource(source);
         move.setDest(Position(posMove));
         move.setCapture(PAWN);
         move.setMoveType(Move::ENPASSANT);
         moves.insert(move);
      }
   }
}
