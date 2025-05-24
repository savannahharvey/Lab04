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
   // Check space in front of us
   
   // Check if we have moved and if the space 2 in front is clear
   
   // Check capture
   
   // Check enpassant - good luck with this
   // We have to check the last move of the adjecent spaces to see what it is and where it came from.
   // If its a pawn and the old position is 2 rows different from the current one then we can enpassant
   
   // Check promotion
   // see if its at the opposite end and then promote it
   // fwhite ? row is 7 : row is 0
}
