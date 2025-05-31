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

/***************************************************
* PEICE GET MOVES
* See what moves we can do as a pawn.
* 1. we can move forward (If nothing is in our way)
* 2. we can move 2 spots (If nothing is in our way and we havent moved yet.)
* 3. We can capture. (up one and over one left or right, if it is on the board and an enemy peice.)
* 4. We can EnPassant (Who made up this stupid rule?)
* 5. we can promote (get to the other side and be the queen!)
***************************************************/
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
      // Check for promotion
      if (fWhite ? posMove.getRow() == 7 : posMove.getRow() == 0)
      {
         move.setMoveType(Move::PROMOTION);
         move.setPromote(QUEEN);
      }
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
      // Check for promotion
      if (fWhite ? posMove.getRow() == 7 : posMove.getRow() == 0)
      {
         move.setMoveType(Move::PROMOTION);
         move.setPromote(QUEEN);
      }
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
      // Check for promotion
      if (fWhite ? posMove.getRow() == 7 : posMove.getRow() == 0)
      {
         move.setMoveType(Move::PROMOTION);
         move.setPromote(QUEEN);
      }
      moves.insert(move);
   }
   
   this->MoveEnpassant(moves, board);
}


/***************************************************
* PAWN MOVES ENPASSANt
* Handles logic for enpassant
***************************************************/
void Pawn::MoveEnpassant(set <Move> &moves, const Board& board) const
{
   // move right and left.
   const int cDelta[] = { 1, -1 };
   // check both directions
   for (int i = 0; i < 2; i++)
   {
      Position posMove(position.getCol() + cDelta[i], position.getRow() + (fWhite ? 1 : -1) ); // where we go
      Position posKill(position.getCol() + cDelta[i], position.getRow()); // what we take
      
      if (posMove.isValid() &&                                 // on the board
          position.getRow() == (fWhite ? 4 : 3) &&             // correct row for color
          board[posMove].getType() == SPACE &&                 // move into a space
          board[posKill].getType() == PAWN &&                  // only can capture a pawn
          board[posKill].isWhite() != fWhite &&                // only capture oposite color
          board[posKill].justMoved(board.getCurrentMove()) &&  // see if it was the last peice moved
          board[posKill].getNMoves() == 1 )                    // It can only move once!
      {
         // add the move.
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
