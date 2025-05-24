//
//  piecePawn.h
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
 *    The PAWN class
 ************************************************************************/

#pragma once

#include "piece.h"

 /***************************************************
  * PAWN
  * The pawn, aka the "Most Confusing Piece"
  ***************************************************/
class Pawn : public Piece
{
public:
   Pawn(const Position& pos, bool isWhite) : Piece(10,10,true) { }
   Pawn(int c, int r, bool isWhite) : Piece(c, r, true) { }
   ~Pawn() {                }
   PieceType getType()            const { return PAWN; }
   void getMoves(set <Move>& moves, const Board& board) const;
   void display(ogstream* pgout)  const {}
};
