/***********************************************************************
 * Header File:
 *    QUEEN
 * Author:
*    <your name here>
 * Summary:
 *    The queen class
 ************************************************************************/

#pragma once

#include "piece.h"

 /***************************************************
  * QUEEN
  * The queen
  ***************************************************/
class Queen : public Piece
{
public:
   Queen(const Position& pos, bool isWhite) : Piece(pos.getCol(), pos.getRow(), isWhite) {}
   Queen(int c, int r, bool isWhite) : Piece(c, r, isWhite) {}
   ~Queen() {}
   PieceType getType()            const { return QUEEN; }
   void getMoves(set <Move>& moves, const Board& board) const;
   void display(ogstream* pgout)  const;
};