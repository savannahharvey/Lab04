/***********************************************************************
 * Header File:
 *    BISHOP
 * Author:
*    <your name here>
 * Summary:
 *    The bishop class
 ************************************************************************/

#pragma once

#include "piece.h"

 /***************************************************
  * BISHOP
  * The bishop
  ***************************************************/
class Bishop : public Piece
{
public:
   Bishop(const Position& pos, bool isWhite) : Piece(pos.getCol(), pos.getRow(), isWhite) {}
   Bishop(int c, int r, bool isWhite) : Piece(c, r, isWhite) {}
   ~Bishop() {}
   PieceType getType()            const { return BISHOP; }
   void getMoves(set <Move>& moves, const Board& board) const;
   void display(ogstream* pgout)  const;
};