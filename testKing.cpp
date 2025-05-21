/***********************************************************************
 * Source File:
 *    TEST KING
 * Author:
 *    <your name here>
 * Summary:
 *    The unit tests for the King
 ************************************************************************/

#include "testKing.h"
//#include "pieceRook.h"
#include "pieceKing.h"     
#include "board.h"
#include "uiDraw.h"
#include <cassert>      


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6       p p p         6
 * 5       p(k)p         5
 * 4       p p p         4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_blocked()
{
   // SETUP
   BoardEmpty board;
   King king(3, 4, false);
   king.fWhite = true;
   king.position.colRow = 0x21;
   board.board[2][1] = &king;
   White white(PAWN);
   board.board[2][5] = board.board[3][5] = board.board[4][5] = &white;
   board.board[2][4] = /* hello there */   board.board[4][4] = &white;
   board.board[2][3] = board.board[3][3] = board.board[4][3] = &white;

   set <Move> moves;

   // EXERCISE
   king.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 0);  // we are blocked

   // TEARDOWN
   board.board[2][5] = board.board[3][5] = board.board[4][5] = nullptr;
   board.board[2][4] = /* hello there */   board.board[4][4] = nullptr;
   board.board[2][3] = board.board[3][3] = board.board[4][3] = nullptr;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6       P P P         6
 * 5       P(k)P         5
 * 4       P P P         4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_capture()
{
   // SETUP
   BoardEmpty board;
   King king(3, 4, false);
   king.fWhite = true;
   king.position.colRow = 0x21;
   board.board[2][1] = &king;
   Black black(PAWN);
   board.board[2][5] = board.board[3][5] = board.board[4][5] = &black;
   board.board[2][4] = /* hello there */   board.board[4][4] = &black;
   board.board[2][3] = board.board[3][3] = board.board[4][3] = &black;

   set <Move> moves;
   Move d5c6p;
   Move d5d6p;
   Move d5e6p;
   Move d5c5p;
   Move d5e5p;
   Move d5c4p;
   Move d5d4p;
   Move d5e4p;
   d5c6p.source.colRow = d5d6p.source.colRow = d5e6p.source.colRow =
   d5c5p.source.colRow =                       d5e5p.source.colRow =
   d5c4p.source.colRow = d5d4p.source.colRow = d5e4p.source.colRow = 0x34;
   
   d5c6p.capture = d5d6p.capture = d5e6p.capture =
   d5c5p.capture =                 d5e5p.capture =
   d5c4p.capture = d5d4p.capture = d5e4p.capture = PAWN;
   
   d5c6p.dest.colRow = 0x25;
   d5d6p.dest.colRow = 0x35;
   d5e6p.dest.colRow = 0x45;
   d5c5p.dest.colRow = 0x24;
   d5e5p.dest.colRow = 0x44;
   d5c4p.dest.colRow = 0x23;
   d5d4p.dest.colRow = 0x33;
   d5e4p.dest.colRow = 0x43;
   

   // EXERCISE
   king.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 8);  // 8 moves

   // TEARDOWN
   board.board[2][5] = board.board[3][5] = board.board[4][5] = nullptr;
   board.board[2][4] = /* hello there */   board.board[4][4] = nullptr;
   board.board[2][3] = board.board[3][3] = board.board[4][3] = nullptr;
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6       . . .         6
 * 5       .(k).         5
 * 4       . . .         4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_free()
{
   assertUnit(NOT_YET_IMPLEMENTED);
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2   . .               2
 * 1  (k).               1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_end()
{
   assertUnit(NOT_YET_IMPLEMENTED);
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2         p p p       2
 * 1   r   . .(k). . r   1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_whiteCastle()
{
   assertUnit(NOT_YET_IMPLEMENTED);
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8   R   . .(K). . R   8
 * 7         P P P       7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_blackCastle()
{
   assertUnit(NOT_YET_IMPLEMENTED);
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2         p p p       2
 * 1   r     .(k).   r   1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_whiteCastleKingMoved()
{
   assertUnit(NOT_YET_IMPLEMENTED);
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2         p p p       2
 * 1   r     .(k).   r   1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_whiteCastleRookMoved()
{
   assertUnit(NOT_YET_IMPLEMENTED);
}

/*************************************
 * GET TYPE : king
 * Input:
 * Output: KING
 **************************************/
void TestKing::getType()
{
   assertUnit(NOT_YET_IMPLEMENTED);
}


