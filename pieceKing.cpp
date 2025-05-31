//
//  pieceKing.cpp
//  Lab04
//
//  Created by Mckay Larman on 5/21/25.
//
#include "pieceKing.h"
#include "board.h"
#include "uiDraw.h"    // for draw*()

 /***************************************************
 * PIECE DRAW
 * Draw all the pieces.
 ***************************************************/
void King::display(ogstream* pgout) const
{
   bool black = !isWhite();
   pgout->drawKing(getPosition(), black);
}


void King::getMoves(set <Move>& moves, const Board& board) const
{
   const Delta deltas[] =
   {
      {-1,  1}, { 0,  1}, { 1,  1 },
      {-1,  0},           { 1,  0 },
      {-1, -1}, { 0, -1}, { 1, -1 }
   };
   
   moves = getMovesNoSlide(board, deltas, 8);
   
   // check if King has moved.
   if (nMoves == 0)
   {
      // short castle (king side)
      //             white side short castle             black side short castle
      if (fWhite ? !board[Position(7, 0)].isMoved() : !board[Position(7, 7)].isMoved())
      {
         // are the spaces between empty?
         if (fWhite ? board[Position(5, 0)].getType() == SPACE && board[Position(6, 0)].getType() == SPACE : // White side
                      board[Position(5, 7)].getType() == SPACE && board[Position(6, 7)].getType() == SPACE)  // Black side
         {
            // Make a new move
            Move move;
            Position posCopy = getPosition(); // new source because it needs to be const
            move.setSource(posCopy);
            fWhite ? move.setDest(Position(6, 0)) : move.setDest(Position(6, 7));
            move.setMoveType(Move::CASTLE_KING);
            moves.insert(move);
         }
      }
      
      // long castle (queen side)
      //             white side long castle             black side long castle
      if (fWhite ? !board[Position(0, 0)].isMoved() : !board[Position(0, 7)].isMoved())
      {
         // are the spaces between empty?
         if (fWhite ?
             board[Position(1,0)].getType() == SPACE && board[Position(2,0)].getType() == SPACE && board[Position(3,0)].getType() == SPACE:
             board[Position(1,7)].getType() == SPACE && board[Position(2,7)].getType() == SPACE && board[Position(3,7)].getType() == SPACE)
         {
            // Make a new move
            Move move;
            Position posCopy = getPosition(); // new source because it needs to be const
            move.setSource(posCopy);
            fWhite ? move.setDest(Position(2, 0)) : move.setDest(Position(2, 7));
            move.setMoveType(Move::CASTLE_QUEEN);
            moves.insert(move);
         }
      }
   }
}
