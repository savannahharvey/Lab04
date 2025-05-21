//
//  pieceKing.h
//  Lab04
//
//  Created by Mckay Larman on 5/21/25.
//


/***********************************************************************
 * Header File:
 *    KING
 * Author:
*    McKay Larman
 * Summary:
 *    The KING class
 ************************************************************************/

#pragma once

#include "piece.h"

 /***************************************************
  * KNIGHT
  * The knight, aka the "Horse"
  ***************************************************/
class King : public Piece
{
public:
   King(const Position& pos, bool isWhite) : Piece(10,10,true) { }
   King(int c, int r, bool isWhite) : Piece(c, r, true) { }
   ~King() {                }
   PieceType getType()            const { return KING; }
   void getMoves(set <Move>& moves, const Board& board) const;
   void display(ogstream* pgout)  const;
};
